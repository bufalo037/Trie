/*Costea Mihai 312CB*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"


TTrie AllocCelula(const int cuv, const unsigned int nrlegmax,
 decodificator decod, codificator cod)
{
	TTrie trie;

	trie = (TTrie)malloc(sizeof(TCelTrie));
	if(!trie)
	{
		erraf
	}

	trie->nr_leg_alocd = 0;
	trie->cuv = cuv;
	trie->nrleg = 0;
	int i;

	trie->indleg = (char *)malloc( sizeof(char) * nrlegmax );
	if(!trie->indleg)
	{
		free(trie);
		erraf
	}

	trie->indchar = (char *)malloc( sizeof(char) * nrlegmax );
	if(!trie->indchar)
	{
		free(trie->indleg);
		free(trie);
		erraf
	}

	for(i = 0;i < nrlegmax;i++)
	{
		trie->indleg[i] = -1;
		trie->indchar[i] = -1;
	}

	trie->leg = NULL;
	
	trie->decod = decod; 
	//generitate
	trie->cod = cod;

	//logica e urmatoarea, nu aloc spatiu pt toate legaturile dar nu le aloc 
	//nici una cate una, pt ca nu vreau sa umplu memoria aiurea dar nici nu 
	//vreau sa realoc memoria de fiecare data cand trebuie sa inserez o 
	//legatura noua

	return trie;
}


static int SetLegatura(TTrie trie, const char key,const int cuv,
	const unsigned int nrlegmax)
{
	TTrie aux;
	int ind;

	aux = AllocCelula(cuv, nrlegmax, trie->decod, trie->cod);
	if(!aux)
	{
		erraf0
	}
	ind = trie->decod(key);
	trie->indleg[ind] = trie->nrleg;
	trie->indchar[trie->nrleg] = ind; //pt remove
	trie->nrleg++;
	trie->leg[(int)trie->indleg[ind]] = aux;

	return 1;
}


static int RealocareLegaturi(TTrie trie)
{
	TTrie *aux;
	int i;
	aux = (TTrie *)realloc(trie->leg, sizeof(TTrie) * 
		(trie->nrleg + FACTOR_ADITIV_ALOCARE));
	//logica e urmatoarea, nu aloc spatiu pt toate legaturile dar nu le aloc 
	//nici una cate una, pt ca nu vreau sa umplu memoria aiurea dar nici nu 
	//vreau sa realoc memoria de fiecare data cand trebuie sa inserez o 
	//legatura noua

	//functia asta se va apela doar cand se va dori sa se introduca o legatura
	//noua dar nu mai este nici o legatura libera alocata
	if(!aux)
	{
		erraf0
	}

	trie->leg = aux;
	trie->nr_leg_alocd += FACTOR_ADITIV_ALOCARE;
	for(i = trie->nrleg; i < trie->nr_leg_alocd; i++)
	{
		trie->leg[i] = NULL;
	}
	return 1;
}





int add(TTrie trie, char *cuv, const int nrlegmax)
{
	int n, cod, indx;
	n = strlen(cuv);
	
	if(n != 0)
	{
		cod = trie->decod(cuv[0]);
		indx = trie->indleg[cod];

		if(indx == -1) //trebuie setata o noua legatura
		{
			if(trie->nrleg == trie->nr_leg_alocd)
				RealocareLegaturi(trie); //testare
			

			SetLegatura(trie, cuv[0],n == 1 ? 1 : 0, nrlegmax); //testare
			add(trie->leg[trie->nrleg - 1], cuv + 1, nrlegmax); //verificare
			
		}
		else
		{
			add(trie->leg[indx], cuv + 1, nrlegmax); //verificare
		}
	}
	else
	{
		trie->cuv = 1;
	}
	return 1;
}


static void RefacereLegaturi(TTrie trie, unsigned int indx)
{
	int i;
	trie->indleg[(int)trie->indchar[indx]] = -1;
	for(i = indx; i < trie->nrleg - 1;i++)
		{
			trie->leg[i] = trie->leg[i + 1];
			trie->indleg[(int)trie->indchar[i + 1]] = i;
			//trie->indleg[i] = trie->indchar[i + 1]; 
			//trie->indchar[(int)trie->indleg[i]] = i;
			trie->indchar[i] = trie->indchar[i + 1]; 
		}

		trie->leg[trie->nrleg - 1] = NULL;
		trie->indleg[(int)trie->indchar[trie->nrleg -1]] = -1;
		trie->indchar[trie->nrleg -1] = -1;

		trie->nrleg--;
}


TTrie Remove(TTrie trie, char *cuv)
{
	static int avans;
	//printf("\n%d %s\n",trie->cuv,cuv);	
	if(trie->cuv == -1)
	{
		//printf("\n%p %s\n",trie->leg,cuv);
		avans = 1;
		//printf("\n%d\n",avans); 
	}
	//printf("\n%d\n",avans); 
	

	int n, cod, indx;
	TTrie eli, aux;
	char *cuvaux = cuv + 1;

	n = strlen(cuv);
	//printf("\n%u\n",n);

	if(trie->cuv != -1 && trie->nrleg <= 1) //gradul nodului e maxim pt remove
	{
		//printf("\n%d\n",trie->nrleg);
		if(n == 0) //trebuie sa fie 0 ca sa fie un nod de eliminat
		{
			trie->cuv = 0;
			if(trie->nrleg == 0)
				return trie;
			else
				return NULL;
		}
		else
			eli = trie;
	}
	else
	{
		if(!n)
		{
			if(trie->cuv != -1) //just in case
				trie->cuv = 0;
			return NULL;
		}

		eli = NULL;

	}
	
	cod = trie->decod(cuv[0]);
	indx = trie->indleg[cod];

	if(indx == -1)
		return NULL;
	//printf("\n%d\n",indx);

	aux = Remove(trie->leg[indx],cuvaux);

	if(avans == 1)
	{
		if(aux && eli)
			return eli;
		else
		{
			if(aux) 
			{
				//printf("\n%d %p\n",indx,trie->leg + indx);
				RefacereLegaturi(trie, indx);
				avans = 0; 
			}
		}
	}
	return aux;
}


static TTrie find(TTrie trie, char *cuv, char *key)
{
	int n, m, cod, indx;
	TTrie aux;

	n = strlen(cuv);
	m = strlen(key);

	if(n != 0)
	{
		cod = trie->decod(cuv[0]);
		indx = trie->indleg[cod];
		if(indx != -1)
		{
			key[m] = cuv[0];
			key[m + 1] = '\0';
			if(n >= 1)
				aux = find(trie->leg[indx], cuv + 1 , key);//modificare in cuv+1
		}
		else
		{
			return trie;
		}
	}
	else
	{
		return trie; 
	}
	return aux;
}


TTrie Cautare(TTrie trie, char *cuv,char *key)
{
	key[0] = '\0';
	return find(trie, cuv, key);
}


static int Afisare(FILE *output, TTrie trie, char *key, int nrlegmax, int *primul)
{
	int i,nr = 0;
	int n = strlen(key);
	if(trie->cuv == 1)
	{
		if(*primul == 0)
		{
			fprintf(output," ");
		}
		//printf("%s\n",key);
		fprintf(output,"%s", key);
		*primul = 0;
		
	}
	
	
	for(i = 0;i < nrlegmax && nr != (int)trie->nrleg; i++) 
	//nrlegmax ca vrea ordine alfabeica
	{
		if(trie->indleg[i] != -1)
		{
			nr++;//indicator daca a citit toate liniile
			key[n] = trie->cod(i);
			key[n + 1] = '\0';
			//	printf("\n%d\n",primul);
			Afisare(output, trie->leg[(int)trie->indleg[i]], key, nrlegmax,
			 primul);

			key[n] = '\0';
		}
	}
	return *primul;
}


int AfisareToateCuv(FILE *output, TTrie trie, char *key, const int nrlegmax)
{
	int primul = 1;
	return Afisare(output, trie, key, nrlegmax, &primul);
	//doar ca utilizatorul din main sa dea date relevante (nu o constanta)
}


static unsigned int Length(TTrie trie,unsigned int *nr, char *key)
{
	unsigned int sum = 0, i;
	unsigned int n = strlen(key);
	//printf("\n%s\n",key);
	if(trie->cuv == 1)
	{
		sum += n;
		(*nr)++;
	}
	for(i = 0;i < trie->nrleg; i++)
	{

			key[n] = 'x'; //nu conteaza ce este atata timp cat este
			key[n + 1] = '\0';
			sum += Length(trie->leg[i], nr , key);
			key[n] = '\0'; 
		
	}

	return sum;
}


unsigned int Mean_length(TTrie trie, unsigned int *nr, char *key)
{
	(*nr) = 0;
	return Length(trie, nr, key);
}


void DistrugereTrie(TTrie trie)
{
	int i;
	for(i = 0;i < trie->nrleg; i++)
	{
		DistrugereTrie(trie->leg[i]);
	}
	free(trie->indleg);
	free(trie->indchar);
	if(trie->leg)
		free(trie->leg);
	free(trie);
}