#include "parser.h"
  void analizatorSkladni (char *inpname){                           

  FILE *in = fopen (inpname, "r");

  int nbra = 0;   
  int npar = 0;   
  alex_init4file (in);        

  lexem_t lex;

  lex = alex_nextLexem ();   
  while (lex != EOFILE) {
    switch (lex) {
    case IDENT:{
        char *iname = alex_ident ();  
        lexem_t nlex = alex_nextLexem ();
        if (nlex == OPEPAR) {   
          npar++;
          put_on_fun_stack (npar,iname);     
        }
        else {                  
          lex = nlex;
          continue;
        }
      }
      break;
    case OPEPAR:
      npar++;
      break;
    case CLOPAR:{             
        if (top_of_funstack () == npar) 
        {                                              
          lexem_t nlex = alex_nextLexem ();
          if (nlex == OPEBRA)   
         {  
            nbra++;
            store_add_def (get_from_fun_stack (), alex_getLN (), inpname);
         }
          else if (nbra == 0)  
            store_add_proto (get_from_fun_stack (), alex_getLN (), inpname);
          else              
            store_add_call (get_from_fun_stack (), alex_getLN (), inpname);
        }
        npar--;
      }
      break;
    case OPEBRA:
      nbra++;
      break;
    case CLOBRA:{
      nbra--;
    def_end(alex_getLN());
    }
      break;
    case ERROR:{
        fprintf (stderr, "\nBUUUUUUUUUUUUUUUUUUUUUU!\n"
                 "W pliku %s (linia %d) są błędy składni.\n"
                 "Kończę!\n\n", inpname, alex_getLN ());
        exit (1);              
      }
      break;
    default:
      break;
    }
    lex = alex_nextLexem ();
  
 }
}
