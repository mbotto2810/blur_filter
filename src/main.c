
#include "imageprocessing.h"
#define N 10

int main() {
  imagem img;
  img = abrir_imagem("data/lena.jpg");
  filtro(&img, N);
  salvar_imagem("out.jpg", &img);
  liberar_imagem(&img);
  return 0;
}
