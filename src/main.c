
#include "imageprocessing.h"
#define N 5

int main() {
  imagem img;
  img = abrir_imagem("data/lena.jpg");
  filtro(&img, N, 0, 0);
  salvar_imagem("out.jpg", &img);
  liberar_imagem(&img);
  return 0;
}
