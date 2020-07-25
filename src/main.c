
#include "imageprocessing.h"
#define N 7

int main() {
  imagem img;
  img = abrir_imagem("data/cachorro.jpg");
  filtro(&img, N);
  salvar_imagem("cachorro-out.jpg", &img);
  liberar_imagem(&img);
  return 0;
}
