#include "BarszczSosnowskiego.h"
#include "Zwierze.h"

BarszczSosnowskiego::BarszczSosnowskiego(Swiat & swiat, const Point & polozenie)
	:RoslinaTrujaca(swiat, polozenie, SYMBOL_BARSZCZU, SILA_BARSZCZU, KOLORKI_BARSZCZU)
{
}

BarszczSosnowskiego::BarszczSosnowskiego(Swiat & swiat, const Point & polozenie, const int & sila)
	: RoslinaTrujaca(swiat, polozenie, SYMBOL_BARSZCZU, sila, KOLORKI_BARSZCZU)
{
}

BarszczSosnowskiego::~BarszczSosnowskiego()
{
}

void BarszczSosnowskiego::Akcja()
{
	if (!this->Zywy())
		return;
	//??? czy barszcz te¿ ma siê rozprzestrzeniaæ ???
	//zak³adam ¿e nie
	std::vector<Point> otoczenie = Point::GetOffsetByAllUnitVectors(this->GetPozycja());
	for (auto pole : otoczenie)
	{
		Organizm * org = this->swiat.GetOrganizm(pole);
		//pusty s¹siad
		if (org == nullptr)
			continue;
		//s¹siad jest zwierzêciem, zabij!
		else if (dynamic_cast<Zwierze*>(org) != nullptr)
 			org->Kolizja(this);
	}

#if BARSZCZ_SIE_ROZPRZESTRZENIA
	this->PodejmijProbeRozmnozeniaSie();
#endif // BARSZCZ_SIE_ROZPRZESTRZENIA


}

std::string BarszczSosnowskiego::GetNazwa() const
{
	return "Barszcz";
}

Organizm * BarszczSosnowskiego::wygenerujKopie(const Point & polozenie)
{
	return new BarszczSosnowskiego(this->swiat, polozenie);
}
