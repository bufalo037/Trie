/*Costea Mihai 312CB*/

typedef unsigned int (*decodificator)(char);
typedef char (*codificator)(unsigned int);

typedef struct trie
{
	char cuv; // Cuantificare 1 este cuvant, 0 nu este cuvant -1 rad
	unsigned char nrleg; //nr de legaturi care pleaca din nod;
	unsigned char nr_leg_alocd; //nr de legaturi alocate
	char *indleg; // face legatura intre un caracter si indicele pointerului
	//catre legatura care are cheia caracterul respectiv
	//ordinea este ordine alfabetica 0-9 a-z
	char *indchar; //inversul lui indleg. E necesar pt stergere
	struct trie **leg; //dublu pointer pt a economisi memorie
	//daca ar fi fost sa fac pointer simplu trebuia sa il cu sizeof de 
	//structura * cu cate pointere as fi dorit eu, si as fi alocat suplimentar
	decodificator decod; //pointer la o functie care returneaza un cod pt un
	//caracter care va fi chiar indice pt indleg pt a afla legatura indicele
	//legaturii
	codificator cod;//pointer la o functiue care primeste un intreg si 
	//returneaza un caracter (Functiia inversa decod-ului). Este necesara pt
	//afisare


}TCelTrie, *TTrie; //am incercat sa minimizez la maxim memoria folosita de 
//struct in timp, in acelas timp facand operatiile de cautare rapide
//nici macar un bitfield nu ar fi imbunatatit mai bine folosirea memoriei pt ca
//s-ar fi facut padding cel mai probabil atunci cand ar fi trebuit sa treaca la
//struct trie ** cu citirea

/* Ce am zis mai sus cu paddingul sunt observatii personale la cum cred ca 
functioneaza. Nu stiu daca depinde de compilator modul in care functioneaza
paddingul sau daca observatiile mele chiar au o valoare de generalitate asupra
modului cum este reprezentata memoria unui struct */

/* Am presupus ca ar fi cel mai bine daca as avea un pointer la o functie de 
codificare, in asa fel, orice celula are un caracter generalist si ar putea
sa stocheze caractere diferite */