#include<stdio.h>
#include<stdlib.h>
#include"fun_stack.h"

typedef struct stack_node {
	int pair_lvl;
	char* fun_name;
	struct stack_node *next;
} *stack_t;

stack_t top;

void put_on_fun_stack( int par_level, char *funame )
{
	if( top == NULL)
	{
		top = malloc( sizeof *top);
		top->pair_lvl = par_level;
		top->fun_name = funame;
		printf("new stack initialized\n");
		printf("%s new name pushed to stack\n", top->fun_name);
	}
	else
	{
		stack_t tmp = malloc( sizeof *tmp);
		tmp->pair_lvl = par_level;
		tmp->fun_name = funame;
		tmp->next = top;
		top = tmp;
		printf("%s new name pushed to stack\n", top->fun_name);
	}
}

char *get_from_fun_stack( void )
{
	char *funame = top->fun_name;
	stack_t tmp = malloc( sizeof *tmp);
	tmp = top;
	top = top->next;
	free(tmp);
	printf("%s name poped from stack\n", funame);

	return funame;
}

int top_of_funstack( void ) // zwraca par_level - "zagłębienie nawiasowe" przechowywane na szczycie
{
	printf("%d stack pair level\n", top->pair_lvl);
	return top->pair_lvl;
}

int main()
{
	put_on_fun_stack( 1, "name1" );
	put_on_fun_stack( 2, "name2" );
	top_of_funstack();
	get_from_fun_stack();
	top_of_funstack();
	put_on_fun_stack( 3, "name3" );
	get_from_fun_stack();
	get_from_fun_stack();
	return EXIT_SUCCESS;
}
