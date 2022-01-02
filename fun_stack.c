#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fun_stack.h"

fun_db stos;

int top_of_funstack(void) {
    if (stos.size == 0) {
        return 0;
    }
    return (stos.data[stos.size - 1].par_level);
}

void put_on_fun_stack(int par_level, char *funame) {
    if (stos.size++ == 0)
        stos.data = malloc(sizeof *stos.data);
    else
        stos.data = realloc(stos.data, stos.size * sizeof *stos.data);
    stos.data[stos.size - 1].funame = malloc((strlen(funame) + 1) * sizeof *funame);
    stos.data[stos.size - 1].par_level = par_level;
    strcpy(stos.data[stos.size - 1].funame, funame);
}

char *get_from_fun_stack(void) {
    if (stos.size == 0) {
        fprintf(stderr, "Próba dostania się do stosu o indeksie <0!\n");
        exit(50);
    }

    char *kopia = malloc((strlen(stos.data[stos.size - 1].funame) + 1) * sizeof *kopia);
    strcpy(kopia, stos.data[stos.size - 1].funame);

    stos.data = realloc(stos.data, --stos.size * sizeof *stos.data);
    return kopia;
}