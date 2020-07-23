
#include "imageprocessing.h"
#define N 4

int main() {
  imagem img;
  img = abrir_imagem("data/lena.jpg");
  filtro(&img, N);
  salvar_imagem("cachorro-out.jpg", &img);
  liberar_imagem(&img);
  return 0;
}
