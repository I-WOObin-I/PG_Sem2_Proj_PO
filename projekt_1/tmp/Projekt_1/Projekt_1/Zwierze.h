#pragma once
#include <string>

#include "Organizm.h"

using namespace std;

class Zwierze : public Organizm {
public:
	Zwierze(Swiat* swiat, int x, int y, int sila, int inicjatywa, int pelnoletnosc);
	virtual void Akcja() override;
	virtual void AktualizujBuffyDebuffy() override;

protected:
	void inicjujKolizje(Wsp n_wsp) override;
	void kolidujDomyslnie(Organizm* somsiad) override;
	void Kopulacja(Organizm* somsiad);
	bool czyGotowyDoRozmnazania() override;
};