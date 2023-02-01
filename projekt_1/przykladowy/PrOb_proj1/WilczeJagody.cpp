#include "WilczeJagody.h"


WilczeJagody::WilczeJagody(Swiat & swiat, const Point & polozenie)
	:RoslinaTrujaca(swiat, polozenie, SYMBOL_WILCZEJ_JAGODY, SILA_WILCZEJ_JAGODY, KOLORKI_WILCZEJ_JAGODY)
{
}

WilczeJagody::WilczeJagody(Swiat & swiat, const Point & polozenie, const int & sila)
	:RoslinaTrujaca(swiat, polozenie, SYMBOL_WILCZEJ_JAGODY, sila, KOLORKI_WILCZEJ_JAGODY)
{
}

WilczeJagody::~WilczeJagody()
{
}

std::string WilczeJagody::GetNazwa() const
{
	return "WilJag";
}

Organizm * WilczeJagody::wygenerujKopie(const Point & polozenie)
{
	return new WilczeJagody(this->swiat, polozenie);
}
