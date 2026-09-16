/* Si scriva un programma in C che riceve da riga di comando il path di un certo numero di file testuali
(ad esempio, il programma potrebbe essere eseguito col comando ./programma filel.txt file2.txt). 
Il programma crea un processo figlio per ogni file. Ogni processo figlio legge il file
e stampa a schermo il numero di righe vuote che esso contiene. 
Il processo padre attende la terminazione di tutti i figli e poi termina. 
La dimensione massima di ogni riga è 4096 caratteri, mentre è ignoto il numero di file passato come argomento al programma. 
Si trascuri la gestione degli errori */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 4096

int main(int argc, char *argv[]){

    for(int i=1;i<argc;i++){
        pid_t pid= fork();

        if(pid==0){
            FILE *fp=fopen(argv[i], "r");
            char line[MAX_LINE+1];
            int righe_vuote= 0;

            while(fgets(line, sizeof(line), fp) !=NULL){
                //Una riga è vuota se contiene solo '\n'

                if(strcmp(line, '\n')==0)
                 righe_vuote++;
                
                printf("File %s: %d righe vuote \n", argv[i], righe_vuote);
                fclose(fp);
                exit(0);
            }

            //il padre aspetta che tutti i figli terminino
            for(int i=1;i<argc;i++){
                wait(NULL);
                return 0;
            }
        }
    }
    
    return 0;
}