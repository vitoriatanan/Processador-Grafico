#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "./address_map_arm.h"

#define LW_BRIDGE_SPAN 0x00005000
#define LW_BRIDGE_BASE 0xFF200000
#define data_a_base 0x80
#define data_b_base 0x70
#define start 0xc0

int set_background_color(int R, int G, int B, volatile int* data_a,  volatile int* data_b) {
    *data_a = (0x0000 | 0x00000); //opcode para WBR e endereço do registrador
    *data_b = (R << 2) | (G << 4) | B; // cor rosa
    return 1;
}

int main() {
    volatile int* data_a_ptr;
    volatile int* data_b_ptr;
    volatile int *start_ptr;
    //volatile int *data_a_ptr, *data_b_ptr;
    int fd = -1;
    void *LW_virtual;

    if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        return(-1);
    }

    LW_virtual = mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
    if (LW_virtual == MAP_FAILED) {
        printf("ERROR: mmap() failed...\n");
        close(fd);
        return(-1);
    }

    data_a_ptr = (int *) (LW_virtual + data_a_base);
    data_b_ptr = (int *) (LW_virtual + data_b_base);
    start_ptr = (int *) (LW_virtual + start);


    set_background_color(7, 2, 3, data_a_ptr, data_b_ptr); 
    *start_ptr = 1; //ativa
    
    *start_ptr = 0; //reinicia
    set_background_color(4, 2, 3, data_a_ptr, data_b_ptr); 
    *start_ptr = 1; //ativa

    //set_background_color(1, 0, 1, data_a_ptr, data_b_ptr);

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
