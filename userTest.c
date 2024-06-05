#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char write_buf[64]; // cada char tem 8 bits
int set_background_color(int fd, int R, int G, int B);

int main() {
    int fd;
    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1){
        printf("Error opening /dev/graphicProcessor: %s\n", strerror(errno));
        return -1;
    }

   // write(fd, write_buf, strlen(write_buf));

    //int bytesWritten = write(fd, write_buf, strlen(write_buf));


    int bytesWritten = set_background_color(fd, 1, 2, 4);
    printf("%d bytes written successfully!\n", bytesWritten);

    close(fd);
    return 0;

}

int set_background_color(int fd, int R, int G, int B) {
    sprintf(write_buf, "%d %d %d", R, G, B);
    int bytesWritten = write(fd, write_buf, strlen(write_buf));
    return bytesWritten;
}
