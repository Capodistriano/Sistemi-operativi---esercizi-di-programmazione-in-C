#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//--------------------------------------------THREAD RITORNA UN *VOID--------------------------------

static void *threadFunc(void *arg){

    char *msg = (char*)arg;

    printf("From thread: %s", msg);

    int *ret = malloc(sizeof(int));

    *ret = strlen(msg);

    return ret; // equivalente a pthread_exit(ret)
}

int main(){

    pthread_t T1;

    void *res; // valore di ritorno del thread

    int s;

    // creazione del thread
    s = pthread_create(&T1, NULL, threadFunc, "Ciao mondo!\n");

    if(s != 0){
        printf("Non posso creare il thread.\n");
        exit(1);
    }

    printf("Messaggio dal main() :\n");

    /* main e threadFunc girano in parallelo -> i due messaggi 
    potrebbero essere inveriti
    Messaggio dal main()
    From thread: Ciao mondo!*/

    // attende la terminazione del thread; pthread_join vuole un void**, perche deve modificare res
    s = pthread_join(T1, &res); // simile a wait() nei processi

    if(s != 0){
        printf("Cannot join thread.\n");
        exit(1);
    }

    // stampa il valore ritornato dal thread
    printf("Thread ritornato %d\n", *((int*)res));

    free(res);

    return 0;
}