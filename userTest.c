#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int8_t write_buf[64]; // cada char tem 8 bits


int main() {
    int fd;
    fd = open("/dev/GP", O_RDWR);
    if (fd < 0) {
        return 0;
    }
    write_buf = "r: 1, g: 2, b: 3";
    bytes_written = write(fd, write_buf, strlen(write_buf)+1);

    close(fd);

}