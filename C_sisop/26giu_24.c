/*Si scriva un programma in C che accetti il nome di una file testuale come argomento. Il file contiene
un numero intero positivo per riga. Il programma crea un processo figlio per ogni numero, il quale ne
calcola e ne stampa a schermo il fattoriale. Si ricordi che il fattoriale di un numero `e il prodotto dei
numeri interi positivi minori o uguali a tale numero. Il programma attende la terminazione di tutti i
figli e poi stampa i) il numero pi`u grande contenuto nel file e ii) il numero di riga al quale esso appare.
Si trascuri la gestione degli errori. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

long long fattoriale(int n){

    long long f =1;
    if(n==0 || n==1)
     return 1;

    for(int i=1; i<=n; i++){
        f= f*i;
    }
    return f;
}



int main(int argc, char * argv[]){
    FILE *fp;
    int n;

    int max;
    int riga_max =1;
    int riga=0;

    fp= fopen(argv[1], "r");
    
    while(fscanf(fp, "%d", &n)==1){
        riga++;

        if(riga==1){
            max=n;
            riga_max=1;
        }else if(n>max){
            max=n;
            riga_max=riga;
        }

        pid_t pid= fork();

        if(pid==0){
            printf("Figlio %d: %d!= %lld\n", getpid(), n, fattoriale(n));
            exit(0);
        }
    }

    fclose(fp);
    while(wait(NULL)>0);

    printf("\n Numero massimo: %d\n", max);
    printf("Riga del massimo: %d\n", riga_max);
    
    return 0;

}