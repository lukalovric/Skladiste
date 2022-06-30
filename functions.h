#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "dataType.h"

int izbornik(const char* const);
void inicijalizacija(const char* const);
void dodajArtikl(const char* const);
void* ucitajArtikl(const char* const);
void ispisiArtikl(const ARTIKL* const);
void brisanjeArtikla(ARTIKL* const, const char* const);
void* pretrazivanje(ARTIKL* const);
void zamjenaCijena(ARTIKL* const, ARTIKL* const);
void* sortiraj( char*);
void ispisiSortiraneArtikle(const ARTIKL* polje);
#endif
