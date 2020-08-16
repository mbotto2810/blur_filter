
#include "imageprocessing.h" /* For all the functions that i created */
#include <stdio.h> /* printf */
#include <string.h> /* strcpy */
#include <stdlib.h> /* exit */
#include <time.h> /* time measure */
#include <sys/time.h> /* time measure*/
#include <pthread.h> /* pthread */
#include "cronometro.h"

#define n_threads 3 /* Number of threads */
#define N 10 /* The number of pixels that i am doing the mean value */

/* A global variable that i am sharing beetwen the threads */
imagem img;

void* filtro_thread(void *arg) {
    int *Q = (int*)(arg);
    int M = (*Q); /* Check to see what thread i am dealing with */
    multi_filtro(&img, N, M); /* Implement the filter. Pass M to the fiter to divide the tasks  */
    return NULL;
}

int main(int argc, char **argv) {

    /* Here i check if an image was selected, if not a choose lena.jpg for you*/
    char IMG[100];
    if (argv[1]==NULL) {
        strcpy(IMG,"data/lena.jpg");
    }
    else {
        strcpy(IMG,argv[1]);
    }

    /* Begins the time measure */
    clock_t ct0, ct1, dct; /* CPU clock */
    struct timeval rt0, rt1, drt; /* Real time */
    void *P;
    gettimeofday(&rt0, NULL);
    ct0 = clock();

    /* Creates a vector of threads and threads identification */
    pthread_t threads[n_threads];
    int threads_id[n_threads];

    img = abrir_imagem(IMG);

    /* Attribute a number to each thread */
    for (int j=0 ; j<n_threads ; j++) {
        threads_id[j]=j;
    }

    /* Begins all the threads */
    for (int j=0 ; j<n_threads ; j++) {
        pthread_create(&(threads[j]),NULL,filtro_thread,(void *) (&threads_id[j]));
    }

    /* Wait fot all the threads to finish */
    for (int j=0; j<n_threads; j++) {
       pthread_join(threads[j],NULL);
    }

    /* Save the image and free the image memory */
    salvar_imagem("out.jpg", &img);
    liberar_imagem(&img);


    /*End measuring the time*/
    ct1 = clock();
    gettimeofday(&rt1, NULL);
    timersub(&rt1, &rt0, &drt);
    printf("real: %ld.%06ld \n", drt.tv_sec, drt.tv_usec);
    printf("user: %f \n", (double)(ct1-ct0)/CLOCKS_PER_SEC);
    printf("\n");

    return 0;
}
