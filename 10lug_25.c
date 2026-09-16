/* Si scriva un programma in C che riceve un intero positivo N da riga di comando.
Il programma crea N processi figli e poi entra in un'attessa perpetua.
Ogni processo figlio, in un ciclo infinito, estrare un numero casuale P e verifica se esso è un numero primo. 
Se esso è un numero primo, lo stampa e invia un segnale di tipo SIGUSR1 al padre.
Quando l'utente preme CTRL+C sulla tastiera (inviando al padre un segnale di tipo SIGINT),
il processo padre stampa il numero di totale di numeri primi trovati da tutti i figli e termina.
Indicazioni per la soluzione:
• Per generare un numero casuale si usi la funzione di libreria int rand(void) che ritorna un numero tra 0 e la costante RAND MAX (che vale 2147483647).
• Si trascuri la gestione degli errori e l'include delle librerie. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int totale = 0;

void gestore_usr1(int sig) {
    totale++;
}

void gestore_int(int sig) {
    printf("Totale numeri primi: %d\n", totale);
    exit(0);
}

int primo(int n) {

    if (n < 2)
        return 0;

    for (int i = 2; i < n; i++) {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

int main(int argc, char *argv[]) {

    int N = atoi(argv[1]);

    signal(SIGUSR1, gestore_usr1);
    signal(SIGINT, gestore_int);

    for (int i = 0; i < N; i++) {

        pid_t pid = fork();

        if (pid == 0) {

            while (1) {

                int P = rand();

                if (primo(P)) {
                    printf("%d\n", P);
                    kill(getppid(), SIGUSR1);
                }
            }
        }
    }

    while (1)
        pause();

    return 0;
}