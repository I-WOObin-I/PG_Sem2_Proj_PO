#pragma once
#include <time.h>
#include <string>

#include "Organizm.h"

#define SZANSA_ROZMN 25

using namespace std;

class Roslina : public Organizm {
public:
	Roslina(Swiat* swiat, int x, int y, int sila);
	virtual void Akcja() override;
	virtual void AktualizujBuffyDebuffy() override;

protected:
	void inicjujKolizje(Wsp n_wsp) override;
	void kolidujDomyslnie(Organizm* somsiad) override;
};