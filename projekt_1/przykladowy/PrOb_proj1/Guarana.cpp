#include "Guarana.h"

Guarana::Guarana(Swiat & swiat, const Point & polozenie)
	:Roslina(swiat, polozenie, SYMBOL_GUARANA, DOMYSLNA_SILA_ROSLINY, KOLORKI_GUARANY)
{
}

Guarana::Guarana(Swiat & swiat, const Point & polozenie, const int & sila)
	: Roslina(swiat, polozenie, SYMBOL_GUARANA, sila, KOLORKI_GUARANY)
{
}

Guarana::~Guarana()
{
}

std::string Guarana::GetNazwa() const
{
	return "Guarana";
}

bool Guarana::Kolizja(Organizm * organizmAtakujacy)
{
	//zwi�ksz si�� organizmu kt�ry mnie zjad�
	organizmAtakujacy->OffsetSile(GUARANA_BONUS_DO_SILY);
	//umrzyj :(
	this->Umrzyj(this);
	return true;
}

Organizm * Guarana::wygenerujKopie(const Point & polozenie)
{
	return new Guarana(swiat, polozenie);
}
