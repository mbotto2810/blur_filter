
#include "imageprocessing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#define n_threads 3
#define N 10

imagem img;

void* filtro_thread(void *arg) {
    int *Q = (int*)(arg);
    int M = (*Q);
    multi_filtro(&img, N, M);
    return NULL;
}

int main(int argc, int **argv) {
    char IMG[100];
    if (argv[1]==NULL) {
        strcpy(IMG,"data/lena.jpg");
    }
    else {
        strcpy(IMG,argv[1]);
    }

    clock_t ct0, ct1, dct; /* Medida de tempo baseada no clock da CPU */
    struct timeval rt0, rt1, drt; /* Tempo baseada em tempo real */
    void *P;

    gettimeofday(&rt0, NULL);
    ct0 = clock();


    pthread_t threads[n_threads];
    int threads_id[n_threads];

    img = abrir_imagem(IMG);

    //Identifica threads
    for (int j=0 ; j<n_threads ; j++) {
        threads_id[j]=j;
    }

    //Dispara threads
    for (int j=0 ; j<n_threads ; j++) {
        pthread_create(&(threads[j]),NULL,filtro_thread,(void *) (&threads_id[j]));
    }

    //Espera threads
    for (int j=0; j<n_threads; j++) {
       pthread_join(threads[j],NULL);
    }

    salvar_imagem("out.jpg", &img);
    liberar_imagem(&img);


    ct1 = clock();
    gettimeofday(&rt1, NULL);

    timersub(&rt1, &rt0, &drt);

    printf("real: %ld.%06ld \n", drt.tv_sec, drt.tv_usec);
    printf("user: %f \n", (double)(ct1-ct0)/CLOCKS_PER_SEC);
    printf("\n");

    return 0;
}
