#include <stdio.h>
int main(int argc, char *argv[]){
    FILE *f;
    char buffer[100];

    if(argc!=2){
        printf("Uso: ./stampa path\n");
        return 1;
    }

    f=fopen(argv[1], "r");
    if(f==NULL){
        printf("Impossibile aprire il file\n");
        return 1;
    }

    while(fgets(buffer,100,f)!=NULL)
    printf("%s",buffer);

    fclose(f);
    return 0;
}