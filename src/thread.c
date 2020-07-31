
#include "imageprocessing.h"
#include <stdio.h>
#include <stdlib.h>
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

int main() {
    pthread_t threads[n_threads];
    int threads_id[n_threads];

    img = abrir_imagem("data/lena.jpg");

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
    return 0;
}
