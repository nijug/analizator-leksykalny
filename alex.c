#include "alex.h"

#include<ctype.h>

static int ln=0;
static char ident[256];
static FILE *ci = NULL;

void
alex_init4file (FILE * in)
{
  ln = 1;
  ci = in;
}

lexem_t alex_nextLexem( void ) {
  int c;
  while( (c= fgetc(ci)) != EOF ) {
   if( c == '\n' ){
	ln++;
	continue;
   }else if( isspace( c ) )
                        continue;
    else if( c == '(' )
    return OPEPAR;
    else if( c == ')' )
      return CLOPAR;
    else if( c == '{' )
                        return OPEBRA;
    else if( c == '}' )
                        return CLOBRA;
    else if( isalpha( c ) ) {
      
      int i= 1;
      ident[0] = c;
      while( isalnum( c= fgetc(ci) ) )
                                ident[i++] = c;
                        ident[i] = '\0';
      ungetc(c,ci); // ungetc nie zawsze zwraca znak do strumienia przez co w plikach testowych omijany jest ')'
			//przez co printf nie sa odpowiednio zdejmowane ze stosu
      return IDENT;
     } else if( c == '"' ) {
      
      int cp = c;
      while( (c= fgetc(ci)) != '"') {
             	cp = c;
	  	if( c == EOF )
      			break;		
      }
      
      return  c== EOF ? EOFILE : OTHER;
    } else if( c == '/' ) {
     
                } if( isdigit( c ) || c == '.' ) {
  
                } else {
              
      return OTHER;
                }
        }
  return EOFILE;
}

char *
alex_ident (void)
{
  return ident;
}

int
alex_getLN ()
{
  return ln;
}
