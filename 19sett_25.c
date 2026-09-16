/* Si scriva un programma in C che riceve come argomenti da riga di comando il path di un file e un numero intero
N. Il programma crea N processi figli, ognuno dei quali processa un sottoinsieme delle righe del file di input. In
particolare, il figlio i-esimo, processa le righe il cui numero di riga modulo N vale i. Ogni figlio cerca la riga di
lunghezza massima e fornisce tale lunghezza al padre tramite il valore di ritorno. Il padre, infine, stampa il valore
ritornato piu alto e il PID del figlio che l’ha fornito. Si supponga che ogni riga sia di massimo 1024 caratteri Si
trascuri la gestione degli errori. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_LINE 1024

int main(int argc, char *argv[]){

    char *path =argv[1];
    int N=atoi(argv[2]);

    pid_t pids[N];

    for(int i=0;i<N;i++){
        pids[i]= fork();

        if(pids[i]==0){
            //processa il figlio i-esimo
            FILE *fin= fopen(path, "r");
            char line[MAX_LINE];
            int riga=0;
            int max_len=0;

            while(fgets(line,MAX_LINE, fin) !=NULL){
                if(riga %N ==i){
                    int len=strlen(line);
                    if(len>max_len)
                      max_len=len;
                }
                riga++;
            }
            fclose(fin);
            exit(max_len); //restituisce la lunghezza massima al padre
        }
    }

    //Padre: aspetta tutti i figli e trova il massimo
    int best_len=0;
    pid_t best_pid=-1;

    for(int i=0; i<N;i++){
        int status;
        pid_t pid= waitpid(pids[i], &status, 0);
        int len=WEXITSTATUS(status);

        if(len>best_len){
            best_len=len;
            best_pid=pid;
        }
    }
    printf("La lunghezza massima: %d, PID figlio: %d\n", best_len, best_pid);
    return 0;
}
