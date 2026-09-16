/*Si scriva un programma in C che riceve come argomenti da riga di comando due path e numero intero N. 
Il programma legge il file al primo path riga per riga e salva nel secondo path le righe lette, ma in ordine casuale.
Per ottenere un ordinamento casuale, si effettuino scambi tra due righe scelte a caso. 
Si effettui un numero di scambi pari al numero di righe lette.
Per generare un numero casuale si usi la funzione di libreria int rand (void) 
che ritorna un numero tra 0 e la costante RAND MAX (che vale 2147483647). 
Si supponga che le righe siano esattamente N (terzo argomento) e che ogni riga sia lunga massimo 512 caratteri.
Non si sovradimensioni vettori dove non strettamente necessario. Si trascuri la gestione degli errori*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 512

int main(int argc, char *argv[]){
    char *path_in=argv[1];
    char *path_out=argv[2];
    int N= atoi(argv[3]);

    // Alloco un array di N righe, ognuna lunga MAX_LINE
    char righe[N][MAX_LINE];

    // leggo le righe dal file in input
    FILE *fin=fopen(path_in, "r");
    for(int i=0;i<N;i++){
        fgets(righe[i], MAX_LINE, fin);
    }
    fclose(fin);

    //eseguo N scambi casuali
    for(int i=0; i<N; i++){
        int a= rand() % N;
        int b= rand() % N;

        char temp[MAX_LINE];
        strcpy(temp, righe[a]);
        strcpy(righe[a], righe[b]);
        strcpy(righe[b], temp);
    }

    //scrivo le righe mescolate nel file di output
    FILE *fout= fopen(path_out, "w");
    for(int i=0;i<N;i++){
        fprintf(fout, "%s", righe[i]);
    }
    
    fclose(fout);
    return 0;
}