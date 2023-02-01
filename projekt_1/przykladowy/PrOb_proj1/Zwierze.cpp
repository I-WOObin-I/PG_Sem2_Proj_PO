#include "Zwierze.h"

bool Zwierze::WykonajRuch()
{
	Point poleDocelowe = this->GetPoleDocelowe();
	//brak pola które spe³ania³oby kryteria kardynalnego -- patrz specfyikacje ró¿nych zwierz¹t
	if (poleDocelowe == this->GetPozycja())
		return false;
	Organizm * org = this->swiat.GetOrganizm(poleDocelowe);
	if (org == nullptr)
	{
		this->swiat.Przenies(this, poleDocelowe);
		return true;
	}
	else if (CzyTenSamGatunek(org))
	{
		RozmnozSie(org);
		return false;
	}
	else if (org->Kolizja(this))
	{
		swiat.Przenies(this, poleDocelowe);
		return false;
	}
}

bool Zwierze::RozmnozSie(Organizm *partner)
{
	std::vector<Point> pola = GetPolaDlaDzieci(partner);

	while (pola.size() > 0)
	{
		int index = std::rand() % pola.size();
		if (this->swiat.GetOrganizm(pola[index]) == nullptr)
		{
			Organizm *dziecko = this->wygenerujKopie(pola[index]);
			this->swiat.DodajOrganizm(pola[index], dziecko);
			return true;
		}
		pola.erase(pola.begin() + index);
	}
	return false;
}

Point Zwierze::GetPoleDocelowe()
{
	Point poleDocelowe = this->GetPozycja();
	Point kierunek = Point::GetRandomUnitVector();
	//for(int i =0; i < zasiegRuchu; ++i)
		poleDocelowe.Offset(kierunek);

	return poleDocelowe;
}

std::vector<Point> Zwierze::GetPolaDlaDzieci(Organizm * partner)
{
	std::vector<Point> wersory = Point::GetAllUnitVectors();
	std::vector<Point> ja, drugi;
	for (int i = 0; i < wersory.size(); ++i)
	{
		ja.push_back(this->GetPozycja());
		drugi.push_back(this->GetPozycja());
		ja[i].Offset(wersory[i]);
		drugi[i].Offset(wersory[i]);
	}
	ja.insert(ja.end(), drugi.begin(), drugi.end());

	return ja;
}

bool Zwierze::CzyWykonalRuch()
{
	double los = (double)std::rand() / RAND_MAX;
	if (los <= szansaWykonaniaRuchu)
		return true;
	return false;
}

bool Zwierze::WykonajUnik(Organizm * atakujacy)
{
	return false;
}

Zwierze::Zwierze(Swiat & swiat, const Point & polozenie, const char & symbol, const int & sila,
	const int & inicjatywa, const Kolorki::Kolor & kolorFrontu, const Kolorki::Kolor & kolorTla, 
	const int &zasiegRuchu, const double &szansaWykonaniaRuchu)
	:Organizm(swiat, polozenie, symbol, sila, inicjatywa, kolorFrontu, kolorTla), zasiegRuchu(zasiegRuchu),
	szansaWykonaniaRuchu(szansaWykonaniaRuchu)
{
}

Zwierze::~Zwierze()
{
}

void Zwierze::Akcja()
{
	if(this->Zywy() && this->CzyWykonalRuch())
		for (int i = 0; i < zasiegRuchu; ++i)
		{
			//zak³adam ¿e walka lub rozmno¿enie siê wyczerpuje wszystkie punkty ruchu
			if (!WykonajRuch())
				break; 
		}
}

bool Zwierze::Kolizja(Organizm * organizmAtakujacy)
{
	//Jestem atakowany!

	if (this->sila > organizmAtakujacy->GetSila())
	{
		//moja sila jest wiêksza, obroni³em siê!
		if(!organizmAtakujacy->CzyOdbilAtak(this))
			organizmAtakujacy->Umrzyj(this); //je¿eli agresor nie jest w stanie odbiæ mojego ataku to umiera
		return false;
	}
	else
	{
		//nie by³em w staniê siê obroniæ
		//próbujê wykonaæ unik
		if (this->WykonajUnik(organizmAtakujacy))
			//udalo mi siê wykonaæ unik, prze¿y³em ale musia³em zwolniæ pole
			return true;
		//nie uda³o siê wykonaæ uniku, próbujê odbiæ atak
		else if (this->CzyOdbilAtak(organizmAtakujacy))
			//odbilem atak!, zostajê na swoim polu, agresor wraca na swoje poprzednie pole
			return false;
		//nic nie zadzia³a³o, umieram :(
		else
		{
			this->Umrzyj(organizmAtakujacy);
			return true;
		}
		
	}
}
