#ifndef _DATA_H_
#define _DATA_H_
#include <stdio.h>
#include <stdlib.h>
// przechowuje nazwe funkcji oraz informacje o prototypie, definicji i wywolaniach
typedef struct {
	char* name; // nazwa funkcji
	char* proto_f; // plik z prototypem
	int proto_l; // linia z porototypem
	char* def_f; // plik z definicja
	int def_s; // start - linijka poczatkowa definicji
	int def_e;// end - linijka koncowa definicji
	char** call_f; //tablica plikow z wywolaniami
	int* call_l; // tablica linijek z wywolaniami
	int call_iterator; //  iterator do tablicy z wywolaniami
} store;

// typ pomocniczy, sluzy do wyswietlenia jakie funkcje zostaly wywolane w definicji funkcji
typedef struct {
	char* names;
	int type;
} pair;

extern store all_data [100];
extern int data_size;
extern pair history [100];
extern int history_size;

int exist(char* word);
int find_def(char* word);
int counter_exist(char* word, pair counter[100], int counter_size);
void create(char* fun_name);
void store_add_proto(char* fun_name, int line, char* file);
void store_add_call(char* fun_name, int line, char* file);
void store_add_def(char* fun_name, int line_s, int line_e, char* file);
void write_data();
#endif
