#pragma once
#include <string>
#include <typeinfo>

#include "Swiat.h"
#include "Wsp.h"

#define TYP_ZWIERZE 1
#define TYP_ROSLINA 2

using namespace std;

class Swiat;

class Organizm {
protected:
	bool zywy = true;
	int sila;
	int inicjatywa;
	int typ;
	int polog;
	int buff = 0;
	Wsp wsp;
	Swiat* swiat;

	virtual bool czyTenSamGatunek(Organizm* o) = 0;

public:
	Organizm(Swiat* swiat, int x, int y, int sila, int inicjatywa, int typ, int polog);
	virtual void Akcja() = 0;
	virtual bool Koliduj(Organizm* somsiad, bool czyAtakuje) = 0;
	virtual void kolidujDomyslnie(Organizm* somsiad) = 0;
	virtual void inicjujKolizje(Wsp n_wsp) = 0;
	virtual void AktualizujBuffyDebuffy() = 0;

	virtual bool czyGotowyDoRozmnazania();
	virtual void dodajPolog();
	virtual Organizm* dajPotomka(Wsp wsp) = 0;

	void Zabij();
	void Przesun(Wsp n_wsp);
	void dodajBuff(int b);

	int getX();
	int getY();
	int getS();
	int getI();
	int getTyp();
	int getPolog();
	int getBuff();
	bool getZ();
	Wsp getWsp();

	virtual char getChar() = 0;
	virtual string getNazwa() = 0;

	~Organizm();
};