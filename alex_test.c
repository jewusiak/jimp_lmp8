#include "parser.h"

int main(int argc, char **argv){
    if(argc<2)
        return 4;
    analizatorSkladni(argv[1]);
    return 0;
}