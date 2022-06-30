#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataType.h"

static int brojArtikala = 0;

void inicijalizacija(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {
		fp = fopen(ime, "wb");

		fwrite(&brojArtikala, sizeof(int), 1, fp);

		fclose(fp);
	}
	else {
		fclose(fp);
	}
}

void dodajArtikl(const char* const ime) {

	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Dodavanje clanova u datoteku");
		exit(EXIT_FAILURE);
	}

	fread(&brojArtikala, sizeof(int), 1, fp);
	printf("Broj clanova: %d\n", brojArtikala);

	ARTIKL temp = { 0 };

	temp.id = brojArtikala + 1;

	getchar();

	printf("Unesite ime: ");
	scanf("%24[^\n]", temp.ime);
	getchar();

	printf("Unesite broj godina odlezanosti: ");
	scanf("%d", &temp.starost);
	getchar();

	printf("unesite vrstu pica: ");
	scanf("%24[^\n]", temp.vrsta);
	getchar();

	printf("unesite cijenu artikla: ");
	scanf("%f", &temp.cijena);
	getchar();

	printf("unesite kolicinu artikla: ");
	scanf("%d", &temp.kolicina);
	getchar();

	fseek(fp, sizeof(ARTIKL) * brojArtikala, SEEK_CUR);
	fwrite(&temp, sizeof(ARTIKL), 1, fp);

	rewind(fp);

	brojArtikala++;

	fwrite(&brojArtikala, sizeof(int), 1, fp);
	fclose(fp);
}

void* ucitajArtikl(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {
		perror("Ucitavanje clanova iz datoteke");
		exit(EXIT_FAILURE);
	}

	fread(&brojArtikala, sizeof(int), 1, fp);
	printf("Broj artikala: %d\n", brojArtikala);

	ARTIKL* poljeArtikala = (ARTIKL*)calloc(brojArtikala, sizeof(ARTIKL));

	if (poljeArtikala == NULL) {
		perror("Zauzimanje memorije za polje artikala.");
		return NULL;

	}

	fread(poljeArtikala, sizeof(ARTIKL), brojArtikala, fp);

	printf("Svi artikli ucitani..\n");

	return poljeArtikala;
}

void zamjena(ARTIKL* const veci, ARTIKL* const manji) {
	ARTIKL temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}


void* sortiraj(ARTIKL* polje) {
	int min = -1;
	for (int i = 0; i < brojArtikala - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < brojArtikala; j++)
		{
			if ((polje + j)->cijena < (polje + min)->cijena) {
				min = j;
			}
		}
		zamjena((polje + i), (polje + min));
	}

	return polje;
}

void ispisiSortiraneArtikle (const ARTIKL* polje){
	
	if (brojArtikala == 0) {
		printf("Polje automobila prazno\n");
		return;
	}


		polje = sortiraj(polje);
	

	for (int i = 0; i < brojArtikala; i++) {
		printf("ID: %d\tIme: %s\tstarost: %d\tvrsta: %s\tcijena: %.2f\tkolicina: %d\n\n",
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->starost,
			(polje + i)->vrsta,
			(polje + i)->cijena,
			(polje + i)->kolicina);
	}
}


void ispisiArtikl(const ARTIKL* const polje) {

	if (polje == NULL) {
		printf("Polje artikala prazno");
		return;
	}

	int i;

	for (i = 0; i < brojArtikala; i++) {
		printf("ID: %d\tIme: %s\tstarost: %d\tvrsta: %s\tcijena: %.2f\tkolicina: %d\n\n", 
							(polje + i)->id, 
							(polje + i)->ime, 
							(polje + i)->starost, 
							(polje + i)->vrsta, 
							(polje + i)->cijena, 
							(polje + i)->kolicina);
	}
}

void* pretrazivanje(ARTIKL* const polje) {

	if (polje == NULL) {
		printf("Polje artikala prazno");
		return NULL;
	}

	int i;

	int trazeniId;

	printf("Unesite ID artikla kojeg trazite: ");
	scanf("%d", &trazeniId);

	for (i = 0; i < brojArtikala; i++) {

		if (trazeniId == (polje + i)->id) {
			printf("artikl pronaden.\n");

			return (polje + i);
		}
	}

	return NULL;
}

void brisanjeArtikla(ARTIKL* const polje, const char* const dat) {

	if (brojArtikala == 0) {
		printf("Polje artikala je prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Brisanje artikala");
		exit(EXIT_FAILURE);
	}

	fseek(fp, sizeof(int), SEEK_CUR);

	int i, trazeniId;

	printf("Unesite ID artikla kojeg zelite obrisati: ");

	do {
		scanf("%d", &trazeniId);
		if (trazeniId < 1 || trazeniId > brojArtikala) {
			printf("Artikl s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojArtikala);

	ARTIKL* poljeArtikala = (ARTIKL*)calloc(brojArtikala - 1, sizeof(ARTIKL));

	int counter = 0;

	for (i = 0; i < brojArtikala; i++) {

		if (trazeniId != (polje + i)->id) {
			*(poljeArtikala + counter) = *(polje + i);

			if ((poljeArtikala + counter)->id > trazeniId) {
				(poljeArtikala + counter)->id -= 1;
			}

			fwrite((poljeArtikala + counter), sizeof(ARTIKL), 1, fp);
			counter++;
		}
	}

	free(poljeArtikala);
	poljeArtikala = NULL;

	rewind(fp);

	fwrite(&counter, sizeof(int), 1, fp);
	fclose(fp);

	printf("Artikl je uspjesno obrisan\n");
}

int izlaz(ARTIKL* polje) {

	free(polje);

	return 0;
}