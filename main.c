#include <stdlib.h>
#include "graphics_processor.h"

int main() {

    /**
     * Chamada das funções para setar elementos e realizar o desenho
     * 
     * Desenhos: grama, tartaruga,casa, sol e sprites de árvores.
    */

    // Céu
    set_background_color(1, 4, 7);

    // Grama
    int i;
    for (i = 4000; i < 4800; i++) {
        set_background_block(i, 1, 6, 0);
    }

    /*    TARTARUGA     */
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
  
    // MENOR REGISTRADOR FICA POR CIMA


    //define_poligon(int forma, int R, int G, int B, int tamanho, int x, int y, int endereco);


    // CASA
    //  Telhado
    define_poligon(1, 6, 3, 2, 15, 460, 220, 4);

    // Casa
    define_poligon(0, 7, 7, 7, 13, 460, 350, 3);

    //  Porta
    define_poligon(0, 0, 0, 0, 3, 460, 400, 5);

    // SOL
    define_poligon(0, 7, 7, 0, 5, 50, 50, 6);

    //SPRITES: árvore
    set_sprite(1, 300, 385 , 4, 1);
    set_sprite(2, 100, 385 , 4, 1);
    set_sprite(3, 50, 430 , 4, 1);
    set_sprite(4, 220, 450 , 4, 1);
    set_sprite(5, 560, 430 , 4, 1);


    return 0;
}
