#include "alex.h"

#include <ctype.h>
#include <string.h>

static int ln = 0;
static char ident[256];
static FILE *ci = NULL;

void alex_init4file(FILE *in) {
    ln = 0;
    ci = in;
}

int isKeyword(char *str){
    char *keywords[]={"default", "enum","extern", "for", "if",
                      "else",  "int",
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
    int i;
    for(i=0;i<24; i++)
        if(strcmp(str, keywords[i])==0)
            return 1;
    return 0;

}


lexem_t alex_nextLexem(void) {
    int c;
    while ((c = fgetc(ci)) != EOF) {
        if (isspace(c))
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
            return isKeyword(ident) ? OTHER : IDENT;
        } else if (c == '"') {
            /* Uwaga: tu trzeba jeszcze poprawic obsluge nowej linii w trakcie napisu
               i \\ w napisie
            */
            int cp = c;
            while ((c = fgetc(ci)) != EOF && c != '"' && cp == '\\') {
                cp = c;
            }
            return c == EOF ? EOFILE : OTHER;
        } else if (c == '/') {
            /* moze byc komentarz */
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


void store_add_def(char *funame, int line, char *ipname){

}

void store_add_proto(char *funame, int line, char *ipname){

}

void store_add_call(char *funame, int line, char *ipname){

}
