
#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H


typedef struct {
  unsigned int width, height;
  float *r, *g, *b;
} imagem;

imagem abrir_imagem(char *nome_do_arquivo);
imagem abrir_imagem_mmap(char *nome_do_arquivo);
void salvar_imagem(char *nome_do_arquivo, imagem *I);
void liberar_imagem(imagem *i);
void liberar_imagem_mmap(imagem *I);
void filtro(imagem *I, int N);
void multi_filtro(imagem *I, int N, int n);

#endif
