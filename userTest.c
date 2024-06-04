#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char write_buf[64] = {"r: 1, g: 2, b: 3"}; // cada char tem 8 bits


int main() {
    int fd;
    if ((fd = open("/dev/graphicProcessor", O_RDWR)) == -1){
        printf("Error opening /dev/GP: %s\n", strerror(errno));
        return -1;
    }

   // write(fd, write_buf, strlen(write_buf));

    int bytesWritten = write(fd, write_buf, strlen(write_buf));

    printf("%d bytes written successfully!\n", bytesWritten);

    close(fd);
    return 0;

}
