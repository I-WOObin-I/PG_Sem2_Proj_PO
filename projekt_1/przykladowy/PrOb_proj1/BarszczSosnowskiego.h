#pragma once
#include "RoslinaTrujaca.h"

#define SYMBOL_BARSZCZU 'b'
#define KOLORKI_BARSZCZU Kolorki::red, Kolorki::black
#define SILA_BARSZCZU 10
#define BARSZCZ_SIE_ROZPRZESTRZENIA false


class BarszczSosnowskiego :
	public RoslinaTrujaca
{
public:
	BarszczSosnowskiego(Swiat & swiat, const Point & polozenie);
	BarszczSosnowskiego(Swiat & swiat, const Point & polozenie,
		const int &sila);
	~BarszczSosnowskiego();

	void Akcja() override;

	std::string GetNazwa() const override;

	Organizm * wygenerujKopie(const Point & polozenie) override;

};

