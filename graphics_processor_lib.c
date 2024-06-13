#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define WBR 1
#define WBM 2
#define DP 3

// prototipos
int set_background_color(int R, int G, int B);
int set_sprite(int reg, int x, int y, int offset, int activation_bit);
int set_background_block(int column, int line, int R, int G, int B);
int define_poligon(int forma, int R, int G, int B, int tamanho, int x, int y);


int main() {


    //int bytesWritten = set_background_color(100, 245, 345);
    int bytesWritten = set_sprite (1, 320, 445, 9, 1);
    //int bytesWritten = set_background_block(5, 3, 255, 0, 0);
    printf("%d bytes written successfully!\n", bytesWritten);

    return 0;

}

int set_background_color(int R, int G, int B) {
    int fd;
    unsigned char buffer[23];
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
    unsigned char buffer[30];
    
    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1){
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    sprintf(buffer, "%d %d %d %d %d %d %d %d %d", WBR, 0, 0, 0, reg, x, y, offset, activation_bit);
    int bytesWritten = write(fd, buffer, strlen(buffer));

    close(fd);
    return bytesWritten;

}

int set_background_block(int column, int line, int R, int G, int B) {
    int fd;
    unsigned char buffer[20];

    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1){
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    sprintf(buffer, "%d %d %d %d %d %d", WBM, column, line, R, G, B);
    int bytesWritten = write(fd, buffer, strlen(buffer));

    close(fd);
    return bytesWritten;
}

int define_poligon(int forma, int R, int G, int B, int tamanho, int x, int y) {
    int fd;
    unsigned char buffer[20];

    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1){
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    sprintf(buffer, "%d %d %d %d %d %d %d %d", DP, forma, R, G, B, tamanho, x, y);
    int bytesWritten = write(fd, buffer, strlen(buffer));

    close(fd);
    return bytesWritten;
}
