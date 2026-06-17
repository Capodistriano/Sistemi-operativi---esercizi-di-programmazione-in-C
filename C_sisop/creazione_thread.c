#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//--------------------------------------------THREAD RITORNA UN *VOID--------------------------------


static void * threadFunc(void *arg){
    printf("From thread: %s", (char*)arg);
    int *ret=malloc(sizeof(int));
    *ret=strlen(arg);
    return ret;  // Valore di ritorno del thread. Equivale a pthread_exit(ret)
}

int main(int argc, char *argv[]){
    pthread_t T1;
    void *res; // per il valore di ritorno
    int s;

    s= pthread_create(&T1,NULL, threadFunc, "Ciao mondo!\n"); // creazione del thread
    
    if(s!=0){
        printf("Non posso creare il thread.\n");
        exit(1);
    }

    printf("Messaggio dal main() :\n");
    s= pthread_join(T1,&res); // JOIN richiede un void**, ossia &res

    if(s!=0){
        printf("Cannot join thread.\n");
        exit(1);
    }

    printf("Thread ritornato %d\n", *((int*)res)); // utilizzo del valore di ritorno

    free(res);
    exit(0);

}


