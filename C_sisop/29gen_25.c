#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

#define MAX_LINES 100
#define MAX_PATH 256

int main(int argc, char *argv[]){
    FILE *f;

    char path[MAX_PATH];

    pid_t pid; 
    pid_t figli[MAX_LINES];
    int n_figli=0;

    f=fopen(argv[1], "r");
    while(fgets(path, MAX_PATH,f)!= NULL){
        path[strcspn(path, "\n")] = '\0';
        pid=fork();

        if(pid==0){
            FILE *fnum;
            int numero;
            int somma=0;

            fnum=fopen(path, "r");
            while(fscanf(fnum, "%d", &numero)==1){
                somma=somma+numero;
            }
            fclose(fnum);
            printf("SOMMA:%s:%d\n", path, somma);
            exit(0);
        }

        figli[n_figli]=pid;
        n_figli++;
    }

    fclose(f);
    printf("PID generati: \n");
    for(int i=0;i<n_figli;i++){
        printf("%d\n", figli[i]);
    }

    for(int i=0;i<n_figli;i++){
        wait(NULL);
    }

    return 0;

}