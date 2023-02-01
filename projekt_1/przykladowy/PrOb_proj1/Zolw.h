#pragma once
#include "Zwierze.h"

#define SILA_ZOLWIA			2
#define INICJATYWA_ZOLWIA	1
#define SYMBOL_ZOLWIA		'z'
#define KOLORKI_ZOLWIA		Kolorki::green, Kolorki::darkGreen
#define PRAWDOPODOBIENSTWO_WYKONANIA_RUCHU_PRZEZ_ZOLWIA 0.25
#define ZOLW_ODBIJA_ATAKI_OSTRO_SLABSZE_NIZ 5


class Zolw :
	public Zwierze
{
public:
	Zolw(Swiat & swiat, const Point & polozenie);
	Zolw(Swiat & swiat, const Point & polozenie,
		const int &sila);

	Organizm * wygenerujKopie(const Point & polozenie) override;
	bool CzyTenSamGatunek(Organizm *organizm) override;

	bool CzyOdbilAtak(Organizm *atakujacy) override;

	std::string GetNazwa() const override;

	~Zolw();
};

