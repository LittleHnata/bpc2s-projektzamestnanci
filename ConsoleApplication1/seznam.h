#ifndef __LINSEZNAM_H__
#define __LINSEZNAM_H__

#define VELIKOST 50
#define platzahodinu 80
struct zamestnanci
{
	char prijmeni[VELIKOST];
	char jmeno[VELIKOST];
	int den;
	int mesic;
	int rok;
	double odp_doba;
	zamestnanci *next;
};

enum menu
{
	pridat = 1,
	vypis,
	najdi,
	smazat,
	uloz,
	nacti,
	edituj,
	vypocti,
	konec
};

static const char filePath[] = "./data.txt";

void ulozSeznam(zamestnanci *zaznamy);
void pridej(zamestnanci **zaznamy, char *prijmeni, char *jmeno, int den, int mesic, int rok, double odp_doba);
void tisk(zamestnanci *b);
void smaz(zamestnanci **zaznamy, char *prijmeni);
void nactiSeznam(zamestnanci **zaznam);
void najdiZaznam(zamestnanci *b, char *najdi);
void tiskRadku(zamestnanci *b);
void editujZaznam(zamestnanci **zaznamy, zamestnanci *stary, char *prijmeni, char *jmeno, int den, int mesic, int rok, double odp_doba);
zamestnanci *vratZaznam(zamestnanci *zaznam, char *prijmeni);
void tiskOddelovace();
char *naMale(char *text);
int porovnani(char *str1, char *str2);

#endif