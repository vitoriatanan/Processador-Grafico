#include <stdlib.h>
#include "graphics_processor.h"

int main() {


    //   //Azul claro (ceu)    set_cor_background_wbr(6, 4, 3)
    // cor da grama: 1,7,1

    // verde escuro 1 6 1
    // ceu azul
    set_background_color(1, 4, 7);

    // set_background_block(0, 3, 6, 0); teste de cor verde olivia

    // grama
    int i;
    for (i = 4000; i < 4800; i++) {
        set_background_block(i, 1, 6, 0);
    }

    // patinhas
    define_poligon(0, 1, 6, 0, 1, 200, 402, 0); // patinha 1
    define_poligon(0, 1, 6, 0, 1, 260, 402, 1); // patinha 2
    // set_background_block(3947, 1, 7, 1); //3951

    // entre as patas
    for (i = 3946; i < 3952; i++) {
        set_background_block(i, 0, 7, 0);
    }

    // rabinho
    set_background_block(3863, 0, 7, 0);

    // pele acima da pata
    for (i = 3864; i < 3874; i++) {
        set_background_block(i, 7, 3, 3);
    }

    // CASCO
    for (i = 3784; i < 3794; i++) {
        set_background_block(i, 5, 2, 2);
    }

    for (i = 3704; i < 3714; i++) {
        set_background_block(i, 5, 2, 2);
    }

    for (i = 3625; i < 3633; i++) {
        set_background_block(i, 5, 2, 2);
    }

    for (i = 3546; i < 3552; i++) {
        set_background_block(i, 5, 2, 2);
    }

    for (i = 3467; i < 3471; i++) {
        set_background_block(i, 5, 2, 2);
    }

    // CABEÇA
    for (i = 3874; i < 3877; i++) {
        set_background_block(i, 0, 7, 0);
    }
    for (i = 3794; i < 3798; i++) {
        set_background_block(i, 0, 7, 0);
    }
    for (i = 3714; i < 3718; i++) {
        set_background_block(i, 0, 7, 0);
    }

    for (i = 3634; i < 3637; i++) {
        set_background_block(i, 0, 7, 0);
    }

    // olho
    set_background_block(3716, 0, 0, 0);

    // TELHADO
    define_poligon(1, 6, 3, 2, 15, 460, 220, 2);

    // CASA
    define_poligon(0, 7, 7, 7, 13, 460, 350, 5);

    define_poligon(0, 7, 5, 2, 2, 460, 405, 4);
    // define_poligon(0, 1, 1, 1, 2, 460, 405, 3);

    // MENOR REGISTRADOR FICA POR CIMA

    // porta
}