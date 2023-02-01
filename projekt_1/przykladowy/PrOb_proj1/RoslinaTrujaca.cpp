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
	//bronie siê

	//moja si³a wiêksza od si³y agresora, obroni³em siê, agresor umiera
	if (this->sila > organizmAtakujacy->GetSila())
	{
		organizmAtakujacy->Umrzyj(this);
		return false;
	}
	//nie by³em w stanie siê obroniæ ani uciec, umieram
	else
	{
		this->Umrzyj(organizmAtakujacy);
		return true;
	}
}
