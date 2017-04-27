#include "stdafx.h"
#include "seznam.h"
#include "string.h"
#include "stdlib.h"
#include "iostream"
#include "windows.h"

void pridej(zamestnanci **zaznamy, char *prijmeni, char *jmeno, int den, int mesic, int rok, double odp_doba) //pridava do seznamu
{

	zamestnanci *b = new zamestnanci;
	strcpy_s(b->jmeno, VELIKOST, jmeno);
	strcpy_s(b->prijmeni, VELIKOST, prijmeni);

	b->den = den;
	b->mesic = mesic;
	b->rok = rok;
	b->odp_doba = odp_doba;
	b->next = NULL;

	zamestnanci *temp, *temp2;
	temp = *zaznamy;

		if(temp == NULL) {
			*zaznamy = b;
			return;
		}
		
		if(porovnani(temp->prijmeni, prijmeni) > 0)
		{    *zaznamy = b;
		b->next = temp;
		return;
		}

		temp2 = temp ->next;
				
		while (temp2 != NULL)
		{ 
			if(porovnani(temp2->prijmeni, prijmeni) > 0) {
				temp->next = b;
				return;
			}
		temp = temp2;
		temp2 = temp2->next;
		}

		temp->next = b;
}









void tisk(zamestnanci *b) //tiskne radky s oddelovacem
{
	tiskOddelovace();
	while (b != NULL)
	{
		tiskRadku(b);
		b = b->next;
	}
	tiskOddelovace();
}

void smaz(zamestnanci **zaznamy, char *prijmeni) { //maze urcite veci ze seznamu
	
	zamestnanci *temp, *temp2;
	temp = *zaznamy;

	if (temp) {
		tiskOddelovace();
		printf("Prazdny seznam\n");
		tiskOddelovace();
	}
	if (porovnani(temp->prijmeni, prijmeni) == 0)
		
	
		{
		*zaznamy = temp->next;
		delete temp;
		return;
		}

	temp2 = temp->next;
	while (temp2 != NULL)
	{
		if(porovnani(temp2->prijmeni, prijmeni) == 0){
			temp->next = temp2->next;
			delete temp2;
			return;
		}
		temp = temp2;
		temp2 = temp2->next;
	}
	printf("Zaznam nenalezen\n");
	tiskOddelovace();




	}



void nactiSeznam(zamestnanci **zaznam) { //nacita ze souboru
	FILE *soubor;
	
	system("cls");
	tiskOddelovace();
	if (fopen_s(&soubor, filePath, "r") != 0) {
		printf("Nepodarilo se otevrit soubor.\n");
		tiskOddelovace();
		return;
	}

	char nazev[VELIKOST], autor[VELIKOST];
	int den,mesic,rok;
	double odprhod = 0.0;

	while (!feof(soubor))
	{
		fscanf_s(soubor, "%[^\;];%[^\;];%d;%d;%d;%lf\n", nazev, VELIKOST, autor, VELIKOST, &den, &mesic, &rok, &odprhod);
		pridej(zaznam, nazev, autor, den,mesic,rok, odprhod);
	}

   fclose(soubor);
   printf("Soubor uspesne nacten\n");
   tiskOddelovace();
}

void ulozSeznam(zamestnanci *zaznamy) { //uklada zaznamy do souboru
	FILE *soubor;
	tiskOddelovace();
	if (fopen_s(&soubor, filePath, "w+") != 0) {
		printf("Nepodarilo se otevrit soubor");
		tiskOddelovace();
		return;
	};

	while (zaznamy != NULL)
	{
		fprintf_s(soubor, "%s;%s;%d;%d;%d;%.1lf\n", zaznamy->prijmeni, zaznamy->jmeno, zaznamy->den, zaznamy->mesic, zaznamy->rok, zaznamy->odp_doba);
		zaznamy = zaznamy->next;
	}

	fclose(soubor);
	printf("Soubor uspesne ulozen\n");
	tiskOddelovace();
}


void najdiZaznam(zamestnanci *b, char *najdi) { //hleda zaznamy
	
		tiskOddelovace();
		while(b!=NULL) {
			if(strstr(b->prijmeni, najdi) != NULL){
				tiskRadku(b);
			}
			b=b->next;
		}
		tiskOddelovace();

}

zamestnanci *vratZaznam(zamestnanci *zaznam, char *prijmeni) {
	while (zaznam != NULL)
	{
		if (porovnani(zaznam->prijmeni, prijmeni) == 0) {
			return zaznam;
		}
		zaznam = zaznam->next;
	}
	return NULL;
}

void editujZaznam(zamestnanci **zaznamy, zamestnanci *stary, char *prijmeni, char *jmeno, int den, int mesic, int rok, double odp_doba) { //edituje zaznam
	smaz(zaznamy, stary->prijmeni);
	pridej(zaznamy, prijmeni, jmeno, den, mesic, rok, odp_doba);


}
void vypoctiMzdu(zamestnanci **zaznamy, char *prijmeni, char *jmeno, int mesic, double hodinovasazba) { //vypocitava mzdu za mesic pouze
	double opracdoba=0;
	while (*zaznamy != NULL) {
		if (porovnani((*zaznamy)->prijmeni, prijmeni) == 0 || (porovnani((*zaznamy)->jmeno, jmeno))==0 || (*zaznamy)->mesic==mesic ){
			opracdoba += ((*zaznamy)->odp_doba);
		}
		*zaznamy = (*zaznamy)->next;
	}
	printf("Prijmeni: %-25s Jmeno : %-25s Mesic:%d Vyplata : %lf \n",prijmeni,jmeno,mesic,(opracdoba*hodinovasazba));

}

void tiskOddelovace() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns = 0;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	//rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	for (int i = 0; i < columns - 1; i++)
	{
		printf("=");
	}
	printf("\n");
}

void tiskRadku(zamestnanci *b) {
	printf("Prijmeni: %-25s Jmeno: %-25s  Odpracovane hodiny: %2.1lf Den: %d. %d. %d ", b->prijmeni, b->jmeno, b->odp_doba, b->den, b->mesic, b->rok);
	printf("\n");
}
//porovnani øetìzcù
char *naMale(char *text){
	char *pom;
	pom = new char[strlen(text)];
	for (int i = 0; text[i]; i++)
	{
		pom[i] = tolower(text[i]);
	}
	return pom;
}

int porovnani(char *str1, char *str2){
	return strcmp(naMale(str1), naMale(str2));

}