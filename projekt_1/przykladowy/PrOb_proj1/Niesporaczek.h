#pragma once
#include "Organizm.h"

#define SYMBOL_NIESPORACZKA 'B'
#define KOLORKI_NIESPORACZKA Kolorki::white, Kolorki::red
#define SILA_NIESPORACZKA 1
#define INICJATYWA_NIESPORACZKA 1

class Niesporaczek :
	public Organizm
{
public:
	Niesporaczek(Swiat & swiat, const Point & polozenie);

	void Akcja() override;
	bool Kolizja(Organizm * organizmAtakujacy) override;
	//bool CzyTenSamGatunek(Organizm *odpytujacy) override;
	Organizm * wygenerujKopie(const Point & polozenie) override;

	~Niesporaczek();
};

