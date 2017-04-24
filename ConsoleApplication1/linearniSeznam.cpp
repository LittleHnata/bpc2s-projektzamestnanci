// linearniSeznam.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "seznam.h"
#include <stdlib.h>


void onNajdi(books *zaznamy) {
	char najdiS[50];
	system("cls");
	getchar();
	printf("Titul: ");
	scanf_s("%[^\n]", najdiS, VELIKOST);
	najdiZaznam(zaznamy, najdiS);
}

void onPridej(books **zaznamy) {
	char autor[VELIKOST];
	char nazev[VELIKOST];
	int strany;
	double hodnoceni;
	system("cls");
	getchar();
	printf("Titul: ");
	scanf_s("%[^\n]", nazev, VELIKOST);
	printf("Autor: ");
	getchar();
	scanf_s("%[^\n]", autor, VELIKOST);
	printf("Pocet stran: ");
	scanf_s("%d", &strany);
	printf("Hodnoceni: ");
	scanf_s("%lf", &hodnoceni);
	pridej(zaznamy, nazev, autor, strany, hodnoceni);
	system("cls");
}

void onEdit(books **zaznamy) {
	char autor[VELIKOST];
	char nazev[VELIKOST];
	int strany;
	double hodnoceni;

	getchar();
	system("cls");
	printf("Titul: ");
	scanf_s("%[^\n]", nazev, VELIKOST);
	books *b = vratZaznam(*zaznamy, nazev);
	system("cls");
	if (b != NULL) {
		tiskRadku(b);
	}
	else
	{
		tiskOddelovace();
		printf("Zaznam nenalezen\n");
		tiskOddelovace();
		return;
	}
	getchar();
	printf("Titul: ");
	scanf_s("%[^\n]", nazev, VELIKOST);
	printf("Autor: ");
	getchar();
	scanf_s("%[^\n]", autor, VELIKOST);
	printf("Pocet stran: ");
	scanf_s("%d", &strany);
	printf("Hodnoceni: ");
	scanf_s("%lf", &hodnoceni);
	system("cls");
	editujZaznam(zaznamy, b, nazev, autor, strany, hodnoceni);
}

void onSmaz(books **zaznamy) {
	char titul[50];
	system("cls");
	getchar();
	printf("Zadej titul ke smazani: ");
	scanf_s("%[^\n]", titul, VELIKOST);
	smaz(zaznamy, titul);
}

int main()
{
	books *seznam;
	seznam = NULL;
	menu volba;

	do
	{
		printf("1:Pridat zaznam\n2:Vypis zaznamu\n3:Najdi titul\n4:Smazat zaznam\n5:Uloz zaznamy\n6:Nacti seznam\n7:Edituj zaznam\n8:Konec\n");
		tiskOddelovace();
		printf("Volba: ");
		if (scanf_s("%d", &volba) != 1) {
			tiskOddelovace();
			printf("Chyba pri nacitani\n");
			tiskOddelovace();
			while ((getchar()) != '\n');
			continue;
		}

		switch (volba)
		{
		case pridat:
		{
			onPridej(&seznam);
			break;
		}
		case vypis:
		{
			system("cls");
			tisk(seznam);
			break;
		}
		case najdi:
		{
			system("cls");
			onNajdi(seznam);
			break;
		}
		case smazat:
		{
			onSmaz(&seznam);
			break;
		}
		case uloz:
		{
			ulozSeznam(seznam);
			system("cls");
			break;
		}
		case nacti:
		{
			nactiSeznam(&seznam);
			break;
		}
		case edituj:
		{
			onEdit(&seznam);
			break;
		}
		case konec:
		{
			printf("Konec\n");
			return 1;
			break;
		}
		default:
		{
			printf("Neznama volba.\n");
			break;
		}
		}
	} while (true);

	return 0;
}

