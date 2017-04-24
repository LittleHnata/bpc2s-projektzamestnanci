// linearniSeznam.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "seznam.h"
#include <stdlib.h>


void onNajdi(zamestnanci *zaznamy) {
	char prijmeni[50];
	system("cls");
	getchar();
	printf("Prijmeni: ");
	scanf_s("%[^\n]", prijmeni, VELIKOST);
	najdiZaznam(zaznamy, prijmeni);
}

void onPridej(zamestnanci **zaznamy) {
	char autor[VELIKOST];
	char prijmeni[VELIKOST];
	int den,mesic,rok;
	double odprdoba,od,doc;
	system("cls");
	getchar();
	printf("Prijmeni: ");
	scanf_s("%[^\n]", prijmeni, VELIKOST);
	printf("Jmeno: ");
	getchar();
	scanf_s("%[^\n]", autor, VELIKOST);
	printf("Den: ");
	scanf_s("%d", &den);
	printf("Mesic: ");
	scanf_s("%d", &mesic);
	printf("Rok: ");
	scanf_s("%d", &rok);
	printf("Zacatek smeny: ");
	scanf_s("%lf", &od);
	printf("Konec smeny: ");
	scanf_s("%lf", &doc);
	if (od>doc) {
		odprdoba = od - doc;
	}
	else {
		odprdoba = doc - od;
	}
	pridej(zaznamy, prijmeni, autor, den, mesic, rok ,odprdoba);
	system("cls");
}

void onEdit(zamestnanci **zaznamy) {
	char autor[VELIKOST];
	char prijmeni[VELIKOST];
	int den, mesic, rok;
	double odprdoba;

	getchar();
	system("cls");
	printf("Prijmeni: ");
	scanf_s("%[^\n]", prijmeni, VELIKOST);
	zamestnanci *b = vratZaznam(*zaznamy, prijmeni);
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
	printf("Prijmeni: ");
	scanf_s("%[^\n]", prijmeni, VELIKOST);
	printf("Jmeno: ");
	getchar();
	scanf_s("%[^\n]", autor, VELIKOST);
	printf("Den: ");
	scanf_s("%d", &den);
	printf("Mesic: ");
	scanf_s("%d", &mesic);
	printf("Rok: ");
	scanf_s("%d", &rok);
	printf("Odpracovana doba: ");
	scanf_s("%lf", &odprdoba);
	system("cls");
	editujZaznam(zaznamy, b, prijmeni, autor, den, mesic, rok, odprdoba);
}

void onSmaz(zamestnanci **zaznamy) {
	char prijmeni[50];
	system("cls");
	getchar();
	printf("Zadej zamestnance ke smazani: ");
	scanf_s("%[^\n]", prijmeni, VELIKOST);
	smaz(zaznamy, prijmeni);
}

int main()
{
	zamestnanci *seznam;
	seznam = NULL;
	menu volba;

	do
	{
		printf("1:Pridat zaznam\n2:Vypis zaznamu\n3:Najdi zamestnance\n4:Smazat zaznam\n5:Uloz zaznamy\n6:Nacti seznam\n7:Edituj zaznam\n8:Vypocti vyplatu\n9:Konec\n");
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
		case vypocti:
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

