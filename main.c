/*Costea Mihai 312CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

int main(int argc, char *argv[])
{
	FILE *input, *output;
	input = fopen(argv[1],"r");
	output = fopen(argv[2],"w");

	unsigned int nrOP, i, dimcuv = FACTOR_ADITIV_CUVANT;
	const unsigned int nrleg = ('z' - 'a'  + 1 + '9' - '0' + 1);
	unsigned int nrcharcuv, nrcuv;
	char *instructiune, *cuv, c, *key;
	char * inputbuffer, *outputbuffer;
	TTrie trie, aux;

	//=========================================================================
	instructiune = (char *)malloc(sizeof(char) * DIMMAXINSTR); //look functii.h
	if(!instructiune)
	{
		erram
	}


	cuv = (char *)malloc(sizeof(char) * dimcuv);
	if(!cuv)
	{
		free(instructiune);
		erram
	}

	
	inputbuffer = (char *)malloc(BUFSIZ);
	if(!inputbuffer)
	{
		frees(2,instructiune, cuv);
		erram
	}
	setbuf(input,inputbuffer); //pt a face operatiile mai rapid

	outputbuffer = (char *)malloc(BUFSIZ);
	if(!outputbuffer)
	{
		frees(3,instructiune, cuv, inputbuffer);
		erram
	}
	setbuf(output,outputbuffer);
	
	key = (char *)malloc(sizeof(char) * dimcuv);
	if(!key)
	{
		frees(4,instructiune, cuv, inputbuffer);
		erram
	}

	//=========================================================================

	fscanf(input,"%u",&nrOP); //eroare

	trie = AllocCelula(-1, nrleg, decodificareind, codificareind);
	if(!trie)
	{
		frees(5,instructiune, cuv, key, outputbuffer);
		erram
	}


	//=========================================================================
	//=========================================================================

	for(i = 0;i < nrOP;i++)
	{
		fscanf(input,"%s",instructiune);
		c = fgetc(input); // ori ' ' ori '\n'
	//=========================================================================
		if(strcmp(instructiune,"add") == 0)
		{

			citire_cuv(input, &cuv, &key, &dimcuv);
			add(trie, cuv, nrleg);
			continue;

		}
	//=========================================================================
		if(strcmp(instructiune,"remove") == 0)
		{
			citire_cuv(input, &cuv, &key, &dimcuv);
			aux = Remove(trie, cuv);
			if(aux)
				DistrugereTrie(aux);
			continue;
		}
	//=========================================================================
		if(strcmp(instructiune,"find") == 0)
		{
			citire_cuv(input, &cuv, &key, &dimcuv);
			aux = Cautare(trie, cuv, key);
			if(strcmp(key, cuv) == 0 && aux->cuv == 1)
				fprintf(output,"True\n");
			else
				fprintf(output,"False\n");
			continue;
		}
	//=========================================================================
		if(strcmp(instructiune,"find_longest_prefix") == 0)
		{
			citire_cuv(input, &cuv, &key, &dimcuv);
			//printf("%s\n",cuv);
			Cautare(trie, cuv, key);
			//printf("%s\n",cuv);
			if(key[0] != '\0')
				fprintf(output,"%s\n",key);
			else
				fprintf(output,"None\n");
			continue;
		}
	//=========================================================================
		if(strcmp(instructiune,"find_all_with_prefix") == 0)
		{
			if(c == ' ')
			{
				citire_cuv(input, &cuv, &key, &dimcuv);
				aux = Cautare(trie, cuv, key);
				if(strcmp(cuv, key) != 0)
					fprintf(output,"None");
				else
					if(AfisareToateCuv(output, aux, key, nrleg) == 1)
					//in caz de nu e nici un cuvant si aux e nod rad
//da, se poate intampla ian cazul in care se da input cu un spatiu dupa comanda
//si sir vir dupa 
						fprintf(output,"None");
			}
			else
			{
				key[0] = '\0';
				if(AfisareToateCuv(output, trie, key, nrleg))
					fprintf(output,"None");
			}
			fprintf(output,"\n");
			continue;
		}
	//=========================================================================
		if(strcmp(instructiune,"mean_length") == 0)
		{
			if(c == ' ')
			{
				citire_cuv(input, &cuv, &key, &dimcuv);
				aux = Cautare(trie, cuv, key);
				if(strcmp(cuv, key) != 0)
					fprintf(output,"0\n");
				else
				{
					nrcharcuv = Mean_length(aux, &nrcuv, key);
					if(nrcuv != 0)
						fprintf(output,"%.3f\n", (1.0 * nrcharcuv)/nrcuv);
					else
						fprintf(output,"0\n");
				}
			}
			else
			{
				key[0] = '\0';
				nrcharcuv = Mean_length(trie, &nrcuv, key);
				if(nrcuv != 0)
					fprintf(output,"%.3f\n", (1.0 * nrcharcuv)/nrcuv);
				else
					fprintf(output,"0\n");
			}
			//nu mergea pus doar un printf pt ca mai era si cazul cu stcmp == 0
			// si nu doream sa mai pun o alta variabila sau un alt continue;
			
			continue;
		}
		errinp //daca se ajunge aici inseamna ca este o eroare la input
	}

	fclose(input);
	fclose(output);
	DistrugereTrie(trie);
	trie = NULL;
	frees(5, instructiune, cuv, key, inputbuffer,outputbuffer);
	// am remarcat ca programul executa mai rapid cu aprox 0.5s overall pe toate
	// testele daca le pun buffer fisierelor
	return 0;

}

//modificare Length si modificare find_all_with_prefix in cazul /0