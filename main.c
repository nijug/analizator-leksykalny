#include "data.h"
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

store all_data[];
int data_size=0;
pair history[];
int history_size=0;

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		fprintf(stderr, "%s: Nie podano plikow do analizy, nalezy podac nazwy plikow jako argumenty wywolania.\n", argv[0]);
		return 1;
	}


	for (int i = 1; i < argc; i++)
	{
		analizatorSkladni(argv[i]);
	}

	write_data();
	return 0;
}
