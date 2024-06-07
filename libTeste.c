#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define WBR 1
#define WSM 2
#define DP 3

//char write_buf[64]; // cada char tem 8 bits
int set_background_color(int R, int G, int B);

int main() {

   // write(fd, write_buf, strlen(write_buf));

    //int bytesWritten = write(fd, write_buf, strlen(write_buf));

    int bytesWritten = set_background_color(1, 2, 3);
    printf("%d bytes written successfully!\n", bytesWritten);

    return 0;

}

int set_background_color(int R, int G, int B) {
    int fd;
    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1){
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    char buffer[10] = {WBR, (char)R, (char)G, (char)B, 0, 0, 0, 0, 0};
    int bytesWritten = write(fd, buffer, sizeof(buffer));

    close(fd);
    return bytesWritten;
}

int set_sprite(int reg, int x, int y, int offset, int activation_bit) {
    int fd;
    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1){
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    char buffer[10] = {WBR, 0, 0, 0, (char)reg, (char)x, (char)y, (char)offset, (char)activation_bit};
    int bytesWritten = write(fd, buffer, sizeof(buffer));

    close(fd);
    return bytesWritten;

}

int set_background_block(int column, int line, int R, int G, int B) {
    int fd;
    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1){
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    char buffer[10] = {WSM, (char)column, (char)line, (char)R, (char)G, (char)B};
    int bytesWritten = write(fd, buffer, sizeof(buffer));

    close(fd);
    return bytesWritten;
}

int define_poligono(int forma, int R, int G, int B, int tamanho, int x, int y) {
    int fd;
    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1){
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

    char buffer[10] = {DP, (char)forma, (char)R, (char)G, (char)B, (char)tamanho, (char)x, (char)y};
    int bytesWritten = write(fd, buffer, sizeof(buffer));

    close(fd);
    return bytesWritten;
}
