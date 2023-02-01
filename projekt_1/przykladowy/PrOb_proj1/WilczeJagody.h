#pragma once
#include "RoslinaTrujaca.h"

#define SYMBOL_WILCZEJ_JAGODY 'w'
#define KOLORKI_WILCZEJ_JAGODY Kolorki::darkPurple, Kolorki::black
#define SILA_WILCZEJ_JAGODY 99


class WilczeJagody :
	public RoslinaTrujaca
{
public:
	WilczeJagody(Swiat & swiat, const Point & polozenie);
	WilczeJagody(Swiat & swiat, const Point & polozenie,
		const int &sila);
	~WilczeJagody();

	std::string GetNazwa() const override;

	Organizm * wygenerujKopie(const Point & polozenie) override;
};

