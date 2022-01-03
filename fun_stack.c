#include<stdio.h>
#include<stdlib.h>
#include "fun_stack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fun_stack.h"

typedef struct stack_node {
	int pair_lvl;
	char* fun_name;
	struct stack_node *next;
} *stack_t;

stack_t top;



void put_on_fun_stack( int par_level, char *funame )
{
    char *funcopy = malloc( (strlen(funame)+1) * sizeof (char));
		strcpy(funcopy, funame);

	if( top == NULL)
	{
		
		top = malloc( sizeof *top);
		top->pair_lvl = par_level;
		top->fun_name = funcopy;
		top->next = NULL;
		printf("new stack initialized\n");
		printf("%s new name pushed to stack\n", top->fun_name);
	}
	else
	{
		stack_t tmp = malloc( sizeof *tmp);
		tmp->pair_lvl = par_level;
		tmp->fun_name = funcopy;
		tmp->next = top;
		top = tmp;
		printf("%s new name pushed to stack\n", top->fun_name);
	}
}

char *get_from_fun_stack( void )
{
	if( top == NULL )
	{
		printf("Błąd pobierania danych, stos obecnie jest pusty\n");
		return NULL;
	}
	else
	{
		char *funame = top->fun_name;
		stack_t tmp = top;
		top = top->next;
		free(tmp);
		printf("%s name poped from stack\n", funame);

		return funame;
	}
}

int top_of_funstack( void )
{
	if( top == NULL )
	{
		printf("Błąd pobierania danych, stos obecnie jest pusty\n");
		return EXIT_FAILURE;
	}
	else
	{
		printf("%d stack pair level\n", top->pair_lvl);
		return top->pair_lvl;
	}
}