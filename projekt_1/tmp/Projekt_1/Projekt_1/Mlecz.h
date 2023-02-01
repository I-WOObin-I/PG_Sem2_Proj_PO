#pragma once
#include "Roslina.h"
#define MLECZ_SILA 0
#define MLECZ_CHAR '*'
#define MLECZ_NAZWA "Mlecz"

using namespace std;

class Mlecz : public Roslina {
public:
	Mlecz(Swiat* swiat, int x, int y);

	void Akcja() override;
	bool Koliduj(Organizm* somsiad, bool czyAtakuje) override;

	Organizm* dajPotomka(Wsp wsp) override;
	bool czyTenSamGatunek(Organizm* o);

	char getChar();
	string getNazwa();

};
