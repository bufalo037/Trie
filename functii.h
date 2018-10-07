/*Costea Mihai 312CB*/

#include "trie.h"

#define DIMMAXINSTR 21
#define FACTOR_ADITIV_ALOCARE 6
#define FACTOR_ADITIV_CUVANT 20

#ifndef __ERRORS__
#define __ERRORS__

#define erram fprintf(stderr,"Eroare alocare memorie main");exit(EXIT_FAILURE);
#define erraf fprintf(stderr,"Eroare alocare memorie functii");return NULL;
#define erraf0 fprintf(stderr,"Eroare alocare memorie functii");return 0;
#define errinp fprintf(stderr,"Eroare citire input");exit(EXIT_FAILURE);

#endif

#ifndef __FUNCTII__
#define __FUNCTII__

//functii.c

void frees(int , ...);
unsigned int decodificareind(char );
char codificareind(unsigned int );
char *citire_cuv(FILE *, char **, char **, unsigned int *);

//trie.c

TTrie AllocCelula(const int , const unsigned int,decodificator,codificator);

int add(TTrie, char *, const int );
TTrie Remove(TTrie, char *);
TTrie Cautare(TTrie, char *, char *);
void DistrugereTrie(TTrie);
int AfisareToateCuv(FILE *, TTrie, char *, const int);
unsigned int Mean_length(TTrie,unsigned int *, char *);

#endif