#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr,
                "Uso: %s file1.txt file2.txt ... output.txt\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }

    int n_input = argc - 2;

    FILE **fin = malloc(n_input * sizeof(FILE *)); // fin è un puntatore al primo elemento di un array di FILE *
    if (fin == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n_input; i++)
    {
        fin[i] = fopen(argv[i + 1], "r");
        if (fin[i] == NULL)
        {
            perror(argv[i + 1]);
            exit(EXIT_FAILURE);
        }
    }

    FILE *fout = fopen(argv[argc - 1], "w");
    if (fout == NULL)
    {
        perror(argv[argc - 1]);
        exit(EXIT_FAILURE);
    }
    // buffer per una riga
    // contiene una riga letta da file (es.: ciao | line = "ciao\n")
    char line[MAX_LINE]; 
    
    // buffer per la concatenazione
    char result[MAX_LINE * n_input];

    while (1)
    {
        result[0] = '\0'; // svuoto la stringa risultato , sarabbe come fare result= "". Setto il buffer vuoto

        int eof = 0; // nessun file terminato

        for (int i = 0; i < n_input; i++)
        {
            if (fgets(line, sizeof(line), fin[i]) == NULL)
            {
                eof = 1;
                break;
            }

            line[strcspn(line, "\n")] = '\0';

            strcat(result, line);
        }

        if (eof)
            break;

        fprintf(fout, "%s\n", result);
    }

    for (int i = 0; i < n_input; i++)
        fclose(fin[i]);

    fclose(fout);
    free(fin);

    return 0;
}