#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define MAXSLEEP 5
#define THREADNUM 10

static void * SleepFun(void *arg){
    
    // converte il parametro generico in char*
    // poi prende il carattere puntato
    char thread_number= *((char*)arg);
    // numero casuale tra 0 e MAXSLEEP-1
    int n=rand() % MAXSLEEP; // 0 <= n < MAXSLEEP | al massimo MAXSLEEP -1 secondi
    // sospende il thread per n secondi
    sleep(n);
    // stampa il thread terminato
    printf("Thread %c terminato dopo %d seconds. \n", thread_number, n);
    return NULL;

}

int main(int argc, char * argv[]){
    
    // array di thread
    pthread_t T1 [THREADNUM];
    // array contenente i nomi dei thread
    char names[THREADNUM];
    
    // creazione thread
    for(int i=0;i<THREADNUM;i++){
        
        // genera A B C D ...
        names[i]= 'A'+ i;
        // crea il thread
        pthread_create(&T1[i], NULL, SleepFun, &names[i]); // &names[i]== &c | char c= 'A' +i 
    }
    
    // attende tutti i thread
    for(int i=0;i<THREADNUM;i++){
        pthread_join(T1[i], NULL); // ne fara 10 thread e che terminino
    }
    return 0; // si suicida
}
