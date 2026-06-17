#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
    pid_t pid;
    pid=fork();
    if(pid==0){
        printf("Sono l figlio \n");
    }else{
        printf("Sono il padre \n");
    }
    return 0;
}

//------------------------------------

void Figlio(void);
void Padre(void);

int main(){

    pid_t pid;
    pid=fork();

    if(pid==0)
     Figlio();
    else
     Padre();

}

void Figlio(void){
    for(int i=0;i<10;i++){

        usleep(200);
        printf("\t Sono il figlio. i= %d\n", i);

    }
}

void Padre(void){
    for(int i=0;i<10;i++){

        usleep(250);
        printf(" Sono il figlio. i= %d\n", i);

    }
}


//-------------------------------------- 1. ESERCIZIO IMPLEMENTAZIONE DI WAIT-FORK

int main(){
    pid_t pid;
    printf("T1\n");
    pid=fork();
    if(pid==0){
        printf("T3\n");
        return 0;
    }else{
        printf("T2\n");
        wait ((int*)0); //passa a wait un puntatore che vale zero, non punta a nessuna memoria, ----NULL----
    }
    printf("T4\n");
    return 0;
}

//-------------------------------------- 2. ESERCIZIO IMPLEMENTAZIONE DI WAIT-FORK (Chrome)


int main(){
    pid_t pid;
    printf("T1- Inizio\n");
    pid=fork();

    if(pid==0){
        printf("T3- DNS b.com\n");
        pid_t pid2;
        pid2=fork();
        if(pid2==0){
            printf("T6- DNS b.com\n");
            return 0;

        }else{
            printf("T5- HTTP http://b.com/2\n");
            wait((int*)0); // attendo che termini T6
            return 0;

        }

        

    }else{
        printf("T2- DNS a.com\n");
        printf("T4- HTTP http://a.com/\n");
        wait((int*)0); //attendo che terminino T3 e T5       


    }

    printf("T7- Utilizzo i risultati\n");
    return 0;
}