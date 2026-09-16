/* Si scriva un programma in C che riceve il path di un file da riga di comando. 
Il file è testuale e per ogni riga contiene un numero intero N seguito da N stringhe separate da spazi.
Ad esempio una riga può essere: 3 ciao al mondo. Per ogni riga, il programma crea un processo figlio per stringa. 
Ogni figlio esegue in parallelo ai suoi fratelli e verifica se la sua stringa è palindroma.
Il programma attende che tutti i figli terminino e poi passa alla riga successiva del file in input.
Il programma stampa infine il numero di stringhe palindrome trovate.
Indicazioni per la soluzione:
- Si legga il file di input solo tramite la funzione fscanf.
- Si utilizzi il valore di ritorno dei figli per comunicare al padre se la stringa è palindroma.
- Si supponga che ogni stringa sia al massimo di 256 caratteri.
- Si trascuri la gestione degli errori e l'include delle librerie. */

#include <stdio.h>      // FILE, fopen, fscanf, fclose, printf
#include <stdlib.h>     // exit
#include <string.h>     // strlen
#include <unistd.h>     // fork
#include <sys/wait.h>   // wait, WEXITSTATUS

#define MAX_STR 256

/* restituisce 1 se la stringa è palindroma */
int palindroma(char *s) {
    int len = strlen(s);
    for (int i= 0; i < len/2; i++) {
        if (s[i] != s[len - 1 - i])
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {

    /* apre il file passato come argomento */
    FILE *fp = fopen(argv[1], "r");
    int totale_palindrome = 0;

    while (1) {
        int N;

        /* legge il numero N all'inizio della riga; se fallisce siamo a fine file */
        if (fscanf(fp, "%d", &N) != 1)
            break;

 
        /* per ogni stringa della riga: la legge e crea un processo figlio */
        for (int j= 0; j < N; j++) {
            char parola[MAX_STR + 1];

            /* legge la stringa — fscanf si ferma agli spazi, legge una parola alla volta */
            fscanf(fp, "%s", parola);

            pid_t pid = fork();

            if (pid == 0) {
                /* codice del figlio: comunica l'esito al padre tramite il valore di exit */
                if (palindroma(parola))
                    exit(1); /* 1 = palindroma */
                else
                    exit(0); /* 0 = non palindroma */
            }
            /* il padre non fa nulla qui: i figli girano in parallelo */
        }

        /* attende tutti gli N figli della riga corrente prima di passare alla prossima */
        for (int j= 0; j < N; j++) {
            int status;
            wait(&status);
            /* WEXITSTATUS estrae il valore passato a exit() dal figlio (0 o 1) */
            totale_palindrome = totale_palindrome + WEXITSTATUS(status);
        }
    }

    fclose(fp);
    printf("Numero totale di stringhe palindrome: %d\n", totale_palindrome);

    return 0;
}
