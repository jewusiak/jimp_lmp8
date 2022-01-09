#include <stdio.h>
#include <string.h>
#include "fun_stack.h"


int main() {
    put_on_fun_stack(3, "pierwszy stak");
    put_on_fun_stack(555, "drugi stak");


    printf("%d\n", top_of_funstack());
    printf("%s\n", get_from_fun_stack());
    printf("%d\n", top_of_funstack());
    printf("%s\n", get_from_fun_stack());
    printf("%d\n", top_of_funstack());
    printf("%s\n", get_from_fun_stack());
    printf("%d\n", top_of_funstack());
    return 0;
}