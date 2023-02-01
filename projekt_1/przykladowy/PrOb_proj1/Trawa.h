#pragma once
#include "Roslina.h"

#define SYMBOL_TRWAY 't'
#define KOLORKI_TRAWY Kolorki::green, Kolorki::black


class Trawa :
	public Roslina
{
public:
	Trawa(Swiat &swiat, const Point &polozenie);
	Trawa(Swiat & swiat, const Point & polozenie,
		const int &sila);
	~Trawa();

	std::string GetNazwa() const override;

	Organizm * wygenerujKopie(const Point & polozenie) override;
};

