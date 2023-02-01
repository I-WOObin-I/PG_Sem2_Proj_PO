#pragma once
#include "Zwierze.h"

#define SILA_WILKA 9
#define INICJATYWA_WILKA 5
#define SYMBOL_WILKA 'W'
#define KOLORKI_WILKA Kolorki::white, Kolorki::grey

class Wilk :
	public Zwierze
{
public:
	Wilk(Swiat & swiat, const Point & polozenie);
	Wilk(Swiat & swiat, const Point & polozenie,
		const int &sila);

	Organizm * wygenerujKopie(const Point & polozenie) override;
	bool CzyTenSamGatunek(Organizm *organizm) override;

	std::string GetNazwa() const override;

	~Wilk();
};

