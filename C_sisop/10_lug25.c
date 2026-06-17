#include <unistd.h>     // read, write, lseek, close
#include <fcntl.h>      // open
#include <sys/types.h>  // off_t
#define BUF_SIZE 1;

int main(int argc, char * argv[]){

    int fd_in= open(argv[1], O_RDONLY);

    int fd_out= open(argv[2], O_WRONLY | O_CREAT| O_TRUNC, 0644);

    char c;

    // ottiene la dimensione del file
    off_t size= lseek(fd_in,0, SEEK_END);

    off_t i;

    // scorre il file dall'ultimo byte fino al primo
    for(i=size-1;i>=0;i--){

        //Posiziona il cursore sul byte i-esimo
        lseek(fd_in,i,SEEK_SET);

        /* Legge un byte */
        read(fd_in, &c,1);
         /* Lo scrive nel file di output */
        write(fd_out, &c,1);
    }

    close(fd_in);
    close(fd_out);
    
    return 0;

}