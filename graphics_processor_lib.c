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

int set_background_color(int R, int G, int B);
int set_sprite(int reg, int x, int y, int offset, int activation_bit);
int set_background_block(int endereco_memoria, int R, int G, int B);
int define_poligon(int forma, int R, int G, int B, int tamanho, int x, int y, int endereco);
int write_sprite_mem(int R, int G, int B, int endereco_memoria);

int set_background_color(int R, int G, int B) {
    int fd;
    unsigned char buffer[MAX_SIZE];
    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1) {
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

    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1) {
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

    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1) {
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

    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1) {
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

    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1) {
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    sprintf(buffer, "%d %d %d %d %d", WSM, R, G, B, endereco_memoria);
    int bytesWritten = write(fd, buffer, strlen(buffer));

    close(fd);
    return bytesWritten;
}
