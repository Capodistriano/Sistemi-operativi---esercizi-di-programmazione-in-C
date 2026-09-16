/* Si scriva un programma in C che riceve da riga di comando tre numeri interi A, B e C. Il programma deve trovare
e stampare tutti i numeri primi tra A e B utilizzando, in parallelo, C processi figli. 
Il padre attende la terminazione dei processi figli e stampa quanti numeri primi sono stati trovati.
Si trascurino la gestione degli errori. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int primo(int n){
    if(n<0)
     return 0;
    
    for(int i=2; i*i<= n; i++){
        if(n%i==0)
         return 0;
    }

    return 1;
}

int main(int argc, char *argv[]){
    int A= atoi(argv[1]);
    int B= atoi(argv[2]);
    int C= atoi(argv[3]);

    int ampiezza= (B-A+1)/ C;
    int totale =0;

    for(int i=0; i<C; i++){

        pid_t pid= fork();
        
        if(pid==0){
            int inizio= A+ i* ampiezza;
            int fine;

            /* L'ultimo figlio controlla anche gli eventuali numeri rimasti */
            if(i==C-1)
             fine= B;
            else
             fine= inizio + ampiezza -1;
            
            int contatore=0;

            for(int n= inizio; n<= fine; n++){
                if(primo(n)){
                    printf("Figlio %d: %d è primo\n", i, n);
                    contatore++;
                }
            }
            exit(contatore);
        }
    }
    for(int i=0; i< C; i++){

        int status;
        wait(&status);
        totale= totale+ WEXITSTATUS(status);
    }
    printf("Numero totale di primi trovati: %d\n", totale);
    return 0;
}

