#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define WBR 1
#define WBM 2
#define DP 3
#define WSM 4
#define MAX_SIZE 32

// prototipos
int set_background_color(int R, int G, int B);
int set_sprite(int reg, int x, int y, int offset, int activation_bit);
int set_background_block(int endereco_memoria, int R, int G, int B);
int define_poligon(int forma, int R, int G, int B, int tamanho, int x, int y, int endereco);
int write_sprite_mem (int R, int G, int B, int endereco_memoria);


int main() {

    //int bytesWritten = set_background_color(100, 245, 345);
    //int bytesWritten = set_sprite (1, 320, 445, 9, 1);
    //int bytesWritten = set_background_block(5, 3, 255, 0, 0);
    //printf("%d bytes escritos\n", bytesWritten);

    //   //Azul claro (ceu)    set_cor_background_wbr(6, 4, 3)
    // cor da grama: 1,7,1



    //verde escuro 1 6 1
    set_background_color(1 ,4, 7);
    
    //set_background_block(0, 3, 6, 0); teste de cor verde olivia

    //grama 
    int i;
    for (i = 4000; i < 4800; i++) {
        set_background_block(i, 1, 6, 0);
    }

    //patinhas
    define_poligon(0, 1, 6, 0, 1, 200, 402, 0); //patinha 1
    define_poligon(0, 1, 6, 0, 1, 260, 402, 1); //patinha 2
    //set_background_block(3947, 1, 7, 1); //3951

    //entre as patas
    for (i = 3946; i < 3952; i++){
       set_background_block(i, 0, 7, 0);
    }

    //rabinho
    set_background_block(3863, 0, 7, 0); 

    //pele acima da pata
    for (i = 3864; i < 3874; i++) {
        set_background_block(i, 7, 3, 3);
    }
    
    //3794 cabeça (1 bloco mais a cima da pele)


    //set_background_block(3793, 7, 2, 1);

    //casco até 3793 -> primeira linha casco
    for (i = 3784; i < 3794; i++) {
        set_background_block(i, 5, 2, 2);
    }

    //->segunda linha casco
    set_background_block(3700, 6, 4, 2);
    
    /*
    set_background_block(0, 4, 2, 2); //lilás
    set_background_block(2, 6, 4, 2);
    set_background_block(6, 7, 2, 1);
    set_background_block(8, 6, 3, 1);
    set_background_block(10, 7, 2, 2); //laranja
    set_background_block(12, 5, 3, 2); //verde limão
    set_background_block(14, 5, 2, 2); //marrom
    set_background_block(16, 6, 3, 2); 
    set_background_block(18, 4, 2, 2); */
    



    //define_poligon(0, 7, 3, 3, 1, 150, 325, 4);
    //set_background_block(0, 2, 3, 1);
    //set_background_block(1, 0, 7, 0);
    //casco
    //define_poligon(0, 1, 6, 0, 1, 200, 402, 0); 
    
    //g b r
    //define_poligon(0, 7, 3, 3, 1, 260, 280, 5);
   

     //primeira linha: 0 - 78
    //segunda linha: 80 + 78 = 158
    //0 - 4799
    //set_background_block(4001, 1, 7, 1);
    

}

int set_background_color(int R, int G, int B) {
    int fd;
    unsigned char buffer[MAX_SIZE];
    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1){
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    sprintf(buffer, "%d %d %d %d %d %d %d %d %d", WBR, R, G, B, 0x0000, 0, 0, 0, 0);
    int bytesWritten = write(fd, buffer, strlen(buffer));

    close(fd);
    return bytesWritten;
}

int set_sprite(int reg, int x, int y, int offset, int activation_bit) {
    int fd;
    unsigned char buffer[MAX_SIZE];
    
    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1){
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    sprintf(buffer, "%d %d %d %d %d %d %d %d %d", WBR, 0, 0, 0, reg, x, y, offset, activation_bit);
    int bytesWritten = write(fd, buffer, strlen(buffer));

    close(fd);
    return bytesWritten;

}

int set_background_block(int endereco_memoria, int R, int G, int B) {
    int fd;
    unsigned char buffer[MAX_SIZE];

    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1){
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    sprintf(buffer, "%d %d %d %d %d", WBM, endereco_memoria, R, G, B);
    int bytesWritten = write(fd, buffer, strlen(buffer));

    close(fd);
    return bytesWritten;
}

int define_poligon(int forma, int R, int G, int B, int tamanho, int x, int y, int endereco) {
    int fd;
    unsigned char buffer[MAX_SIZE];

    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1){
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    sprintf(buffer, "%d %d %d %d %d %d %d %d %d", DP, forma, R, G, B, tamanho, x, y, endereco);
    int bytesWritten = write(fd, buffer, strlen(buffer));

    close(fd);
    return bytesWritten;
}

int write_sprite_mem(int R, int G, int B, int endereco_memoria) {
    int fd;
    unsigned char buffer[MAX_SIZE];

    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1){
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    sprintf(buffer, "%d %d %d %d %d", WSM, R, G, B, endereco_memoria);
    int bytesWritten = write(fd, buffer, strlen(buffer));

    close(fd);
    return bytesWritten;
}
