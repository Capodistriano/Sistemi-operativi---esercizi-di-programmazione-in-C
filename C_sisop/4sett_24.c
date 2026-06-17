#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h> // 1. MANCAVA: Necessario per strcspn

#define MAX_LINES 100
#define MAX_PATH 256

typedef struct {
    char path[MAX_PATH];
    long somma;
} dati_thread;

void *worker(void *arg) {
    dati_thread *d = (dati_thread*) arg; // 2. CORRETTO: c'era una virgola invece del punto e virgola

    FILE *fp = fopen(d->path, "r");
    if (fp == NULL) { // 3. AGGIUNTO: Controllo se il file non esiste
        perror("Errore apertura file nel thread");
        d->somma = 0;
        return NULL;
    }

    int n;
    d->somma = 0;
    while (fscanf(fp, "%d", &n) == 1) {
        d->somma = d->somma + n;
    }

    fclose(fp);
    return NULL;
}

int main(int argc, char * argv[]) {
    // 4. AGGIUNTO: Controllo che sia stato passato il file di input
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <file_lista>\n", argv[0]);
        return 1;
    }

    FILE *lista = fopen(argv[1], "r");
    if (lista == NULL) { // 5. AGGIUNTO: Controllo apertura file lista
        perror("Errore apertura file lista");
        return 1;
    }

    pthread_t tid[MAX_LINES];
    dati_thread dati[MAX_LINES];

    int n_files = 0;
    // 6. OTTIMIZZATO: Evita buffer overflow se la lista ha più di 100 righe
    while (n_files < MAX_LINES && fgets(dati[n_files].path, MAX_PATH, lista) != NULL) {
        dati[n_files].path[strcspn(dati[n_files].path, "\n")] = '\0';
        n_files++;
    }

    fclose(lista);

    // 7. CORRETTO: I cicli devono essere SEPARATI per avere parallelismo!
    
    // FASE 1: Avvia tutti i thread in parallelo
    for (int i = 0; i < n_files; i++) {
        pthread_create(&tid[i], NULL, worker, &dati[i]);
    }

    // FASE 2: Attendi che TUTTI abbiano finito e accumula il totale
    long totale = 0;
    for (int i = 0; i < n_files; i++) {
        pthread_join(tid[i], NULL);
        totale = totale + dati[i].somma;
    }

    printf("Somma totale = %ld\n", totale);
    return 0;
}
