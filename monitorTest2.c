#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "./address_map_arm.h"

/*
#define LW_BRIDGE_SPAN 0x00005000
#define LW_BRIDGE_BASE 0xFF200000
#define data_a_base 0x80 //DATA_A
#define data_b_base 0x70 //DATA_B
#define WERREG 0xc0 //start*/

//
void escrita_buffer(volatile int* wrreg_ptr) {
    *wrreg_ptr = 1;
    *wrreg_ptr = 0;
}

//define cor do background
int set_background_color (int R, int G, int B, volatile int* data_a,  volatile int* data_b, volatile int* wrreg) {
    *data_a = 0x0000; //opcode para WBR e endereço do registrador
    *data_b = (B << 6) | (G << 4) | R;
    
    escrita_buffer(wrreg);
    return 1;
}

//seta um sprite
int set_sprite (int registrador, int x, int y, int offset, int activation_bit, volatile int* data_a, volatile int* data_b, volatile int* wrreg) {
    *data_a = (registrador << 4) | 0x0000;
    *data_b = (activation_bit << 29) | (x << 19) | (y << 9) | offset;
    
    escrita_buffer(wrreg);
    return 1;
}

//edita um bloco no background 80x60
int set_background_block (int column, int line, int R, int G, int B, volatile int* data_a, volatile int* data_b, volatile int* wrreg) {
    //Calcula o endereço de memória do bloco com base na coluna e linha
    int endereco_memoria = (line * 80 + column); // 80: numero de colunas por linha = 245

    *data_a = (endereco_memoria << 4) | 0b0010;
    *data_b = (B << 6) | (G << 4) | R;

    escrita_buffer(wrreg);
    return 1;
}

int dp (int forma, int R, int G, int B, int tamanho, int x, int y, volatile int* data_a, volatile int* data_b, volatile int* wrreg) {
    *data_a = (0b0) | 0b0011;
    *data_b = (forma << 31) | (B << 28) | (G << 25) | (R << 22) | (tamanho << 18) | (y << 9) | x;
    escrita_buffer(wrreg);
    return 1;
}

int main() {
    volatile int* data_a_ptr;
    volatile int* data_b_ptr;
    //volatile int* start_ptr;
    volatile int* wrreg_ptr;    

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

    data_a_ptr = (int *) (LW_virtual + DATA_A_BASE);
    data_b_ptr = (int *) (LW_virtual + DATA_B_BASE);
    wrreg_ptr = (int *) (LW_virtual + WERREG);


    //cor DarkMagenta
    set_background_color (255, 20, 147, data_a_ptr, data_b_ptr, wrreg_ptr);
    
    //sprite coração
    set_sprite (1, 320, 445, 9, 1, data_a_ptr, data_b_ptr, wrreg_ptr);

    //edita um bloco para laranja
    set_background_block (5, 3, 255, 0, 0, data_a_ptr, data_b_ptr, wrreg_ptr);

    dp (1, 0, 255, 0, 15, 500, 260, data_a_ptr, data_b_ptr, wrreg_ptr);

    //0, 255, 255 ceu azul
    

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

