#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

void cptOneFile(char* filePath) {
    char buf[512];
    int fd, n;
    unlink(filePath);
    fd = open(filePath, O_CREATE | O_RDWR);
    while((n = read(0, buf, sizeof(buf))) > 0) {
        if (write(fd, buf, n) != n) {
            printf(0, "write error\n");
            close(fd);
            return;
        }
    }
    if(n < 0){
        printf(0, "read error\n");
        close(fd);
        return;
    }
    printf(0, "\nDone!\n");
    close(fd);
    return;

}

void cptTwoFile(char* firstFilePath, char* secondFilePath) {
    char buf[512];
    int fd1, fd2, n;
    fd1 = open(firstFilePath, O_RDWR);
    if(fd1 >= 0) {
        unlink(secondFilePath);
        fd2 = open(secondFilePath, O_CREATE | O_RDWR);
        while((n = read(fd1, buf, sizeof(buf))) > 0) {
            if (write(fd2, buf, n) != n) {
                printf(0, "write error\n");
                close(fd1);
                close(fd2);
                return;
            }
        }
        if(n < 0){
            printf(0, "read error\n");
            close(fd1);
            close(fd2);
            return;
        }
        printf(0, "\nDone!\n");
        close(fd1);
        close(fd2);
        return;
    } else {
        printf(0, "The file path to read the text from doesn't exist!!!\n");
        close(fd1);
        return;
    }
}

int main(int argc, char *argv[])
{
    if(argc == 2){
        cptOneFile(argv[1]);
        exit();
    }
    else if(argc == 3){
        cptTwoFile(argv[1], argv[2]);
        exit();
    }
    else {
        
    }
    exit();
}