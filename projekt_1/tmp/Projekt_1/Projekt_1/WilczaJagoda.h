#pragma once
#include "Roslina.h"
#define WJAG_SILA 99
#define WJAG_CHAR '%'
#define WJAG_NAZWA "Wilcza Jagoda"

using namespace std;

class WilczaJagoda : public Roslina {
public:
	WilczaJagoda(Swiat* swiat, int x, int y);

	bool Koliduj(Organizm* somsiad, bool czyAtakuje) override;

	Organizm* dajPotomka(Wsp wsp) override;
	bool czyTenSamGatunek(Organizm* o);

	char getChar();
	string getNazwa();

};
