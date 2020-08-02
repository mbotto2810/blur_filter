
#include <stdlib.h>
#include <stdio.h>

#include "imageprocessing.h"

#include <FreeImage.h>

/*
imagem abrir_imagem(char *nome_do_arquivo);
void salvar_imagem(char *nome_do_arquivo, imagem *I);
void liberar_imagem(imagem *i);
void filtro(imagem *I, int N);
void multi_filtro(imagem *I, int N, int n);
*/

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
      int media_r, media_g, media_b;
      int contagem;
      for (int i=0; i<(I->width); i++) {
            for (int j=0; j<(I->height); j++) {
                media_r = 0;
                media_g = 0;
                media_b = 0;
                contagem = 0;
                for (int k=-N; k<=N; k++) {
                    for (int z=-N; z<=N; z++) {
                        if ( (((j+k)*I->width + i + z) >= 0) && (((j+k)*I->width + i + z) <= ((I->width)*(I->height-1)+I->width-1)) ) {
                            contagem++;
                            /* Media no canal R */
                            media_r = media_r + I->r[(j+k)*I->width + i + z] ;
                            /* Media no canal G */
                            media_g = media_g + I->g[(j+k)*I->width + i + z] ;
                            /* Media no canal B */
                            media_b = media_b + I->b[(j+k)*I->width + i + z] ;
                        }
                    }
                }

                I->r[j*I->width + i] = media_r/contagem;
                I->g[j*I->width + i] = media_g/contagem;
                I->b[j*I->width + i] = media_b/contagem;

            }
        }
    }

void multi_filtro(imagem *I, int N, int n) {
          if (n%3==0) {
              int media_r;
              int contagem_r;
              for (int i=0; i<(I->width); i++) {
                    for (int j=0; j<(I->height); j++) {
                        media_r = 0;
                        contagem_r = 0;
                            for (int k=-N; k<=N; k++) {
                                for (int z=-N; z<=N; z++) {
                                    if ( (((j+k)*I->width + i + z) >= 0) && (((j+k)*I->width + i + z) <= ((I->width)*(I->height-1)+I->width-1)) ) {
                                        contagem_r++;
                                        /* Media no canal R */
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
                                    if ( (((j+k)*I->width + i + z) >= 0) && (((j+k)*I->width + i + z) <= ((I->width)*(I->height-1)+I->width-1)) ) {
                                        contagem_b++;
                                        /* Media no canal B */
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
                                    if ( (((j+k)*I->width + i + z) >= 0) && (((j+k)*I->width + i + z) <= ((I->width)*(I->height-1)+I->width-1)) ) {
                                        contagem_g++;
                                        /* Media no canal G */
                                        media_g = media_g + I->g[(j+k)*I->width + i + z] ;
                                    }
                                }
                            }
                        I->g[j*I->width + i] = media_g/contagem_g;
                    }
                }
            }
    }
