/* Si scriva un programma in C il quale riceve il path di una cartella p come argomento da riga di comando.
Il programma legge il contenuto del file binario / etc/numbers.bin. Il file / etc/numbers.bin 
contiene un numero intero L seguito da una lista di L interi positivi. 
Il programma carica in memoria la lista di L interi positivi. Il programma controlla nella cartella p 
se esistono file regolari che appartengono a uno degli utenti il cui user ID è contenuto nella lista di L interi positivi. 
Per tali file, il programma ne stampa il nome e user ID proprietario. Si trascuri la gestione degli errori.*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>


int presente(uid_t uid, int *lista, int L){
    int i;
    for(i=0;i<L;i++){
        if(lista[i]==uid)
         return 1;
    }
    return 0;

}

int main(int argc, char *argv[]){
    //apertura del file binario
    FILE *fp=fopen("/etc/numbers.bin", "rb");

    int L;

    //legge il numero di UID
    fread(&L, sizeof(int),1 ,fp);

    //alloca il vettore
    int *lista=malloc(L*sizeof(int));

    //legge i L interi
    fread(lista, sizeof(int), L, fp);
    fclose(fp);

    //apre la directory passata da riga di comando
    DIR *dir=opendir(argv[1]);

    struct dirent *entry;

    while((entry = readdir(dir)) != NULL){
        char path[1024];

        // costrusico il path completo
        sprintf(path, " %s/%s", argv[1], entry -> d_name);

        struct stat st;

        stat(path , &st);

        // controlla se è un file regolare
        if(S_ISREG(st.st_mode)){
            // controlla se l'UID è nella lista
            if(presente(st.st_uid, lista, L)){
                printf("File: %s UID: %d\n", entry->d_name, (int)st.st_uid);
            }
        }


    }
    
    closedir(dir);
    free(lista);
    return 0;
}
