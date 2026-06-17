#include<unistd.h>
#include<fcntl.h>

int main(int argc, char *argv[]){
    int fd_in;
    int fd_out;

    char c;
    fd_in= open(argv[1], O_RDONLY);
    fd_out= open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    off_t size;
    size=lseek(fd_in,0, SEEK_END);

    for(off_t i=size -1; i>=0;i--){
        lseek(fd_in,i,SEEK_SET);
        read(fd_in, &c,1);
        write(fd_out, &c, 1);
    }

    close(fd_in);
    close(fd_out);
    return 0;
}