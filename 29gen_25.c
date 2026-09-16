/*Si scriva un programma in C che accetti un argomento dalla linea di comando. L’argomento rappresenta
un file che contiene il path di un file per riga. Il programma crea un processo per ogni path. Ogni
processo legge il corrispondente file, il quale contiene un numero intero per riga e ne calcola la somma,
stampando la stringa: SOMMA:nomefile:somma sostituendo a nomefile e somma rispettivamente il nome
del file e la somma che ha calcolato. I vari processi devono eseguire in parallelo. Infine il programma
stampa l’elenco dei PID del processi generati. Si supponga che il file fornito come argomento abbia
massimo MAX_LINES righe e ogni riga sia lungha al massimo MAX_PATH caratteri. Si trascuri la gestione
degli errori.*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

#define MAX_LINES 100
#define MAX_PATH 256

int main(int argc, char *argv[]){
    FILE *f; //puntatore al file che contiene la lista dei path 

    char path[MAX_PATH]; //buffer, per percorso path per volta memorizzato

    pid_t pid; // conterrà il valore restituito da fork()
    pid_t figli[MAX_LINES]; // array che memorizza i PID di tutti i processi figli creati
    int n_figli=0;

    f=fopen(argv[1], "r");
    while(fgets(path, MAX_PATH,f)!= NULL){ //legge una riga del file; ogni riga ha un path
        path[strcspn(path, "\n")] = '\0'; // elimina il carattere di "a capo" (\n) che fgets() inserisce nella stringa.
        /*restituisce la posizione del primo \n.
         Poi quella posizione viene sostituita con '\0'  ossia il teminatore di stringa*/


        pid=fork(); //creo un nuovo processo

        if(pid==0){ //solo figlio
            FILE *fnum; //puntatore al file contenente numeri
            int numero; //variabile dove leggere ogni intero
            int somma=0;

            fnum=fopen(path, "r"); //apre il file indicato da path
            while(fscanf(fnum, "%d", &numero)==1){ //legge un numero alla volta
                somma=somma+numero;
            }
            fclose(fnum);
            printf("SOMMA:%s:%d\n", path, somma);
            exit(0); /* Termina il processo figlio
                        È importante. Se mancasse, il figlio continuerebbe 
                        ad eseguire il codice del padre, creando altri figli.*/
        }
        //Solo il PADRE esegue questo
        figli[n_figli]=pid; //Salva il PID del nuovo figlio nell'array

        n_figli++; // Aggiorna il numero dei figli creati.
        /*Il ciclo ricomincia.
        Il padre legge il path successivo
        e crea un altro figlio.*/ 
    }

    fclose(f); //Chiude il file contenente i percorsi.
    printf("PID generati: \n");
    for(int i=0;i<n_figli;i++){ //Scorre tutti i PID memorizzati
        printf("%d\n", figli[i]);
    }
    
    //Attesa dei figli
    for(int i=0;i<n_figli;i++){
        wait(NULL); //Ripete wait() tante volte quanti sono i figli
        /*Aspetta che un figlio termini.
          Non importa quale.
          Ripetendolo n_figli volte il padre aspetta tutti i processi.*/
    }

    return 0;
}