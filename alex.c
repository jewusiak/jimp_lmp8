#include "alex.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

static int ln = 0;
static char ident[256];
static FILE *ci = NULL;

store dane;

char **fx_in_store;
int fx_in_store_Size = 0;

void alex_init4file(FILE *in) {
    ln = 0;
    ci = in;
}

static const char *keywords[] = {"default", "enum", "extern", "for", "if",
                                 "else", "int",
                                 "while",
                                 "break", "continue",
                                 "double", "float",
                                 "return", "char",
                                 "case", "const",
                                 "sizeof", "long",
                                 "short", "typedef",
                                 "switch",
                                 "void", "static",
                                 "struct"};

int isKeyword(char *str) {

    int i;
    for (i = 0; i < 24; i++)
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    return 0;

}


lexem_t alex_nextLexem(void) {
    int c;
    while ((c = fgetc(ci)) != EOF) {
        if (isspace(c) && c != '\n')
            continue;
        else if (c == '\n')
            ln++;
        else if (c == '(')
            return OPEPAR;
        else if (c == ')')
            return CLOPAR;
        else if (c == '{')
            return OPEBRA;
        else if (c == '}')
            return CLOBRA;
        else if (isalpha(c)) {
            int i = 1;
            ident[0] = c;
            while (isalnum(c = fgetc(ci)))
                ident[i++] = c;
            ident[i] = '\0';
            //dodano:
            if (ungetc(c, ci) == EOF)
                exit(-50);
            return isKeyword(ident) == 1 ? OTHER : IDENT;
        } else if (c == '"') {
            /* Uwaga: tu trzeba jeszcze poprawic obsluge nowej linii w trakcie napisu
               i \\ w napisie
            */
            char cp = 0;
            while ((c = fgetc(ci)) != EOF && (c != '"' || (cp == '\\' && c == '"')))
                cp = c;

            /*
             * Wykonuj dopóki:
             * != EOF i
             * (
             * c=" i cp=\ lub
             * c!="
             * )
             * */
            return c == EOF ? EOFILE : OTHER;
        } else if (c == '/') {
            if ((c = fgetc(ci)) != EOF) {
                if (c == '/') {
                    while ((c = fgetc(ci)) != EOF && c != '\n');
                } else if (c == '*') {
                    char cp = 0;
                    /*
                     * dopóki:
                     * !=EOF oraz
                     * !(cp==* oraz c==/)
                     * */

                    while ((c = fgetc(ci)) != EOF && !(cp == '*' && c == '/')) {
                        if (c == '\n')
                            ln++;
                        cp = c;
                    }
                }
            }
            //nie komentarz
            ungetc(c, ci);

            return OTHER;
        }
        if (isdigit(c) || c == '.') {
            /* liczba */
        } else {
            return OTHER;
        }
    }
    return EOFILE;
}

char *alex_ident(void) {
    return ident;
}

int alex_getLN() {
    return ln;
}

void add_uniq_fx(char *funame) {
    int i;
    for (i = 0; i < fx_in_store_Size; i++)
        if (strcmp(fx_in_store[i], funame) == 0)
            return;

    if (fx_in_store_Size++ == 0)
        fx_in_store = malloc(sizeof *fx_in_store);
    else
        fx_in_store = realloc(fx_in_store, fx_in_store_Size * sizeof *fx_in_store);
    fx_in_store[fx_in_store_Size - 1] = malloc((strlen(funame) + 1) * sizeof *fx_in_store);
    strcpy(fx_in_store[fx_in_store_Size - 1], funame);

}

void store_add_def(char *funame, int line, char *ipname) {
    if (dane.size++ == 0)
        dane.data = malloc(sizeof *dane.data);
    else
        dane.data = realloc(dane.data, dane.size * sizeof *dane.data);

    dane.data[dane.size - 1].type = malloc(4 * sizeof(char));
    strcpy(dane.data[dane.size - 1].type, "def");

    dane.data[dane.size - 1].funame = malloc((strlen(funame) + 1) * sizeof(*funame));
    strcpy(dane.data[dane.size - 1].funame, funame);

    dane.data[dane.size - 1].line = line;

    dane.data[dane.size - 1].ipname = malloc((strlen(ipname) + 1) * sizeof(*ipname));
    strcpy(dane.data[dane.size - 1].ipname, ipname);
    add_uniq_fx(funame);

}


void store_add_proto(char *funame, int line, char *ipname) {

    if (dane.size++ == 0)
        dane.data = malloc(sizeof *dane.data);
    else
        dane.data = realloc(dane.data, dane.size * sizeof *dane.data);

    dane.data[dane.size - 1].type = malloc(6 * sizeof(char));
    strcpy(dane.data[dane.size - 1].type, "proto");

    dane.data[dane.size - 1].funame = malloc((strlen(funame) + 1) * sizeof(*funame));
    strcpy(dane.data[dane.size - 1].funame, funame);

    dane.data[dane.size - 1].line = line;

    dane.data[dane.size - 1].ipname = malloc((strlen(ipname) + 1) * sizeof(*ipname));
    strcpy(dane.data[dane.size - 1].ipname, ipname);
    add_uniq_fx(funame);

}

void store_add_call(char *funame, int line, char *ipname) {
    if (dane.size++ == 0)
        dane.data = malloc(sizeof *dane.data);
    else
        dane.data = realloc(dane.data, dane.size * sizeof *dane.data);

    dane.data[dane.size - 1].type = malloc(5 * sizeof(char));
    strcpy(dane.data[dane.size - 1].type, "call");

    dane.data[dane.size - 1].funame = malloc((strlen(funame) + 1) * sizeof(*funame));
    strcpy(dane.data[dane.size - 1].funame, funame);

    dane.data[dane.size - 1].line = line;

    dane.data[dane.size - 1].ipname = malloc((strlen(ipname) + 1) * sizeof(*ipname));
    strcpy(dane.data[dane.size - 1].ipname, ipname);
    add_uniq_fx(funame);
}


void print_store() {
/*
int i;
    for(i=0;i<dane.size;i++)
        printf("%s(), typ: %s, linia: %d\n", dane.data[i].funame, dane.data[i].type, dane.data[i].line);
*/

    int i, j;
    for (i = 0; i < fx_in_store_Size; i++) {
        printf("Funkcja %s:\n", fx_in_store[i]);
        printf("\tPrototyp:\n");
        for (j = 0; j < dane.size; j++)
            if (strcmp(dane.data[j].type, "proto") == 0 && strcmp(dane.data[j].funame, fx_in_store[i]) == 0)
                printf("\t\tplik %s w linii %d\n", dane.data[j].ipname, dane.data[j].line);

        printf("\tDefinicja:\n");
        for (j = 0; j < dane.size; j++)
            if (strcmp(dane.data[j].type, "def") == 0 && strcmp(dane.data[j].funame, fx_in_store[i]) == 0)
                printf("\t\tplik %s w linii %d\n", dane.data[j].ipname, dane.data[j].line);

        printf("\tUzycie:\n");
        for (j = 0; j < dane.size; j++)
            if (strcmp(dane.data[j].type, "call") == 0 && strcmp(dane.data[j].funame, fx_in_store[i]) == 0)
                printf("\t\tplik %s w linii %d\n", dane.data[j].ipname, dane.data[j].line);
    }
}