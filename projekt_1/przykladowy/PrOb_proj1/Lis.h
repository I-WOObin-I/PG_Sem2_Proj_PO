#pragma once
#include "Zwierze.h"

#define SILA_LISA		3
#define INICJATYWA_LISA	7
#define SYMBOL_LISA		'L'
#define KOLORKI_LISA	Kolorki::white, Kolorki::darkRed
#define SILNIEJSZY_OSTROSC_ZNAKU >


class Lis :
	public Zwierze
{
public:
	Lis(Swiat & swiat, const Point & polozenie);
	Lis(Swiat & swiat, const Point & polozenie,
		const int &sila);

	Organizm * wygenerujKopie(const Point & polozenie) override;
	bool CzyTenSamGatunek(Organizm *organizm) override;

	//zwraca pole które nie jest okupowane przez silniejszy organizm lub obecne pole je¿eli nie ma takiego pola
	Point GetPoleDocelowe() override;

	std::string GetNazwa() const override;

	~Lis();
};

