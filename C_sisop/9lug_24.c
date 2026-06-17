#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    DIR *dir;

    struct dirent *entry;
    struct stat st;

    char maxfile[1024];
    char path[1024];

    off_t maxsize = -1;

    dir=opendir(argv[1]);

    while((entry= readdir(dir)) != NULL){
        //ignoro . ed ..
        if(strcmp(entry->d_name, ".")==0 ||
           strcmp(entry-> d_name, "..")==0)
            continue;

        
        int len =strlen(entry-> d_name);

        //ignoro i file .gz
        if(len >=3 &&
           strcmp(entry->d_name+ len-3, ".gz")==0)
            continue;

        sprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);
        stat(path, &st);

        if(S_ISREG(st.st_mode) && st.st_size > maxsize){
            maxsize= st.st_size;
            strcpy(maxfile, path);
        }
    }

    closedir(dir);

    pid_t pid= fork();
    if(pid==0){
        execlp("gzip", "gzip", maxfile, (char*)NULL);
        exit(1);
    }
    wait(NULL);
    return 0;


}