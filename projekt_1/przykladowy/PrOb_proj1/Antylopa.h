#pragma once
#include "Zwierze.h"

#define SILA_ANTYLOPY			4
#define INICJATYWA_ANTYLOPY		4
#define SYMBOL_ANTYLOPY			'A'
#define KOLORKI_ANTYLOPY		Kolorki::yellow, Kolorki::blue
#define ZASIEG_RUCHU_ANTYLOPY	2
#define SZASNA_NA_UNIK_ANTYLOPY	0.5

class Antylopa :
	public Zwierze
{
public:
	Antylopa(Swiat & swiat, const Point & polozenie);
	Antylopa(Swiat & swiat, const Point & polozenie,
		const int &sila);

	Organizm * wygenerujKopie(const Point & polozenie) override;
	bool CzyTenSamGatunek(Organizm *organizm) override;

	bool WykonajUnik(Organizm * atakujacy) override;

	std::string GetNazwa() const override;

	~Antylopa();
};

