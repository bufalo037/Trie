/*Costea Mihai 312CB*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

void frees(int nr, ...)
{
	int i;
	va_list list;
	void * argument;
	va_start(list,nr);
	for(i = 0;i < nr;i++)
	{
		argument = va_arg(list,void *);
		free(argument);
	}
	va_end(list);
}


unsigned int decodificareind(char c)
{
	char *p;
	p = strchr("0123456789",c);
	if(p)
	{
		return c - '0'; // se poate verifica ascii
	}

	return c - 'a' + 10;
}


char codificareind(unsigned int x)
{
	if(x <= 9)
		return (char)(x + '0');
	return (char)(x + 'a' - 10);
}

char *citire_cuv(FILE *input, char **cuv, char **key,unsigned int *dimcuv)
{
	char *aux,ok = 0;
	fpos_t *pos;
	pos = (fpos_t *)malloc(sizeof(fpos_t));
	fgetpos(input, pos);
	fgets(*cuv, *dimcuv, input);
	while(feof(input) == 0 && (*cuv)[strlen(*cuv) - 1] != '\n' )
	{
		ok = 1;
		*dimcuv += FACTOR_ADITIV_CUVANT;
		aux = realloc(*cuv, sizeof(char) * (*dimcuv) );
		if(!aux)
		{
			free(pos);
			return NULL;
		}
		*cuv = aux;

		fsetpos(input, pos);
		fgetpos(input, pos);
		fgets(*cuv,*dimcuv,input);

	}

	if( (*cuv)[strlen(*cuv) - 1] == '\n' ) 
	{
		(*cuv)[strlen(*cuv) - 1] = '\0';
	}

	if( strlen(*cuv) && (*cuv)[strlen(*cuv) - 1] == '\r' ) //testul8.in era bulit
	//cel mai probabil cand s-a rescris fisierul s-a rescris pe windows si a a
	//aparut un carige return de nicaieri care dadea segmentation fault
	{
		(*cuv)[strlen(*cuv) - 1] = '\0';
	}
	

	free(pos);
	if(ok == 1)
	{
		aux = realloc(*key, sizeof(char) * (*dimcuv));
		if(!aux)
		{
			return NULL;
		}
		*key = aux;
	}
	return *cuv;
}