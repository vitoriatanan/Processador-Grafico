#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WBR      1
#define WBM      2
#define DP       3
#define WSM      4

#define MAX_SIZE 32

// Função para definir a cor de fundo usando valores RGB
int set_background_color(int R, int G, int B);

// Função para definir as propriedades de um sprite
int set_sprite(int reg, int x, int y, int offset, int activation_bit);

// Função para definir um bloco de fundo
int set_background_block(int endereco_memoria, int R, int G, int B);

// Função para definir um polígono
int define_poligon(int forma, int R, int G, int B, int tamanho, int x, int y, int endereco);

// Função para escrever um sprite na memória
int write_sprite_mem(int R, int G, int B, int endereco_memoria);


int set_background_color(int R, int G, int B) {
    int fd;
    unsigned char buffer[MAX_SIZE]; // Buffer que prepara um comando para configurar a cor de fundo com os valores fornecidos
    // Abre o dispositivo gráfico para leitura e escrita
    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1) {
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1; // Se falhar, imprime um erro e retorna -1
    }

    // Prepara o comando para configurar a cor de fundo
    sprintf(buffer, "%d %d %d %d %d %d %d %d %d", WBR, R, G, B, 0x0000, 0, 0, 0, 0);
    int bytesWritten = write(fd, buffer, strlen(buffer)); // Escreve o comando no dispositivo

    close(fd); // Se falhar, imprime um erro e retorna -1
    return bytesWritten;
}

int set_sprite(int reg, int x, int y, int offset, int activation_bit) {
    int fd;
    unsigned char buffer[MAX_SIZE];

    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1) {
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    // Prepara o comando para configurar o sprite
    sprintf(buffer, "%d %d %d %d %d %d %d %d %d", WBR, 0, 0, 0, reg, x, y, offset, activation_bit);
    int bytesWritten = write(fd, buffer, strlen(buffer)); // Escreve o comando no dispositivo

    close(fd);
    return bytesWritten;
}

int set_background_block(int endereco_memoria, int R, int G, int B) {
    int fd;
    unsigned char buffer[MAX_SIZE];

    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1) {
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    // Prepara o comando para configurar o background block
    sprintf(buffer, "%d %d %d %d %d", WBM, endereco_memoria, R, G, B);
    int bytesWritten = write(fd, buffer, strlen(buffer)); // Escreve o comando no dispositivo

    close(fd);
    return bytesWritten;
}

int define_poligon(int forma, int R, int G, int B, int tamanho, int x, int y, int endereco) {
    int fd;
    unsigned char buffer[MAX_SIZE];

    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1) {
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    // Prepara o comando para configurar o polígono
    sprintf(buffer, "%d %d %d %d %d %d %d %d %d", DP, forma, R, G, B, tamanho, x, y, endereco);
    int bytesWritten = write(fd, buffer, strlen(buffer)); // Escreve o comando no dispositivo

    close(fd);
    return bytesWritten;
}

int write_sprite_mem(int R, int G, int B, int endereco_memoria) {
    int fd;
    unsigned char buffer[MAX_SIZE];

    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1) {
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }
    
    // Prepara o comando para escrever o sprite na memória
    sprintf(buffer, "%d %d %d %d %d", WSM, R, G, B, endereco_memoria);
    int bytesWritten = write(fd, buffer, strlen(buffer)); // Escreve o comando no dispositivo

    close(fd);
    return bytesWritten;
}
