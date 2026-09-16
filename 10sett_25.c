/*Si scriva un programma in C che riceve come argomento da riga di comando il path di un file, nel quale,
in ogni riga, è riportato il path di un file testuale e due numeri interi positivi A e B. Il programma processa 
ogni riga e svolge la seguente operazione: legge dal file indicato i caratteri dal numero A al numero B (incluso). 
I caratteri sono numerati a partire da 0. Ad esempio, se una riga contiene /tmp/a.txt 1 3, il programma legge da /tmp/a.txt il secondo, 
il terzo e il quarto carattere. Il programma memorizza tutti i caratteri letti in un'unica stringa e infine chiede all'utente di inserire
un comando da riga di comando (per semplicità, si usi la funzione di libreria gets()).
Si trascuri la gestione degli errori e l'include delle librerie. Ogni path può avere lunghezza massima 256 caratteri.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_PATH 256
#define MAX_CMD 512
#define MAX_STRING 10000

int main(int argc, char * argv[]){

    FILE *fp_lista;
    FILE *fp_file;

    char path[MAX_PATH];

    int A;
    int B;

    char risultato[MAX_STRING];
    risultato[0]= '\0';

    fp_lista= fopen(argv[1], "r");
    while(fscanf(fp_lista, "%s %d %d", path, &A, &B)==3){
        fp_file=fopen(path, "r");
        fseek(fp_file, A, SEEK_SET);
        
        for(int i=A; i<=B; i++){
            char c;
            
            if(fread(&c, sizeof(char),1,fp_file)==1){
                int len=strlen(risultato);
                
                risultato[len]=c;
                risultato[len+1]='\0';
            }
        }
        fclose(fp_file);
    }

    fclose(fp_lista);

    char comando[MAX_CMD];
    gets(comando);
    if(strcmp(comando, "V")==0){
        printf("%s\n", risultato);
    }else if(comando[0]== 'F'){
        char outpath[MAX_PATH];
        sscanf(comando, "F %s", outpath);

        FILE *out= fopen(outpath, "w");
        fprintf(out, "%s", risultato);
        fclose(out);
    }else if(strcmp(comando, "Q")==0)

    return 0;
}
