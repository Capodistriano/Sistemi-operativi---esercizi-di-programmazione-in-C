/* Si scriva un programma in C che accetta il nome di un file come argomento. 
Il programma richiede all'utente di inserire due interi da tastiera A e B. 
Il programma stampa quindi a schermo i caratteri del file ricevuto come argomento a partire dal carattere A per una lunghezza B. 
Dopodichè il programma ritorna al passo precedente (chiedendo l'inserimento di due interi) a meno che B non valga 0.
In tal caso il programma termina stampando la coppia di valori A e B inseriti dall'utente con B maggiore.
Si eviti di leggere completamente il file se non necessario. Si trascuri la gestione degli errori.*/

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    int A, B;

    int maxA=0;
    int maxB=-1;

    char c;

    fp= fopen(argv[1], "r");
    
    while(1){
        printf("Inserisci A e B: ");
        scanf("%d %d", &A, &B);

        if(B>maxB){
            maxB=B;
            maxA=A;
        }

        if(B==0)
         break;
        
        fseek(fp, A, SEEK_SET);
        for(int i=0; i<B && (c= fgetc(fp)) != EOF; i++)
         putchar(c);
        
        printf("\n");
        fseek(fp, 0, SEEK_SET);


    }
    printf("Coppia con B massimo: (%d, %d)\n", maxA, maxB);
    fclose(fp);

    return 0;

}
