
#include "imageprocessing.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h> /* exit() */
#include <sys/time.h>
#include <time.h>
#include <sys/types.h> /* define pid_t */
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h> /* fork() */

#define N 10
#define n_processos 3

int main(int argc, char **argv) {

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


    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANON;

    /* Criar area de memoria compartilhada */
    imagem *img;
    img = (imagem*) mmap(NULL, sizeof(imagem), protection, visibility, 0, 0);
    *img = abrir_imagem_mmap(IMG);

    pid_t pid[n_processos];
    for (int i=0; i<n_processos; i++) {
        pid[i] = fork();
        if (pid[i]==0) {
            multi_filtro(img, N, i);
            exit(0);
        }
    }

    for (int i=0; i<n_processos; i++) {
        waitpid(pid[i], NULL, 0);
    }

    salvar_imagem("out.jpg", img);
    liberar_imagem_mmap(img);



    ct1 = clock();
    gettimeofday(&rt1, NULL);
    timersub(&rt1, &rt0, &drt);
    printf("real: %ld.%06ld \n", drt.tv_sec, drt.tv_usec);
    printf("user: %f \n", (double)(ct1-ct0)/CLOCKS_PER_SEC);
    printf("\n");


    return 0;
}
