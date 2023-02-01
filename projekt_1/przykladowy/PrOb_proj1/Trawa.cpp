#include "Trawa.h"

Trawa::Trawa(Swiat & swiat, const Point & polozenie)
	:Roslina(swiat, polozenie, SYMBOL_TRWAY, DOMYSLNA_SILA_ROSLINY, KOLORKI_TRAWY)
{
}

Trawa::Trawa(Swiat & swiat, const Point & polozenie, const int & sila)
	:Roslina(swiat, polozenie, SYMBOL_TRWAY, sila, KOLORKI_TRAWY)
{
}

Trawa::~Trawa()
{
}

std::string Trawa::GetNazwa() const
{
	return "Trawa";
}

Organizm * Trawa::wygenerujKopie(const Point & polozenie)
{
	return new Trawa(swiat, polozenie);
}
