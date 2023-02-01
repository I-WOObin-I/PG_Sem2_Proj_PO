#pragma once
#include "Roslina.h"
class RoslinaTrujaca :
	public Roslina
{
public:
	RoslinaTrujaca(Swiat & swiat, const Point & polozenie, const char &symbol, const int &sila,
		const Kolorki::Kolor &kolorFrontu, const Kolorki::Kolor &kolorTla,
		const double &prawdopodobienstwo_rozmnozenia_sie = DOMYSLNE_PRAWDOPODOBIENSTWO_ROZMNOZENIA_SIE_ROSLINY);
	virtual ~RoslinaTrujaca();

	virtual bool Kolizja(Organizm * organizmAtakujacy) override;
};

