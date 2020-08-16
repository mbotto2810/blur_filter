
#include <stdlib.h> /* exit */
#include <stdio.h> /* printf */
#include "imageprocessing.h"
#include <FreeImage.h> /* image structs and functions */
#include <sys/types.h> /* define pid_t */
#include <sys/wait.h> /* waitpid */
#include <sys/mman.h> /* mmap */
#include <unistd.h> /* fork() */


imagem abrir_imagem_mmap(char *nome_do_arquivo) {
    FIBITMAP *bitmapIn;
    int x, y;
    RGBQUAD color;

    /* Defines the mmap flags. The memory has R/W flags, shared and anonnymous*/
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANON;

    imagem I;

    bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

    if (bitmapIn == 0) {
    // printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
    } else {
    // printf("Arquivo lido corretamente!\n");
    }

    x = FreeImage_GetWidth(bitmapIn);
    y = FreeImage_GetHeight(bitmapIn);

    I.width = x;
    I.height = y;
    /* Here i used mmap instead of malloc to deal with the shared memory space on multiprocess */
    I.r = (float *) mmap(NULL,sizeof(float)*x*y,protection,visibility,0,0);
    I.g = (float *) mmap(NULL,sizeof(float)*x*y,protection,visibility,0,0);
    I.b = (float *) mmap(NULL,sizeof(float)*x*y,protection,visibility,0,0);

    for (int i=0; i<x; i++) {
        for (int j=0; j <y; j++) {
            int idx;
            FreeImage_GetPixelColor(bitmapIn, i, j, &color);

            idx = i + (j*x);

            I.r[idx] = color.rgbRed;
            I.g[idx] = color.rgbGreen;
            I.b[idx] = color.rgbBlue;
        }
    }
    return I;

}

imagem abrir_imagem(char *nome_do_arquivo) {
    FIBITMAP *bitmapIn;
    int x, y;
    RGBQUAD color;
    imagem I;

    bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

    if (bitmapIn == 0) {
    // printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
    } else {
    // printf("Arquivo lido corretamente!\n");
    }

    x = FreeImage_GetWidth(bitmapIn);
    y = FreeImage_GetHeight(bitmapIn);

    I.width = x;
    I.height = y;
    I.r = malloc(sizeof(float) * x * y);
    I.g = malloc(sizeof(float) * x * y);
    I.b = malloc(sizeof(float) * x * y);

    for (int i=0; i<x; i++) {
        for (int j=0; j <y; j++) {
            int idx;
            FreeImage_GetPixelColor(bitmapIn, i, j, &color);

            idx = i + (j*x);

            I.r[idx] = color.rgbRed;
            I.g[idx] = color.rgbGreen;
            I.b[idx] = color.rgbBlue;
        }
    }
    return I;

}

void liberar_imagem(imagem *I) {
    free(I->r);
    free(I->g);
    free(I->b);
}


void liberar_imagem_mmap(imagem *I) {
    /* I use munmap to free the memory space of abrir_imagem_mmap */
    munmap(I->r,0);
    munmap(I->g,0);
    munmap(I->b,0);
}

void salvar_imagem(char *nome_do_arquivo, imagem *I) {
    FIBITMAP *bitmapOut;
    RGBQUAD color;

    //printf("Salvando imagem %d por %d...\n", I->width, I->height);
    bitmapOut = FreeImage_Allocate(I->width, I->height, 24, 0, 0, 0);

    for (int i=0; i<I->width; i++) {
        for (int j=0; j<I->height; j++) {
        int idx;

        idx = i + (j*I->width);
        color.rgbRed = I->r[idx];
        color.rgbGreen = I->g[idx];
        color.rgbBlue = I->b[idx];

        FreeImage_SetPixelColor(bitmapOut, i, j, &color);
        }
    }

    FreeImage_Save(FIF_JPEG, bitmapOut, nome_do_arquivo, JPEG_DEFAULT);
}


void filtro(imagem *I, int N) {
        /* void filtro(imagem *I, int N)
           - returns nothing
           - Implement the blur filter
           - It has a pointer to a struct image, thus one argument is the image that i am deling with
           - It has a integer N of how many pixels i want to make a median
        */

        /* Contagem is for how many pixels i am calculating the mean value and the others are for storing the mean values of each channel */
        int media_r, media_g, media_b;
        int contagem;
        /* 2 for statements to acess all the pixels */
        for (int i=0; i<(I->width); i++) {
            for (int j=0; j<(I->height); j++) {
                media_r = 0;
                media_g = 0;
                media_b = 0;
                contagem = 0;
                for (int k=-N; k<=N; k++) {
                    for (int z=-N; z<=N; z++) {
                        /* On this if statemnet i check if i am acessing a valid memory location on the image */
                        if ( (((j+k)*I->width + i + z) >= 0) && (((j+k)*I->width + i + z) <= ((I->width)*(I->height-1)+I->width-1)) ) {
                            contagem++;
                            /* Mean in channel R */
                            media_r = media_r + I->r[(j+k)*I->width + i + z] ;
                            /* Mean in channel G */
                            media_g = media_g + I->g[(j+k)*I->width + i + z] ;
                            /* Mean in channel B */
                            media_b = media_b + I->b[(j+k)*I->width + i + z] ;
                        }
                    }
                }
                /* Here i pass the final result to the struct of the image */
                I->r[j*I->width + i] = media_r/contagem;
                I->g[j*I->width + i] = media_g/contagem;
                I->b[j*I->width + i] = media_b/contagem;

            }
        }
    }

void multi_filtro(imagem *I, int N, int n) {
         /* void filtro(imagem *I, int N, int n)
           - returns nothing
           - implement the blur filter with each channel (R,G,B) being worked on with a diferrent thread/process
           - It has a pointer to a struct image, thus one argument is the image that i am deling with
           - It has an integer N of how many pixels i want to make the median
           - It has an integer identifying the process/thread

           On this function the logic follows filtro() but i implemented a division
           on the tasks based on the division remainder of 3. In this way each thread/worker
           deals only with one channel (R,G,B).
        */

          if (n%3==0) {
              int media_r;
              int contagem_r;
              for (int i=0; i<(I->width); i++) {
                    for (int j=0; j<(I->height); j++) {
                        media_r = 0;
                        contagem_r = 0;
                            for (int k=-N; k<=N; k++) {
                                for (int z=-N; z<=N; z++) {
                                    /* On this if statemnet i check if i am acessing a valid memory location on the image */
                                    if ( (((j+k)*I->width + i + z) >= 0) && (((j+k)*I->width + i + z) <= ((I->width)*(I->height-1)+I->width-1)) ) {
                                        contagem_r++;
                                        /* Mean on channel R */
                                        media_r = media_r + I->r[(j+k)*I->width + i + z] ;
                                    }
                                }
                            }
                        I->r[j*I->width + i] = media_r/contagem_r;
                    }
                }
            }
          if (n%3==1) {
              int media_b;
              int contagem_b;
              for (int i=0; i<(I->width); i++) {
                    for (int j=0; j<(I->height); j++) {
                        media_b = 0;
                        contagem_b = 0;
                            for (int k=-N; k<=N; k++) {
                                for (int z=-N; z<=N; z++) {
                                    /* On this if statemnet i check if i am acessing a valid memory location on the image */
                                    if ( (((j+k)*I->width + i + z) >= 0) && (((j+k)*I->width + i + z) <= ((I->width)*(I->height-1)+I->width-1)) ) {
                                        contagem_b++;
                                        /* Mean on channel B */
                                        media_b = media_b + I->b[(j+k)*I->width + i + z] ;
                                    }
                                }
                            }
                        I->b[j*I->width + i] = media_b/contagem_b;
                    }
                }
            }

          if (n%3==2) {
              int media_g;
              int contagem_g;
              for (int i=0; i<(I->width); i++) {
                    for (int j=0; j<(I->height); j++) {
                        media_g = 0;
                        contagem_g = 0;
                            for (int k=-N; k<=N; k++) {
                                for (int z=-N; z<=N; z++) {
                                    /* On this if statemnet i check if i am acessing a valid memory location on the image */
                                    if ( (((j+k)*I->width + i + z) >= 0) && (((j+k)*I->width + i + z) <= ((I->width)*(I->height-1)+I->width-1)) ) {
                                        contagem_g++;
                                        /* Mean on channel G */
                                        media_g = media_g + I->g[(j+k)*I->width + i + z] ;
                                    }
                                }
                            }
                        I->g[j*I->width + i] = media_g/contagem_g;
                    }
                }
            }
    }
