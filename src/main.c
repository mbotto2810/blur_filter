
#include <time.h> /* time measure */
#include <sys/time.h> /* time measure */
#include <string.h> /* sctrcpy */
#include <stdio.h> /* For printf */
#include "imageprocessing.h" /* For all the functions that i created */
#include "cronometro.h"

#define N 10 /* The number of pixels that i am doing the mean value*/

int main(int argc, char **argv) {
    /* Here i check if an image was selected, if not a choose lena.jpg for you*/
    char IMG[100];
    if (argv[1]==NULL) {
      strcpy(IMG,"data/lena.jpg");
    }
    else {
      strcpy(IMG,argv[1]);
    }
    /* Begin measuring the time */
    clock_t ct0, ct1, dct; /* CPU clock */
    struct timeval rt0, rt1, drt; /* Real time */
    void *P;
    gettimeofday(&rt0, NULL);
    ct0 = clock();

    imagem img;
    /* The memory on img receives the IMG path data */
    img = abrir_imagem(IMG);
    /* Blur filter */
    filtro(&img, N);
    /* Save the image after the filter */
    salvar_imagem("out.jpg", &img);
    /* Free the image memory */
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
