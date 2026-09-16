/*Si scriva un programma in C che accetti un argomento dalla linea di comando. L’argomento rappresenta
un file che contiene il path di un file per riga. Il programma crea un thread per ogni path. Ogni thread
legge il corrispondente file, il quale contiene un numero intero per riga e ne calcola la somma. Infine il
programma stampa la somma totale tra tutti i file. Si supponga che il file fornito come argomento abbia
massimo MAX_LINES righe e ogni riga sia lungha al massimo MAX_PATH caratteri. Si trascuri la gestione
degli errori.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h> // Necessario per strcspn
#define MAX_LINES 100
#define MAX_PATH 256

int tot_sum=0; //variabile globale -- somma totale di tutti i file
pthread_mutex_t mutex;

void *thread_function(void *arg){
    char *path= (char *) arg;
    
    FILE *fp=fopen(path, "r");

    int numero;
    int somma=0;

    while(fscanf(fp, "%d", &numero)==1)
     somma=somma+numero;
    
    fclose(fp);

    pthread_mutex_lock(&mutex);
    tot_sum=tot_sum+somma;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char * argv[]){

    FILE *lista= fopen(argv[1], "r");
    
    char path[MAX_LINES][MAX_PATH];
    pthread_t tid[MAX_LINES];

    int n=0;

    while(fscanf(lista, "%s",path[n])==1)
     n++;

    fclose(lista);
    pthread_mutex_init(&mutex, NULL);

    for(int i=0;i<n;i++)
     pthread_create(&tid[i],NULL, thread_function,path[i]);
    
    for(int i=0;i<n;i++)
     pthread_join(tid[i],NULL);

    printf("Somma totale= %d\n", tot_sum);
    
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
