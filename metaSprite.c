#include <stdlib.h>
#include "graphics_processor.h"

int main() {
    int i;
    //linha superior
    for (i = 10000; i <= 10040; i++) {
        write_sprite_mem(7, 7, 0, i);
    }

    //linha inferior
    for (i = 10360; i <= 10400; i++) {
        write_sprite_mem(7, 7, 0, i);
    } 


    //lateral esquerda
    for (i = 10041; i <= 10341; i+=20) {
        write_sprite_mem(7, 7, 0, i);
    }


    set_sprite(1, 0, 0, 25, 1);
}