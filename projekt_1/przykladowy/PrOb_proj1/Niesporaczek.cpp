#include "Niesporaczek.h"

Niesporaczek::Niesporaczek(Swiat & swiat, const Point & polozenie)
	:Organizm(swiat, polozenie, SYMBOL_NIESPORACZKA, SILA_NIESPORACZKA, INICJATYWA_NIESPORACZKA,
		KOLORKI_NIESPORACZKA)
{
}

void Niesporaczek::Akcja()
{
	Point nowePole(GetPozycja());
	nowePole.Offset(Point::GetRandomUnitVector());
	Organizm * org = swiat.GetOrganizm(nowePole);
	if (org == nullptr)
		swiat.Przenies(this, nowePole);
	else if (org->Kolizja(this))
		swiat.Przenies(this, nowePole);
		
}

bool Niesporaczek::Kolizja(Organizm * organizmAtakujacy)
{
	//bronie siê

	//moja sila wiêksza od si³y agressora, obroni³em siê, agresor umiera
	if (sila > organizmAtakujacy->GetSila())
	{
		organizmAtakujacy->Umrzyj(this);
		return false;
	}
	//nie by³em w stanie siê obroniæ ani uciec, umieram
	else
	{
		Umrzyj(organizmAtakujacy);
		return true;
	}
}

Organizm * Niesporaczek::wygenerujKopie(const Point & polozenie)
{
	Organizm * dziecko = new Niesporaczek(this->swiat, polozenie);
	return dziecko;
}

//bool Niesporaczek::CzyTenSamGatunek(Organizm * odpytujacy)
//{
//	if (Niesporaczek *n = dynamic_cast<Niesporaczek*>(odpytujacy))
//		return true;
//	return false;
//}

Niesporaczek::~Niesporaczek()
{
}
