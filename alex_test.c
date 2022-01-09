#include "parser.h"
#include "alex.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Brak plikow w komendzie wywolania!");
        return 4;
    }
    int i;
    for (i = 1; i < argc; i++)
        analizatorSkladni(argv[i]);
    print_store();
    return 0;
}