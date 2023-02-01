#pragma once
#include "Roslina.h"
#define BARSZCZ_SILA 10
#define BARSZCZ_CHAR '$'
#define BARSZCZ_NAZWA "BarszczSosnowskiego"

using namespace std;

class BarszczSosnowskiego : public Roslina {
public:
	BarszczSosnowskiego(Swiat* swiat, int x, int y);

	void Akcja() override;
	bool Koliduj(Organizm* somsiad, bool czyAtakuje) override;

	Organizm* dajPotomka(Wsp wsp) override;
	bool czyTenSamGatunek(Organizm* o);

	char getChar();
	string getNazwa();

};

