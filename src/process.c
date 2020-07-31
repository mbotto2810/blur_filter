
#include "imageprocessing.h"
#include <stdio.h>
#include <stdlib.h> /* exit() */
#include <sys/types.h> /* define pid_t */
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h> /* fork() */

#define N 10
#define n_processos 3

int main() {

    /* Definir flags de protecao e visibilidade de memoria */
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANON;

    /* Criar area de memoria compartilhada */
    imagem *img;
    img = (imagem*) mmap(NULL, sizeof(imagem), protection, visibility, 0, 0);
    *img = abrir_imagem("data/lena.jpg");

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
    liberar_imagem(img);
    return 0;
}
