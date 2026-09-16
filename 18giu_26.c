/* Si scriva un programma in C che riceve da riga di comando il path di un file. 
Questo file contiene dei dati in formato space-separated values, ovvero una tabella in cui ogni riga è una entry
e le colonne sono separate da spazi. La prima riga contiene (separati da spazio) il numero delle colonne e i loro nomi.
Le righe successive contengono i dati, i quali sono numeri decimali.
Il programma stampa, per ogni colonna, il nome, il valore minimo, medio e massimo.
Il file non deve essere caricato interamente in memoria. 
Si consideri la funzione int feof (FILE *stream) che ritorna 1 se il cursore di un file è posizionato alla sua fine, altrimenti 0. 
Il numero delle colonne non è noto e non si deve supporre un numero massimo di esse. 
Il valore minimo e massimo che può assumere un double è DBL MIN e DBL MAX, rispettivamente.
Si trascurino la gestione degli errori.
Si consideri, ad esempio, il file:
2 tempo punti
0.4 10
0.6 20
0.2 30
Il programma stampa:
tempo:
min=0.2 max=0.6 media=0.4
punti:
min=10 max=30 media=20 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");

    int ncol;
    fscanf(fp, "%d", &ncol);

    double *min= malloc(ncol * sizeof(double));
    double *max= malloc(ncol * sizeof(double));
    double *somma= malloc(ncol * sizeof(double));
    char buffer[256];

    /* prima passata: legge i nomi e li scarta, inizializza min/max/somma */
    for (int i = 0; i < ncol; i++) {
        fscanf(fp, "%s", buffer);
        min[i]   = DBL_MAX;
        max[i]   = -DBL_MAX;
        somma[i] = 0;
    }

    long nrighe = 0;
    double x;

    /* legge tutti i valori riga per riga */
    while (!feof(fp)) {
        for (int i = 0; i < ncol; i++) {
            if (fscanf(fp, "%lf", &x) != 1) goto fine; /* fine file o errore */
            if (x < min[i])   min[i] = x;
            if (x > max[i])   max[i] = x;
            somma[i] += x;
        }
        nrighe++;
    }
    fine:

    fclose(fp);

    /* seconda passata: rilegge solo i nomi per stamparli */
    fp = fopen(argv[1], "r");
    fscanf(fp, "%d", &ncol);

    for (int i = 0; i < ncol; i++) {
        fscanf(fp, "%s", buffer);
        printf("%s:\nmin=%lf max=%lf media=%lf\n\n",
               buffer, min[i], max[i], somma[i] / nrighe);
    }

    fclose(fp);
    free(min);
    free(max);
    free(somma);

    return 0;
}