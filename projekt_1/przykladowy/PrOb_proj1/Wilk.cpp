#include "Wilk.h"

Wilk::Wilk(Swiat & swiat, const Point & polozenie)
	:Zwierze(swiat, polozenie, SYMBOL_WILKA, SILA_WILKA, INICJATYWA_WILKA, KOLORKI_WILKA)
{
}

Wilk::Wilk(Swiat & swiat, const Point & polozenie, const int & sila)
	:Zwierze(swiat, polozenie, SYMBOL_WILKA, sila, INICJATYWA_WILKA, KOLORKI_WILKA)
{
}

Organizm * Wilk::wygenerujKopie(const Point & polozenie)
{
	Organizm * dziecko = new Wilk(this->swiat, polozenie);
	return dziecko;
}

bool Wilk::CzyTenSamGatunek(Organizm * organizm)
{
	return dynamic_cast<Wilk*>(organizm) != nullptr;
}

std::string Wilk::GetNazwa() const
{
	return "Wilk";
}

Wilk::~Wilk()
{
}
