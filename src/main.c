
#include "imageprocessing.h"
#define N 3

int main() {
  imagem img;
  img = abrir_imagem("data/cachorro.jpg");
  unsigned int media_r, media_g, media_b;
  media_r = media_g = media_b = 0;

  for (unsigned int i=0; i<(img.width); i++) {
    for (unsigned int j=0; j<(img.height); j++) {
        media_r = media_g = media_b = 0;

        for (int k=-N; k<=N; k++) {
            for (int z=-N; z<=N; z++) {
                if ( (((j+k)*img.width + i + z) >= 0) && (((j+k)*img.width + i + z) <= ((img.width)*(img.height-1)+img.width-1)) ) {

                    /* Media no canal R */
                    media_r += img.r[(j+k)*img.width + i + z] / ((2*N+1)*(2*N+1));
                    /* Media no canal G */
                    media_g += img.g[(j+k)*img.width + i + z] / ((2*N+1)*(2*N+1));
                    /* Media no canal B */
                    media_b += img.b[(j+k)*img.width + i + z] / ((2*N+1)*(2*N+1));

                    }
                }
            }

        img.r[j*img.width + i] = media_r;
        img.g[j*img.width + i] = media_g;
        img.b[j*img.width + i] = media_b;

        }
    }

  salvar_imagem("cachorro-out.jpg", &img);
  liberar_imagem(&img);
  return 0;
}
