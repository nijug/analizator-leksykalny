#include<stdio.h>
#include<stdlib.h>
#include"fun_stack.h"

int main()
{
	int i;

	put_on_fun_stack( 1, "name1" );	//badanie przypadków normalnego użytkowania stosu - dodawanie i zdejmowanie par
	put_on_fun_stack( 2, "name2" );
	put_on_fun_stack( 3, "name3" );

	if( top_of_funstack() == 3 )
		printf("Dodawanie do stosu: prawidłowe\n\n");

	get_from_fun_stack();

	if( top_of_funstack() == 2 )
		printf("Zdejmowanie ze stosu: prawidłowe\n\n");

	get_from_fun_stack();
	get_from_fun_stack();
					//badanie skrajnych przypadków - próba pobrania danych z pustego stosu
	if( get_from_fun_stack() == NULL )
		printf("Podjęcie próby zdejmowania z pustego stosu: prawidłowe\n\n");

	for(i = 0; i<1001; i++)		//badanie skrajnych przypadków - próba przepełnienia stosu
	{
		put_on_fun_stack( i, "name" );
	}
	if( top_of_funstack() == 1000 )
		printf("Przepełnianie stosu: prawidłowe\nStos został zaimplementowany dynamicznie\n");	
	
	return EXIT_SUCCESS;
}
