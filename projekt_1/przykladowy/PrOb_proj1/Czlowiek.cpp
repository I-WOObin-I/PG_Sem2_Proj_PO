#include "Czlowiek.h"
#include <conio.h>



bool Czlowiek::AktywyujZdolnoscSpecjalna()
{
	if (cooldownZdolnosci > 0 || pozostalyCzasZdolnosci > 0)
		return false;
	cooldownZdolnosci = COOLDOWN_ZDOLNOSCI_SPECJALNEJ;
	pozostalyCzasZdolnosci = CZAS_TRWANIA_ZDOLNOSCI_SPECJALNEJ;
	ZdolnoscSpecjalna();
	return true;
}

void Czlowiek::ZdolnoscSpecjalna()
{
	//zdolnoœæ nieaktywna
	if (pozostalyCzasZdolnosci == 0)
		return;

	bool odswiez = false;
	std::vector<Organizm*> sasiedzi = this->swiat.GetSasiednieOrganizmy(this->GetPozycja());
	for (auto sasiad : sasiedzi)
	{
		if (sasiad == nullptr)
			continue;
		sasiad->Umrzyj(this);
		odswiez = true;
	}

	//odœwie¿ mapê je¿eli zabi³eœ jakieœ organizmy
	if (odswiez)
		this->swiat.Rysuj();
}

void Czlowiek::TuraZdolnosci()
{
	if (pozostalyCzasZdolnosci > 0)
		--pozostalyCzasZdolnosci;
	else if (cooldownZdolnosci > 0)
		--cooldownZdolnosci;
}

Czlowiek::Czlowiek(Swiat & swiat, const Point & polozenie)
	:Zwierze(swiat, polozenie, SYMBOL_CZLOWIEKA, SILA_CZLOWIEKA, INICJATYWA_CZLOWIEKA, KOLORKI_CZLOWIEKA),
	pozostalyCzasZdolnosci(0), cooldownZdolnosci(0)
{
}

Czlowiek::Czlowiek(Swiat & swiat, const Point & polozenie, const int & sila, 
	const int & zdolnosc, const int & cooldown)
	:Zwierze(swiat, polozenie, SYMBOL_CZLOWIEKA, sila, INICJATYWA_CZLOWIEKA, KOLORKI_CZLOWIEKA),
	pozostalyCzasZdolnosci(zdolnosc), cooldownZdolnosci(cooldown)
{
}

Organizm * Czlowiek::wygenerujKopie(const Point & polozenie)
{
	return new Czlowiek(this->swiat, polozenie);
}

bool Czlowiek::CzyTenSamGatunek(Organizm * organizm)
{
	return dynamic_cast<Czlowiek*>(organizm) != nullptr;
}

Point Czlowiek::GetPoleDocelowe()
{
	Point poleDocelowe = this->GetPozycja();

	char c;
	while (true)
	{
		c = _getch();
		c = tolower(c);
		switch (c)
		{
		case CZLEK_KIER_NORTH:
			poleDocelowe.Offset(Point::North);
			return poleDocelowe;
		case CZLEK_KIER_EAST:
			poleDocelowe.Offset(Point::East);
			return poleDocelowe;
		case CZLEK_KIER_SOUTH:
			poleDocelowe.Offset(Point::South);
			return poleDocelowe;
		case CZLEK_KIER_WEST:
			poleDocelowe.Offset(Point::West);
			return poleDocelowe;
		case CZLEK_ZDOLNOSC:
			this->AktywyujZdolnoscSpecjalna();
			break;
		case CZLEK_PASS:
			return poleDocelowe;
		}
	}
}

void Czlowiek::Akcja()
{
	ZdolnoscSpecjalna();
	if(CzyWykonalRuch())
		for (int i = 0; i < zasiegRuchu; ++i)
		{
			if (!WykonajRuch())
				break;
		}
	ZdolnoscSpecjalna();
	TuraZdolnosci();
}

std::string Czlowiek::GetNazwa() const
{
	return "Czlowiek";
}

std::string Czlowiek::SaveToString() const
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

	//human specific
	DLMTR;
	CONCAT HUGO(this->pozostalyCzasZdolnosci);
	DLMTR;
	CONCAT HUGO(this->cooldownZdolnosci);

	CONCAT NEWLINEDLIMITER;

	return str;
}

Czlowiek::~Czlowiek()
{
}
