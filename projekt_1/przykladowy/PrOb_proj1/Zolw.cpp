#include "Zolw.h"

Zolw::Zolw(Swiat & swiat, const Point & polozenie)
	:Zwierze(swiat, polozenie, SYMBOL_ZOLWIA, SILA_ZOLWIA, INICJATYWA_ZOLWIA, KOLORKI_ZOLWIA,
		DOMYSLNY_ZASIEG_RUCHU, PRAWDOPODOBIENSTWO_WYKONANIA_RUCHU_PRZEZ_ZOLWIA)
{
}

Zolw::Zolw(Swiat & swiat, const Point & polozenie, const int & sila)
	:Zwierze(swiat, polozenie, SYMBOL_ZOLWIA, sila, INICJATYWA_ZOLWIA, KOLORKI_ZOLWIA,
		DOMYSLNY_ZASIEG_RUCHU, PRAWDOPODOBIENSTWO_WYKONANIA_RUCHU_PRZEZ_ZOLWIA)
{
}

Organizm * Zolw::wygenerujKopie(const Point & polozenie)
{
	return new Zolw(this->swiat, polozenie);
}

bool Zolw::CzyTenSamGatunek(Organizm * organizm)
{
	return dynamic_cast<Zolw*>(organizm) != nullptr;
}

bool Zolw::CzyOdbilAtak(Organizm * atakujacy)
{
	if(atakujacy->GetSila() < ZOLW_ODBIJA_ATAKI_OSTRO_SLABSZE_NIZ)
		return true;
	return false;
}

std::string Zolw::GetNazwa() const
{
	return "Zolw";
}

Zolw::~Zolw()
{
}
