#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PATH 256
#define MAX_CMD 512 // lunghezza massima del comando inserito dall'utente
#define MAX_STR 100000 // dimensione massima della stringa risultato

int main(int argc, char *argv[]){
    int i;

    // Apro il file passato da riga di comando
    FILE *fp= fopen(argv[1], "r");

    // Stringa che conterrà tutti i caratteri estratti
    char risultato[MAX_STR];

    // Indice della prossima posizione libera in risultato
    int pos=0;

    // Buffer per memorizzare il path letto da file
    char path[MAX_PATH+1];

    // Estremi dell'intervallo di caratteri da leggere
    int A,B;

    // Legge una riga del tipo:
    // path A B
    while(fscanf(fp,"%s %d %d",path, &A, &B)==3){
        // Apro il file indicato nella riga corrente
        FILE *f = fopen(path, "r");

        int i;
        int c; // carattere letto

        // mi sposto fino alla posizione A
        for(i=0; i<A;i++) {c= fgetc(f);}
            

        // Leggo i caratteri da A a B inclusi

        for(int i=A; i<=B; i++){
            
            // Legge un carattere dal file
            c=fgetc(f);

            // Se raggiungo la fine del file, esco
            if(c==EOF) break;
            
            // Copio il carattere nella stringa finale
            risultato[pos++]=c;

        }

        // chiudo il file corrente
        fclose(f);
    }
    // Aggiungo il terminatore di stringa
    risultato[pos]= '\0';

    // chiudo il file contenente le istruzioni
    fclose(fp);

    // Buffer che conterrà il comando dell'utente
    char commando[MAX_CMD];

    // Legge una riga da tastiera
    gets(commando);
    
    // Caso 1: l'utente ha scritto "V"
    if(strcmp(commando, "V")==0){
        
        // stampa la riga costruita
        printf("%s\n", risultato);
    }
    
    // Caso 2: l'utente ha scritto "F path"
    else if(commando[0]=='F'){
        // Buffer per il path del file di destinazione
        char outpath[MAX_PATH+1];
        
        // Estrae il path dal comando
        // Esempio:
        // "F output.txt"
        sscanf(commando, "F %s", outpath);

        // Apre il file di destinazione in scrittura
        FILE *out= fopen(outpath, "w");

        // Scrive la stringa nel file
        fputs(risultato, out);
        
        // chiude il file
        fclose(outpath);
        
    }

    // Caso 3: l'utente ha scritto "Q"
    else if(strcmp(commando, "Q")==0){

        //termina senza fare nulla
        return 0;
    
    }
    // fine del programma
    return 0;

}

