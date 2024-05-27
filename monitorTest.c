#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "auxFiles/address_map_arm.h"

#define dataA_BASE 0x80
#define dataB_BASE 0x70

int set_background_color(int R, int G, int B, volatile int *dataA,  volatile int *dataB) {
    *dataA = (0x0000 | 0x00000); //opcode para WBR e endereço do registrador
    *dataB = (R << 16) | (G << 8) | B; // cor rosa

    return 1;
}

int main() {
    volatile int * dataA_ptr;
    volatile int * dataB_ptr;
    int fd = -1;
    void *LW_virtual;

    if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        return(-1);
    }

    LW_virtual = mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BBRIDGE_BASE);
    if (LW_virtual == MAP_FAILED) {
        printf("ERROR: mmap() failed...\n");
        close(fd);
        return(-1);
    }

    dataA_ptr = (int *) (LW_virtual + dataA_BASE);
    dataB_ptr = (int *) (LW_virtual + dataB_BASE);

    set_background_color(7, 2, 3, dataA_ptr, dataB_ptr);

    if (munmap (LW_virtual, LW_BRIDGE_SPAN) != 0) {
        printf("ERROR: munmap() failed...\n");
        return(-1);
    }
    
    close(fd);
    return 0;
}
    // WBR
/*
    opcode -> 0000
    register -> 00000 São 32 registradores, sendo o primeiro reservado para o armazenamento da cor de background da tela
    dataA -> opcode e registrador (0000 e 00000)
    dataB -> dados a serem armazenados (RGB)
*/
