#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void gestore(int sig){
    char scelta;
    while(1){
        printf("Vuoi terminare il programma? (Y/N)");
        scanf("%c", &scelta);

        if(scelta== 'Y' || scelta == 'y'){
            exit(0);
        }

        if(scelta == 'N' || scelta == 'n'){
            return;
        }
        printf("Scelta non valida.\n");
    }
}

int main(){
    int pid;
    signal(SIGINT, gestore);
    
    while(1){
        printf("Inserisci PID: ");
        scanf("%d", &pid);

        kill(pid, SIGKILL);
    }

    return 0;
}