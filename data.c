#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//0 dla prototypu
// 1 dla definicji
// 2 dla call
static store all_data [100];
static int data_size=0;
static pair history [100];
static int history_size=0;

int exist(char* word) //zwraca indeks jesli nazwa jest zapina, -1 jesli nie jest
{
	for (int i = 0; i < data_size; i++)
	{
		if (strcmp(all_data[i].name, word) == 0) return i;
	}

	return -1;
}
int find_def(char* word) 
{
	for (int i = 0; i < history_size; i++)
	{
		if (strcmp(history[i].names, word) == 0 && history[i].type == 1) return i;
	}

	return -1;
}
int counter_exist(char* word, pair *counter, int counter_size) 
{
	for (int i = 0; i < counter_size; i++)
	{
		if (strcmp(counter[i].names, word) == 0) return i;
	}

	return -1;
}
void create(char* fun_name)
{
	store temp;
	temp.name= fun_name;
	temp.proto_f = NULL; 
	temp.proto_l = 0; 
	temp.def_f = NULL;
	temp.def_s = 0; 
	temp.def_e = 0; 
	temp.call_f = malloc(100* sizeof * temp.call_f); 
	temp.call_l = malloc(100 * sizeof * temp.call_l);
	temp.call_iterator = 0;
	all_data[data_size] = temp;
	data_size++;
 }
void store_add_proto(char* fun_name, int line, char* file)
{
	int i = exist(fun_name);
	if (i == -1)
	{
		create(fun_name);
		all_data[data_size - 1].proto_f = file;
		all_data[data_size - 1].proto_l = line;
	}
	else
	{
		all_data[i].proto_f = file;
		all_data[i].proto_l = line;
	}
	history[history_size].names = fun_name;
	history[history_size].type = 0;
	history_size++;


}

void store_add_call(char* fun_name, int line, char* file)
{
	int i = exist(fun_name);
	if (i == -1)
	{
		create(fun_name);
		all_data[data_size - 1].call_f[all_data[data_size-1].call_iterator] = file;
		all_data[data_size - 1].call_l[all_data[data_size-1].call_iterator] = line;
		all_data[data_size-1].call_iterator++;
	}
	else
	{
		all_data[i].call_f[all_data[i].call_iterator] = file;
		all_data[i].call_l[all_data[i].call_iterator] = line;
		all_data[i].call_iterator++;
	}
	history[history_size].names = fun_name;
	history[history_size].type = 2;
	history_size++;


}

void store_add_def(char* fun_name, int line_s, char* file)
{
	int i = exist(fun_name);
	if( (strcmp( fun_name, "for") != 0) && (strcmp( fun_name, "while") != 0) && (strcmp( fun_name, "if") != 0) )
	{
		if (i == -1)
		{
			create(fun_name);
			all_data[data_size - 1].def_f = file;
			all_data[data_size - 1].def_s = line_s;
		}
		else
		{
			all_data[i].def_f = file;
			all_data[i].def_s = line_s;
		}
		history[history_size].names = fun_name;
		history[history_size].type = 1;
		history_size++;
	}
}

void def_end(int line)
{
    for (int i= history_size-1; i>=0; i--)
    {
        if (history[i].type==1)
        {
            int j=exist(history[i].names);
            all_data[j].def_e=line;
            return;
        }
    }
}

void write_data() // dane przechowywane globalnie, wystarczy wywolac funkcje na koniec main i zamknac program
{
	for (int i = 0; i < data_size; i++)
	{
		if (all_data[i].def_f == NULL)
			continue; // jesli funkcja nie ma definicji jest funkjc� wbudowan�- nie nalezy wyswieltac
		printf("Funkcja %s:\n", all_data[i].name);
		
		printf(" Prototyp:\n");
		if (all_data[i].proto_f == NULL)
			printf("  brak\n");
		else
			printf("  plik %s od linia %d do linia %d\n", all_data[i].proto_f, all_data[i].proto_l, all_data[i].proto_l);
		
		printf(" Definicja:\n");
		printf("  plik %s od linia %d do linia %d\n", all_data[i].def_f, all_data[i].def_s, all_data[i].def_e);
		
		printf(" Uzycie:\n");
		if (all_data[i].call_iterator == 0)
			printf("  brak\n");
		else
		{
			for (int j = 0; j < all_data[i].call_iterator; j++)
			{
				printf("  plik %s od linia %d do linia %d\n", all_data[i].call_f[j], all_data[i].call_l[j], all_data[i].call_l[j]);
		
			}
		}
	
		printf(" Wywoluje:\n");
		int start = find_def(all_data[i].name)+1;
		if (history[start].type != 2)
			printf("  brak\n\n");
		else
		{
			int end = start;
			while (history[end + 1].type == 2 && end +1  <= history_size)
				end++;
			if (end == start)
				printf("%s\n", history[start].names);
			else
			{
				pair counter[100];
				int counter_size = 0;
				for (int j = start; j <= end; j++)
				{
					int temp = counter_exist(history[j].names,counter,counter_size);
					if (temp == -1)
					{
						counter[counter_size].names = history[j].names;
						counter[counter_size].type = 1;
						counter_size++;
					}
					else
						counter[temp].type++;
				}
				for (int j = 0; j < counter_size; j++)
				{
				if (counter[j].type==1)
					printf("%s\n", counter[j].names);
				else
					printf("%s (%d razy)\n", counter[j].names, counter[j].type);
				}
				
			}
			printf("\n");
		}
	
	}
	
}
