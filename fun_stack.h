#ifndef _FUN_STACK_H_IS_INCLUDED_
#define _FUN_STACK_H_IS_INCLUDED_

typedef struct {
    int par_level;
    char *funame;
} fun_t;

typedef struct {
    fun_t *data;
    int size;
} fun_db;


int top_of_funstack(void);  // zwraca par_level - "zagłębienie nawiasowe" przechowywane na szczycie

void put_on_fun_stack(int par_level, char *funame); // odkłada na stos parę (funame,par_level)

char *get_from_fun_stack(void); // usuwa z wierzchołka parę (funame,par_level), zwraca zdjętą funame

#endif

