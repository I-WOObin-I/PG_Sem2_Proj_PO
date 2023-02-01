#include "Organizm.h"

char Organizm::GetSymbol() const
{
	return symbolOrganizmu;
}

Organizm::Organizm(Swiat & swiat, const Point & polozenie, const char & symbol, const int & sila,
	const int & inicjatywa, const Kolorki::Kolor & kolorFrontu, const Kolorki::Kolor & kolorTla)

	:swiat(swiat), polozenie(polozenie), symbolOrganizmu(symbol), sila(sila), inicjatywa(inicjatywa),
	kolorSymbolu(kolorFrontu), kolorTla(kolorTla), zywy(true)
{
}

void Organizm::Rysowanie()
{
	Konsola::Wypisz(symbolOrganizmu, polozenie.GetX(), polozenie.GetY(), kolorSymbolu, kolorTla);
}

Point Organizm::GetPozycja() const
{
	return polozenie;
}

void Organizm::SetPozycja(const int & x, const int & y)
{
	SetPozycja(Point(x, y));
}

void Organizm::SetPozycja(const Point & nowePolozenie)
{
	polozenie = nowePolozenie;
}

int Organizm::GetInicjatywa() const
{
	return inicjatywa;
}

int Organizm::GetSila() const
{
	return sila;
}

void Organizm::OffsetSile(const int & przesuniecie)
{
	sila += przesuniecie;
}

Organizm::~Organizm()
{
}

bool Organizm::Zywy()
{
	return zywy;
}

bool Organizm::Umrzyj(Organizm * atakujacy)
{
	//this->swiat.komentator.RelacjonujSmierc(this);cl
	this->swiat.GetKomentator().PowiadomOSmierciOrganizmu(this, atakujacy);
	zywy = false;
	swiat.Zabij(this);
	return true;
}

bool Organizm::CzyOdbilAtak(Organizm * atakujacy)
{
	return false;
}

std::string Organizm::GetNazwa() const
{
	char buf[256];
	sprintf(buf, "%p", this);
	return std::string(buf);
}

std::string Organizm::ToString() const
{
	return std::string(this->GetNazwa() + "(" + std::to_string(this->GetPozycja().GetX()) 
		+ "," +  std::to_string(this->GetPozycja().GetY()) + ")");
}

std::string Organizm::SaveToString() const
{

#define CONCAT str += 
#define DLMTR CONCAT DELIMITER
#define HUGO std::to_string

	std::string str;
	CONCAT this->GetSymbol();
	DLMTR;
	CONCAT HUGO(this->GetPozycja().GetX());
	DLMTR;
	CONCAT HUGO(this->GetPozycja().GetY());
	DLMTR;
	CONCAT HUGO(this->GetSila());

	CONCAT NEWLINEDLIMITER;
	
	return str;
}
