#include "Roslina.h"

double Roslina::GetPrawdRozmnozenia()
{
	return prawdopodobienstwo_rozmnozenia_sie;
}

bool Roslina::PodejmijProbeRozmnozeniaSie()
{
	//losowanie szansy
	double los = (double)std::rand() / RAND_MAX;
	if (los > this->GetPrawdRozmnozenia())
		return false;
	//losowanie pola
	Point docelowePole = this->GetPozycja();
	docelowePole.Offset(Point::GetRandomUnitVector());
	//sprawdzenie czy wylosowane pole jest wolne
	Organizm * org = this->swiat.GetOrganizm(docelowePole);
	//pole okupowane, rozmno¿enie siê nieudane
	if (org != nullptr)
		return false;
	//pole wolne, rozmno¿enie siê
	Organizm * dziecko = wygenerujKopie(docelowePole);
	this->swiat.DodajOrganizm(docelowePole, dziecko);
	return true;
}

Roslina::Roslina(Swiat & swiat, const Point & polozenie, const char & symbol, const int & sila,
	const Kolorki::Kolor & kolorFrontu, const Kolorki::Kolor & kolorTla,
	const double &prawdopodobienstwo_rozmnozenia_sie)
	:Organizm(swiat, polozenie, symbol, sila, INICJATYWA_ROSLINY, kolorFrontu, kolorTla), 
	prawdopodobienstwo_rozmnozenia_sie(prawdopodobienstwo_rozmnozenia_sie)
{
}

Roslina::~Roslina()
{
}

void Roslina::Akcja()
{
	if(this->Zywy())
		this->PodejmijProbeRozmnozeniaSie();
}

bool Roslina::Kolizja(Organizm * organizmAtakujacy)
{
	//domyœlnie roœliny nie s¹ w stanie siê obroniæ
	this->Umrzyj(organizmAtakujacy);
	return true;
}
