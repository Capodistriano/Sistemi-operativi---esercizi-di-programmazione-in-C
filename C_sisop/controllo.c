#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_not_integer(const char *str) {
    char *endptr;
    strtol(str, &endptr, 10);  // Prova a convertire in intero base 10

    // Se endptr non punta al terminatore, c'erano caratteri non numerici
    return *endptr != '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso corretto: %s input\n", argv[0]);
        return 1;
    }

    if (is_not_integer(argv[1])) {
        printf("'%s' NON è un intero.\n", argv[1]);
    } else {
        printf("'%s' è un intero valido.\n", argv[1]);
    }

    return 0;
}
