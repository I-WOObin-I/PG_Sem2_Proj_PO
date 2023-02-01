#pragma once
#include "Roslina.h"

#define SYMBOL_GUARANA 'g'
#define KOLORKI_GUARANY Kolorki::purple, Kolorki::black
#define GUARANA_BONUS_DO_SILY 3

class Guarana :
	public Roslina
{
public:
	Guarana(Swiat &swiat, const Point &polozenie);
	Guarana(Swiat & swiat, const Point & polozenie,
		const int &sila);
	~Guarana();

	std::string GetNazwa() const override;

	bool Kolizja(Organizm * organizmAtakujacy) override;

	Organizm * wygenerujKopie(const Point &polozenie) override;
};

