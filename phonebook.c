#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct cvorStabla* stablo;
struct cvorStabla {
	char ime[20];
	char prezime[20];
	char  br[20];
	stablo L;
	stablo D;
};

typedef struct HashTable* hash;
struct HashTable {
	int velTab;
	stablo *hashlist;
};

hash inicijalizacija(int);
int preslikavanje(hash, char[]);
void ispisTab(hash);
void ispisStabla(stablo, int);
stablo dodajElm(stablo, char[], char[], char[]);
void dodajHash(hash);
void traziElem(hash);
stablo traziStablo(stablo s, char[], char[]);
void addNew(hash);
void deleteE(hash);
stablo brisiElement(stablo, char[], char[]);
stablo traziMin(stablo);
void alterContact(hash);

int main() {

	hash H = NULL;
	int i = 0, vel=11, flag=0, n;


	H = inicijalizacija(vel);

	
	dodajHash(H);
	
	

	while (flag == 0) {

		printf("*****************IMENIK*****************\n");
		printf("(1) Trazi kontakt\n");
		printf("(2) Dodati novi kontakt\n");
		printf("(3) Izbrisati kontakt\n");
		printf("(4) Promjeniti kontakt\n");
		printf("(5) Ispis cijelog imenika\n");
		printf("(6) Izlaz iz imenika\n");

		printf("Vas izbor:\n");
		scanf("%d", &n);

		if (n == 1) {
			traziElem(H);
		}
		else if (n == 2) {
			addNew(H);
		}
		else if (n == 3) {
			deleteE(H);
		}
		else if (n == 4) {
			alterContact(H);
		}
		else if (n == 5) {
			ispisTab(H);
		}
		else if (n == 6) {
			flag = 1;
		}
		else {
			printf("Taj izbor nije moguc\n");
			return;
		}
	}



	return 0;
}


hash inicijalizacija(int vel) {
	hash H;
	int i;

	H = (hash)malloc(sizeof(struct HashTable));

	if (H == NULL) {
		printf("greska pri alokaciji memorije u inic\n");
		return;
	}

	H->velTab = vel;

	H->hashlist = (stablo*)malloc(sizeof(stablo) * H->velTab);

	if (H->hashlist == NULL) {
		printf("geska pri alokaciji H->hashlist\n");
		return;
	}

	for (i = 0; i < H->velTab; i++)
		H->hashlist[i] = NULL;

	return H;
}

int preslikavanje(hash H, char prezime[]) {
	int i=0;
	int sum = 0;

	while (prezime[i] != '\0') {
		sum = sum + (int)prezime[i];
		++i;
	}

	return(sum % H->velTab);
}

void ispisTab(hash H) {
	int i = 0, z=1;

	if (H->hashlist==NULL)
	{
		printf("tablica ne postoji\n");
		return;
	}
	else {
		while (i != H->velTab) {
			printf("%d:\n", i);
			ispisStabla(H->hashlist[i], &z);

			++i;
		}
	}
}

void ispisStabla(stablo H, int *z) {

	if (H != NULL) {
		printf("%d %s %s %s\n", *z, H->prezime, H->ime, H->br);
		++(*z);
		ispisStabla(H->L, z);
		
		ispisStabla(H->D, z);
		
	}
}

stablo dodajElm(stablo s, char ime[], char prez[], char br[]) {
	if (s == NULL) {
		s = (stablo)malloc(sizeof(struct cvorStabla));
		s->L = NULL;
		s->D = NULL;
		strcpy(s->br, br);
		strcpy(s->ime, ime);
		strcpy(s->prezime, prez);

	
	}
	else if (strcmp(prez, s->prezime)<0) {
		s->L = dodajElm(s->L, ime, prez, br);
	
	}
	else if (strcmp(prez, s->prezime) > 0) {
		s->D = dodajElm(s->D, ime, prez, br);
	}
	else if (strcmp(prez, s->prezime) == 0) {
		if (strcmp(ime, s->ime) < 0) {
			s->L = dodajElm(s->L, ime, prez, br);
		}
		else if (strcmp(ime, s->ime) > 0) {
			s->D = dodajElm(s->D, ime, prez, br);
		}
		else if (strcmp(ime, s->ime) == 0) {
			printf("Korisnik vec postoji\n");
			
		}
	}


	return s;






}

void dodajHash(hash H) {

	char ime[20], prezime[20], broj[20];
	int i;
	FILE* fp = fopen("imenik.txt", "r");

	if (fp == NULL) {
		printf("greska kod otvranaja datoteke\n");
		return;
	}

	while (!feof(fp)) {
		fscanf(fp, "%s %s %s", prezime, ime, broj);

		i = preslikavanje(H, prezime);

		H->hashlist[i] = dodajElm(H->hashlist[i], ime, prezime, broj);
	}
	
	
}

void traziElem(hash H) {

	stablo korisnik;
	char ime[20], prezime[20];
	int i;

	printf("Kojeg korisnika trazite\n");
	scanf("%s %s",ime, prezime);

	i = preslikavanje(H, prezime);

	korisnik = traziStablo(H->hashlist[i], prezime, ime);

	printf("%s %s %s\n", korisnik->ime, korisnik->prezime, korisnik->br);
}

stablo traziStablo(stablo s, char prezime[], char ime[]) {
	if (s == NULL) {
		printf("Nazalost, podaci o tom korisniku ne postoje\n");
		return s;
	}
	else if (strcmp(prezime, s->prezime) < 0) {
		return traziStablo(s->L, prezime, ime);
		
	}
	else if (strcmp(prezime, s->prezime) > 0) {
		return traziStablo(s->D, prezime, ime);
		
	}
	else if (strcmp(prezime, s->prezime)==0) {
	
		if (strcmp(ime, s->ime) < 0) {
			return traziStablo(s->L, prezime, ime);
		
		}
		else if (strcmp(ime, s->ime) > 0) {
			return traziStablo(s->D, prezime, ime);
			
		}
		else if (strcmp(ime, s->ime) == 0) {
			return s;

		}
	
	}

	
}

void addNew(hash H) {
	char ime[20], prezime[20], broj[15];
	int i;

	printf("Unesite ime, prezime i  broj novog korisnika\n");
	scanf("%s %s %s", ime, prezime, broj);

	i = preslikavanje(H, prezime);

	H->hashlist[i] = dodajElm(H->hashlist[i], ime, prezime, broj);
}

void deleteE(hash H) {
	char ime[20], prezime[20], broj[15];
	int i;

	printf("Unesite ime i prezime korisnika kojeg zelite izbrisati\n");
	scanf("%s %s", ime, prezime);

	i = preslikavanje(H, prezime);

	H->hashlist[i] = brisiElement(H->hashlist[i], ime, prezime);




}

stablo brisiElement(stablo s, char ime[], char prezime[]) {
	stablo temp;
     
	if (s == NULL) {
		printf("Nazalost, podaci o tom korisniku ne postoje\n");
		return s;
	}
	else if (strcmp(prezime, s->prezime) < 0) {
		
		s->L = brisiElement(s->L, ime, prezime);
		
		return s;

	}
	else if (strcmp(prezime, s->prezime) > 0) {
		
		s->D = brisiElement(s->D, ime, prezime);
		
		return s;
	}
	else if (strcmp(prezime, s->prezime) == 0) {

		if (strcmp(ime, s->ime) < 0) {
			
			s->L = brisiElement(s->L, ime, prezime);

			return s;
		}
		else if (strcmp(ime, s->ime) > 0) {
			
			s->D = brisiElement(s->D, ime, prezime);

			return s;
		}
		else if (strcmp(ime, s->ime) == 0) {
			
			if (s->L != NULL && s->D != NULL) {
				temp = traziMin(s->D);

				strcpy(s->ime, temp->ime);
				strcpy(s->prezime, temp->prezime);
				strcpy(s->br, temp->br);

				s->D = brisiElement(s->D, s->ime, s->prezime);

				return s;
			}
			else {
				temp = s;
				
				if (s->L == NULL)
					s = s->D;
				else
					s = s->L;

				free(temp);
				
				return s;

			}

		}
	}
	}
	

	


stablo traziMin(stablo s) {
	if (s == NULL)
		return s;
	else if (s->L == NULL)
		return s;
	else
		return traziMin(s->L);
}

void alterContact(hash H) {

	char ime[20], prezime[20], broj[15];
	stablo korisnik;
	char tempI[20], tempP[20], tempB[20];
	int i, n, flag=0;

	printf("Unesite ime i prezime\n");
	scanf("%s %s", ime, prezime);
	
	i = preslikavanje(H, prezime);

	korisnik = traziStablo(H->hashlist[i], prezime, ime);

	
	strcpy(tempI, korisnik->ime);
	strcpy(tempP, korisnik->prezime);
	strcpy(tempB, korisnik->br);

	H->hashlist[i] = brisiElement(H->hashlist[i], korisnik->ime, korisnik->prezime);
	
	while (flag == 0) {
		printf("Što zelite promijeniti?\n");
		printf("Ime korisnika (1)\nPrezime korisnika (2)\nBroj korisnika (3)\nIZLAZ (4)\n");
		scanf("%d", &n);

		switch (n) {
		case 1:
			printf("Unesite novo ime\n");
			scanf("%s", ime);

			tempI[0] = 0;
			strcpy(tempI, ime);

			i = preslikavanje(H, tempP);

			H->hashlist[i] = dodajElm(H->hashlist[i], tempI, tempP, tempB);

			break;

		case 2:
			printf("Unesite novo prezime\n");
			scanf("%s", prezime);

			tempP[0] = 0;
			strcpy(tempP, prezime);

			i = preslikavanje(H, tempP);

			H->hashlist[i] = dodajElm(H->hashlist[i], tempI, tempP, tempB);

			break;
		case 3:
			printf("Unesite novi broj\n");
			scanf("%s", broj);

			tempB[0] = 0;
			strcpy(tempB, broj);

			i = preslikavanje(H, tempP);

			H->hashlist[i] = dodajElm(H->hashlist[i], tempI, tempP, tempB);

			break;
		case 4:
			flag = 1;
			break;
		default:
			printf("Dogodila se greška kod promjene kontakta\n");
			break;
		}

	}
	



}