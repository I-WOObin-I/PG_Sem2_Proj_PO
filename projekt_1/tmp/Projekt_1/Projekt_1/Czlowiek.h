#pragma once
#include <iostream>
#include <conio.h>

#include "KontrolerOrganizmow.h"
#include "Zwierze.h"
#include "Wilk.h"

#define CZLOWIEK_SILA 5
#define CZLOWIEK_INIC 4
#define CZLOWIEK_CHAR '8'
#define CZLOWIEK_POLOG 5
#define CZLOWIEK_PELNOLETNOSC 10
#define CZLOWIEK_NAZWA "Czlowiek"
#define TARCZA_NAPIS "Tarcza Alzura"
#define CZAS_DZIALANIA_TARCZY 5
#define COOLDOWN_TARCZY 5
#define PRZYCISK_TARCZY 't'
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

class Czlowiek : public Zwierze {
private:
	int czasTarczy = 0; // czasTarczy zmniejszany o 1 w kazdej rundzie // 0 - COOLDOWN -> regeneracja tarczy // COOLDOWN - CZAS_DZIALANIA -> czas aktywnej tarczy //
public:
	Czlowiek(Swiat* swiat, int x, int y);

	void Akcja() override;
	bool Koliduj(Organizm* somsiad, bool czyAtakuje) override;

	void dodajPolog() override;
	Organizm* dajPotomka(Wsp wsp) override;
	bool czyTenSamGatunek(Organizm* o);
	void AktualizujBuffyDebuffy() override;

	char getChar();
	string getNazwa() override;
	
};
