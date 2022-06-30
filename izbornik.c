#define _CRT_SECURE_NO_WARNINGS

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int izbornik(const char* const ime) {

	printf("-------------------------\n\n");
	printf("Odaberite jednu od ponudenih opcija\n\n");
	printf("-------------------------\n\n");
	printf("Opcija 1: Dodavanje clanova\n");
	printf("Opcija 2: Sortiranje po cijeni\n");
	printf("Opcija 3: Ispisivanje svih clanova\n");
	printf("Opcija 4: Pretrazivanje clanova po ID-u\n");
	printf("Opcija 5: Brisanje artikla\n");
	printf("Opcija 6: Zavrsetak programa\n\n");
	printf("-------------------------\n\n");

	int uvijet = 0;

	static ARTIKL* poljeArtikala = NULL;
	static ARTIKL* pronadeniArtikl = NULL;

	scanf("%d", &uvijet);
	system("cls");

	switch (uvijet) {
	case 1:

		dodajArtikl(ime);

		break;

	case 2:
		if (poljeArtikala != NULL) {
			free(poljeArtikala);
			poljeArtikala = NULL;
		}

		poljeArtikala=(ARTIKL*)ucitajArtikl(ime);

		ispisiSortiraneArtikle(poljeArtikala);

		break;
	case 3:
		if (poljeArtikala != NULL) {
			free(poljeArtikala);
		}

		poljeArtikala = (ARTIKL*)ucitajArtikl(ime);

		ispisiArtikl(poljeArtikala); 

		break;
	case 4:
		if (poljeArtikala != NULL) {
			free(poljeArtikala);
		}

		poljeArtikala = (ARTIKL*)ucitajArtikl(ime);

		pronadeniArtikl = (ARTIKL*)pretrazivanje(poljeArtikala);

		if (pronadeniArtikl != NULL) {
			printf("ID: %d\n", pronadeniArtikl->id);
			printf("Ime: %s\n", pronadeniArtikl->ime);
			printf("starost artikla: %d\n", pronadeniArtikl->starost);
			printf("vrsta artikla: %s\n", pronadeniArtikl->vrsta);
			printf("cijena artikla: %d\n", pronadeniArtikl->cijena);
			printf("kolicina artikla: %d\n", pronadeniArtikl->kolicina);
		}
		else {
			printf("Ne postoji artikl s tim ID-em");
		}

		break;
	case 5:

		if (poljeArtikala != NULL) {
			free(poljeArtikala);
			poljeArtikala = NULL;
		}

		poljeArtikala = (ARTIKL*)ucitajArtikl(ime);

		ispisiSortiraneArtikle(poljeArtikala);
		break;
	case 6:

		uvijet = izlaz(poljeArtikala);
		break;
	default:
		uvijet = 0;
	}

	return uvijet;
}