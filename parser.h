#include <stdio.h>
#include <stdlib.h> // exit - ale exit trzeba kiedyś usunąć i nie będzie to potrzebne
#include "alex.h"       // analizator leksykalny
#include "fun_stack.h"  // stos funkcji
#include "data.h" //przechowywanie danych
#define MAXINDENTLENGHT 256     // maks długość identyfikatora

void analizatorSkladni (char *inpname)
