/*Si scriva un programma in C che accetti il nome di una file testuale come argomento. Il file contiene
un numero intero positivo per riga. Il programma crea un processo figlio per ogni numero, il quale ne
calcola e ne stampa a schermo il fattoriale. Si ricordi che il fattoriale di un numero `e il prodotto dei
numeri interi positivi minori o uguali a tale numero. Il programma attende la terminazione di tutti i
figli e poi stampa i) il numero più grande contenuto nel file e ii) il numero di riga al quale esso appare.
Si trascuri la gestione degli errori. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

long long fattoriale(int n){

    long long f =1;
    if(n==0 || n==1) //caso base
     return 1; //funzione termina subito restituendo 1

    for(int i=1; i<=n; i++){
        f= f*i;
    }
    return f;
}


int main(int argc, char * argv[]){
    FILE *fp;
    int n; //verrà letto ogni numero del file

    int max; //avrà il numero massimo trovato
    int riga_max =1; //numero della riga dove compare il massimo
    int riga=0; //righe lette

    fp= fopen(argv[1], "r");
    
    while(fscanf(fp, "%d", &n)==1){ //legge un intero dal file, il ciclo continua finché riesce a leggere un numero
        riga++; //incrementa il numero della riga corrente

        if(riga==1){ //se è la prima riga del file
            max=n; //il primo numero diventa il massimo provvisorio
            riga_max=1; //il massimo si trova alla prima riga
        }else if(n>max){ //per le righe successive
            max=n;
            riga_max=riga;
        }

        pid_t pid= fork(); // creo un nuovo processo figlio

        if(pid==0){ // solo figlio entra qui
            printf("Figlio %d: %d!= %lld\n", getpid(), n, fattoriale(n));
            exit(0); //il figlio termina immediatamente;
        }           //in questo modo non continua a leggere il file (operazione che deve fare solo il padre)
    }
    /*Finito il while, il padre ha:
      letto tutto il file;
      creato un figlio per ogni numero.*/

    fclose(fp);
    while(wait(NULL)>0); //il padre aspetta che tutti i figli terminino

    printf("\n Numero massimo: %d\n", max);
    printf("Riga del massimo: %d\n", riga_max);
    
    return 0;

}