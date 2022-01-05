#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fun_stack.h"

typedef struct stack_node {	//deklaracja typu struktury który będzie odkładany na stos
	int pair_lvl;
	char* fun_name;
	struct stack_node *next;
} *stack_t;

stack_t top;			//globalna deklaracja pierwszego elementu stosu



void put_on_fun_stack( int par_level, char *funame )	//funkcja dodająca elementy do stosu
{

	char *funcopy = malloc( (strlen(funame)+1) * sizeof (char));
	strcpy(funcopy, funame);	//kopiowanie stringa zawierającego nazwę identyfikatora do nowej zmiennej
					//operacja wymagana do prawidłowego działania programu

	if( top == NULL)	//inicjacja pierwszego elementu stosu
	{
		
		top = malloc( sizeof *top);
		top->pair_lvl = par_level;
		top->fun_name = funcopy;
		top->next = NULL;
	}
	else			//zapełnianie kolejnych elementów stosu
	{
		stack_t tmp = malloc( sizeof *tmp);
		tmp->pair_lvl = par_level;
		tmp->fun_name = funcopy;
		tmp->next = top;
		top = tmp;
	}
}

char *get_from_fun_stack( void )	//funkcja zdejmująca elementy ze stosu
{
	if( top == NULL )	//obsługa błędów w razie napotkania pustego stosu
	{
		printf("Błąd pobierania danych, stos obecnie jest pusty\n");
		return NULL;
	}
	else			//zwalnianie pamięci dla struktury znajdującej się na szczycie stosu
	{			//a następnie zwracanie wskaźnika na identyfikator przechowywany na usuniętym szczycie
		char *funame = top->fun_name;
		stack_t tmp = top;
		top = top->next;
		free(tmp);

		return funame;
	}
}

int top_of_funstack( void )	//funkcja sprawdzająca zagłębienie nawiasowe przechowywane na szczycie stosu
{
	if( top == NULL )	//obsługa błędów w razie napotkania pustego stosu
	{
		printf("Błąd pobierania danych, stos obecnie jest pusty\n");
		return EXIT_FAILURE;
	}
	else			//zwracanie przez funkcję numeru zagłębienia nawiasowego ze szczytu
	{
		return top->pair_lvl;
	}
}
