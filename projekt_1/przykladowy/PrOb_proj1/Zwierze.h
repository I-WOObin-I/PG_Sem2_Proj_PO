#pragma once
#include "Organizm.h"

#define DOMYSLNY_ZASIEG_RUCHU 1
#define DOMYSLNA_SZANSA_WYKOANIA_RUCHU 1

class Zwierze :
	public Organizm
{
protected:
	//wykonuje ruch, zwraca true je¿eli zwierze wykona³o ruch bez walki lub rozmno¿enia siê
	//zwraca false je¿eli stoczy³o walkê lub siê rozmno¿y³o
	virtual bool WykonajRuch();
	virtual bool CzyTenSamGatunek(Organizm *organizm) = 0;
	virtual bool RozmnozSie(Organizm *partner);
	int zasiegRuchu;
	virtual Point GetPoleDocelowe();
	std::vector<Point> GetPolaDlaDzieci(Organizm *partner);
	double szansaWykonaniaRuchu;
	bool CzyWykonalRuch();
	virtual bool WykonajUnik(Organizm * atakujacy);

public:
	Zwierze(Swiat & swiat, const Point & polozenie, const char &symbol, const int &sila,
		const int &inicjatywa, const Kolorki::Kolor &kolorFrontu, const Kolorki::Kolor &kolorTla,
		const int &zasiegRuchu = DOMYSLNY_ZASIEG_RUCHU, 
		const double &szansaWykonaniaRuchu = DOMYSLNA_SZANSA_WYKOANIA_RUCHU);
	virtual ~Zwierze();

	virtual void Akcja() override;
	virtual bool Kolizja(Organizm * organizmAtakujacy) override;
};

