/*Si scriva un programma in C che riceve da riga di comando un certo numero di path di file. Il programma
concatena i file (escluso l’ultimo) riga per riga (separandoli con uno spazio), salvando il risultato nell’ultimo file.
I file in input non hanno lo stesso numero di righe; il programa termina quando (almeno) un file viene letto per
intero. I file non devono essere caricati interamente in memoria.
Si supponga che il numero massimo di argomenti che il programma puo ricevere sia la costante
MAX_FILES. Si supponga che ogni riga sia lunga massimo MAX_ROW
Si trascuri la gestione degli errori.*/

#include <stdio.h>
#include <string.h>
#define MAX_FILES 10
#define MAX_ROW 1024

int main(int argc, char *argv[]) {
    int n_input = argc - 2;
    FILE *fin[MAX_FILES];
    
    for (int i = 0; i < n_input; i++)
        fin[i] = fopen(argv[i + 1], "r");

    FILE *fout = fopen(argv[argc - 1], "w");

    char line[MAX_ROW];
    char result[MAX_ROW * MAX_FILES];

    while (1) {
        result[0] = '\0';

        int eof = 0;
        for (int i = 0; i < n_input; i++) {
            if (fgets(line, sizeof(line), fin[i]) == NULL) {
                eof = 1;
                break;
            }
            line[strcspn(line, "\n")] = '\0';
            if (i > 0) strcat(result, " "); /* aggiunge spazio tra le righe */
            strcat(result, line);
        }

        if (eof) break;

        fprintf(fout, "%s\n", result);
    }

    for (int i = 0; i < n_input; i++)
        fclose(fin[i]);
    fclose(fout);

    return 0;
}
