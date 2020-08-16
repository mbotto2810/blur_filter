
#include "imageprocessing.h" /* For all the funtions that i created*/
#include <string.h> /* strcpy */
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit */
#include <sys/time.h> /* time measure */
#include <time.h> /* time measure */
#include <sys/types.h> /* define pid_t */
#include <sys/wait.h> /* waitpid */
#include <sys/mman.h> /* mmap */
#include <unistd.h> /* fork */
#include "cronometro.h"

#define N 10 /* The number of pixels that i am doing the meean value */
#define n_processos 3 /* Number of child process */

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

    /* Defines the mmap flags. The memory has R/W flags, shared and anonnymous*/
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANON;

    /* Creates a shared memory space beetwen the chidren and parent */
    imagem *img;
    img = (imagem*) mmap(NULL, sizeof(imagem), protection, visibility, 0, 0);

    /* The memory on img receives the IMG path data */
    *img = abrir_imagem_mmap(IMG);

    /* Beggins the children tasks and exits after the filter is implemented on the memory above */
    pid_t pid[n_processos];
    for (int i=0; i<n_processos; i++) {
        pid[i] = fork();
        if (pid[i]==0) {
            multi_filtro(img, N, i);
            exit(0);
        }
    }

    /* Wait for all the children to end */
    for (int i=0; i<n_processos; i++) {
        waitpid(pid[i], NULL, 0);
    }

    /* Save the image and free the image memory */
    salvar_imagem("out.jpg", img);
    liberar_imagem_mmap(img);

    /*End measuring the time*/
    ct1 = clock();
    gettimeofday(&rt1, NULL);
    timersub(&rt1, &rt0, &drt);
    printf("real: %ld.%06ld \n", drt.tv_sec, drt.tv_usec);
    printf("user: %f \n", (double)(ct1-ct0)/CLOCKS_PER_SEC);
    printf("\n");

    return 0;
}
