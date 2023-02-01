#include "RoslinaTrujaca.h"


RoslinaTrujaca::RoslinaTrujaca(Swiat & swiat, const Point & polozenie, const char & symbol, const int & sila, 
	const Kolorki::Kolor & kolorFrontu, const Kolorki::Kolor & kolorTla, 
	const double & prawdopodobienstwo_rozmnozenia_sie)
	:Roslina(swiat, polozenie, symbol, sila, kolorFrontu, kolorTla, prawdopodobienstwo_rozmnozenia_sie)
{
}

RoslinaTrujaca::~RoslinaTrujaca()
{
}

bool RoslinaTrujaca::Kolizja(Organizm * organizmAtakujacy)
{
	//taka sytuacja nie powinna sie zdazyc, ale na wszelki wypadek jest ten warunek tutaj
	if (!this->Zywy())
		return true;
	//bronie si�

	//moja si�a wi�ksza od si�y agresora, obroni�em si�, agresor umiera
	if (this->sila > organizmAtakujacy->GetSila())
	{
		organizmAtakujacy->Umrzyj(this);
		return false;
	}
	//nie by�em w stanie si� obroni� ani uciec, umieram
	else
	{
		this->Umrzyj(organizmAtakujacy);
		return true;
	}
}
