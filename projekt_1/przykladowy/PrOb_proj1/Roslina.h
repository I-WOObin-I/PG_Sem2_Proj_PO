#pragma once
#include "Organizm.h"

#define INICJATYWA_ROSLINY 0
#define DOMYSLNA_SILA_ROSLINY 0
#define DOMYSLNE_PRAWDOPODOBIENSTWO_ROZMNOZENIA_SIE_ROSLINY 0.1

class Roslina :
	public Organizm
{
private:
	double prawdopodobienstwo_rozmnozenia_sie;
protected:
	double GetPrawdRozmnozenia();
	bool PodejmijProbeRozmnozeniaSie();
public:
	Roslina(Swiat & swiat, const Point & polozenie, const char &symbol, const int &sila, 
		const Kolorki::Kolor &kolorFrontu, const Kolorki::Kolor &kolorTla,
		const double &prawdopodobienstwo_rozmnozenia_sie = DOMYSLNE_PRAWDOPODOBIENSTWO_ROZMNOZENIA_SIE_ROSLINY);
	virtual ~Roslina();

	virtual void Akcja() override;
	virtual bool Kolizja(Organizm * organizmAtakujacy) override;
};

