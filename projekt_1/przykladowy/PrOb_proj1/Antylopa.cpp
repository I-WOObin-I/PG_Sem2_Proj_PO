#include "Antylopa.h"
#include "Zwierze.h"


Antylopa::Antylopa(Swiat & swiat, const Point & polozenie)
	:Zwierze(swiat, polozenie, SYMBOL_ANTYLOPY, SILA_ANTYLOPY, INICJATYWA_ANTYLOPY, KOLORKI_ANTYLOPY,
		ZASIEG_RUCHU_ANTYLOPY)
{
}

Antylopa::Antylopa(Swiat & swiat, const Point & polozenie, const int & sila)
	:Zwierze(swiat, polozenie, SYMBOL_ANTYLOPY, sila, INICJATYWA_ANTYLOPY, KOLORKI_ANTYLOPY)
{
}

Organizm * Antylopa::wygenerujKopie(const Point & polozenie)
{
	return new Antylopa(this->swiat, polozenie);
}

bool Antylopa::CzyTenSamGatunek(Organizm * organizm)
{
	return dynamic_cast<Antylopa*>(organizm);
}

bool Antylopa::WykonajUnik(Organizm * atakujacy)
{
	//je¿eli organizm atakujacy nie jest zwierzêciem to nie wykonuj uniku
	//to jest po to by antylopa nie unika³a ataków barszczu
   	if(dynamic_cast<Zwierze *>(atakujacy) == nullptr)
		return false;

	double los = (double)std::rand() / RAND_MAX;

	//unik nieudany
	/*if (los > SZASNA_NA_UNIK_ANTYLOPY)
		return false;*/

	std::vector<Point> mozliwePoleDoUcieczki = Point::GetOffsetByAllUnitVectors(this->GetPozycja());
	while (mozliwePoleDoUcieczki.size())
	{
		int i = std::rand() % mozliwePoleDoUcieczki.size();
		//pole zajete
		if (this->swiat.GetOrganizm(mozliwePoleDoUcieczki[i]) != nullptr)
		{
			mozliwePoleDoUcieczki.erase(mozliwePoleDoUcieczki.begin() + i);
			continue;
		}
		//pole wolne
		this->swiat.Przenies(this, mozliwePoleDoUcieczki[i]);
		this->swiat.GetKomentator().PowiadomOUniku(this, atakujacy);
		return true;
	}
	//wszystkie sasiednie pola sa zajete
	return false;

}

std::string Antylopa::GetNazwa() const
{
	return "Antylopa";
}

Antylopa::~Antylopa()
{
}
