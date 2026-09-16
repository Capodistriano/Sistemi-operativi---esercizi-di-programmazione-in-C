/*Si scriva un programma in C che riceve da riga un numero arbitrario di path di file. 
Il programma crea un processo figlio per ogni path di file. I processi lavorano in parallelo. 
Ogni processo figlio legge un file, in quale contiene in forma testuale un numero intero per riga. 
Il processo scrive tali numeri in formato binario in file <path>.bin (e.g., se il processo legge f.txt, scrive f.txt.bin).
Il processo padre attende la terminazione di tutti i figli e poi termina. Non si facciano ipotesi sul numero massimo di argomenti passati al programma. 
Si trascurino la gestione degli errori.*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){

    for(int i=1; i<argc; i++){
        pid_t pid= fork();
        if(pid==0){
            FILE *fp= fopen(argv[i], "r");

            char destinazione[1024];
            sprintf(destinazione, "%s.bin", argv[i]);
            FILE *fout= fopen(destinazione, "wb");

            int num;
            while(fscanf(fp, "%d", &num)==1){
                fwrite(&num, sizeof(int), 1, fout);
            }
            fclose(fp);
            fclose(fout);
        
            exit(0);
            
        }
    }

    for(int i=1; i<argc; i++){
        wait(NULL);
    }
    
    return 0;
}

