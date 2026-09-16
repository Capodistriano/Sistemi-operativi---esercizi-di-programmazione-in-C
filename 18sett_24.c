/* Si realizzi un programma in C. Esso richiede all'utente di inserire il PID di un processo
e invia a tale processo un segnale di tipo SIGKILL. Il programma ripete questa operazione per sempre.
Nel caso l'utente prema CTRL +C sulla tastiera, il programma chiede all'utente,
tramite un messaggio testuale, se vuole terminare il programma. Se l'utente inserisce il carattere Y
il programma esce, se l'utente inserisce il carattere N il programma non esce (e riprende le normali operazioni).
In caso l'utente inserisca un altro carattere, il programma chiede nuovamente all'utente cosa fare (se uscire oppure no).
Si trascuri la gestione degli errori. */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void gestore(int sig){

    char scelta;

    while(1){

        printf("\nVuoi terminare il programma? (Y/N): ");
        scanf(" %c", &scelta);

        if(scelta=='Y' || scelta=='y')
            exit(0); //terminazione corretta

        if(scelta=='N' || scelta=='n')
            return; //esce dalla funzione gestore(), torna esattamente dove era stato interotto

        printf("Scelta non valida!\n");
    }
}

int main(){
    int pid;
    signal(SIGINT, gestore);
    //di base SIGINT(CTRL + C) termina; a meno che non ci sia un handler come in questo caso il gestore(SIGINT)
    
    while(1){
        printf("Inserisci PID: ");
        scanf("%d", &pid);

        kill(pid, SIGKILL); //invia al processo con PID ad es. 1234 il segnale SIGKILL che lo termna immediatamente
    }

    return 0;
}