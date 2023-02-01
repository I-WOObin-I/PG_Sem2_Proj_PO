#include "Komentator.h"
#include "Konsola.h"
#include "Organizm.h"

void Komentator::WymazWiersz(const int & wiersz)
{
	std::string jestemLeniwy = "                                                            ";
	Konsola::Wypisz(jestemLeniwy, punktZaczepienia.GetX(), punktZaczepienia.GetY() + wiersz,
		KOLORKI_GUMKI_KOMENTATORA);
}

void Komentator::WypiszWiersz(const std::string & komunikat)
{
	Konsola::Wypisz(komunikat, punktZaczepienia.GetX(), punktZaczepienia.GetY() + obecnyWiersz,
		KOLORKI_KOMENTATORA);
	obecnyWiersz++;
	if (obecnyWiersz > MAX_WYSOKOSC)
		obecnyWiersz = 0;
	WymazWiersz(obecnyWiersz);
}

Komentator::Komentator(const Point &punktZaczepienia)
	:punktZaczepienia(punktZaczepienia), obecnyWiersz(0)
{
}

void Komentator::Zaczep(const Point & punktZaczepienia)
{
	this->punktZaczepienia = punktZaczepienia;
}

void Komentator::PowiadomONowejTurze(const int & licznikTury)
{
	std::string komunikat = "Rozpoczela sie tura nr. " + std::to_string(licznikTury);
	this->WypiszWiersz(komunikat);
}

void Komentator::PowiadomOSmierciOrganizmu(Organizm * umierajacy, Organizm * zabijajacy)
{
	std::string komunikat;
	if (zabijajacy == nullptr)
		komunikat = umierajacy->ToString() + " umiera";
	else
		komunikat = umierajacy->ToString() + " zostal zabity przez " + zabijajacy->ToString();

	this->WypiszWiersz(komunikat);
}

void Komentator::PowiadomOUniku(Organizm * uniknal, Organizm * tenCoAtakowal)
{
	this->WypiszWiersz(uniknal->ToString() + " wykonal unik przed " + tenCoAtakowal->ToString());
}

Komentator::~Komentator()
{
}
