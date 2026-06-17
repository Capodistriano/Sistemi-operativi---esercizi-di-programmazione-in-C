#include <signal.h>
#define MAX_NUM 2147483647

int contatore_primi=0;

//handler per SIGUSR1
void gestore_usr1(int sig){
    contatore_primi++;
}

//handler per SIGINT
void gestore_int(int sig){
    printf("Totale numeri primi trovati: %d\n", contatore_primi);
    exit(0);
}

int primo(int n){
    int i, isPrime=1;

    // I numeri minori o uguali a 1 non sono primi
    if(n<=1){
        isPrime=0;
    }else{
        for(i=2;i<=sqrt(n);i++){
            if(n%i==0){
                isPrime=0;
                break;
            }
        }
    }
    return isPrime;
}


int main(int argc, char *argv[]){
    int N= atoi(argv[1]);
    signal(SIGUSR1, gestore_usr1);
    signal(SIGINT, gestore_int);

    int i;

    for(i=0;i<N;i++){
        pid_t pid=fork();
        if(pid==0){

            //codice eseguito dal figlio
            while(1){
                int P=rand();
                if(primo(P)){
                    printf("Figlio %d: %d\n", getpid(), P);
                    kill(getppid(), SIGUSR1);
                }
            }
        }
    }

    //padre in attesa perpetua

    while(1)
     pause();
    
    return 0;


}