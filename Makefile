CC=gcc

#all tylko dla clion
all:
	$(CC) alex_test.c

alex:
	$(CC) alex_test.c alex.c fun_stack.c parser.c -oalex-w

funstack:
	$(CC) funstack_test.c fun_stack.c -ofunstack-w