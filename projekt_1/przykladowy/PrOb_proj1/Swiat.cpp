#pragma once
#include <chrono>
#include <thread>
#include <fstream>
#include "Swiat.h"
#include "LogError3.h"

//prawdopodobienista umieszczenia na mapie przy zaludnianiu œwiata
#include "SwiatPrawdopodobienstwa.h"

//organizmy
#include "ListaWszystkichOrganizmow.h"

//sta³e
#include "Swiat_STALE.h"

void Swiat::zaiinicjujNoweOrganizmy()
{
	//brak organizmow do dodania
	if (nowoDodaneOrganizmy.size() == 0)
		return;
	while (nowoDodaneOrganizmy.size() > 0)
	{
		kolejkaOrganizmow.push_back(nowoDodaneOrganizmy.front());
		nowoDodaneOrganizmy.pop();
	}
	this->SortujOrganizmy();
}

void Swiat::WykonajZadania()
{
	while (doZabicia.size() > 0)
	{
		ZabijNow(doZabicia.front());
		doZabicia.pop();
	}
	while (doPrzeniesienia.size() > 0)
	{
		PrzeniesNow(doPrzeniesienia.front());
		doPrzeniesienia.erase(doPrzeniesienia.begin());
	}
}

Point Swiat::WrapPoint(const Point & point)
{
	Point p = point;
	if (point.GetX() < 0)
		p.OffsetX(width);
	if (point.GetX() >= width)
		p.OffsetX(-width);
	if (point.GetY() < 0)
		p.OffsetY(height);
	if (point.GetY() >= height)
		p.OffsetY(-height);
	return p;
}

void Swiat::ZaludnijSwiat(const double & procentZaludnienia)
{
	int l_organizmow = 1;
	//DODANIE CZ£OWIEKA
	DodajOrganizm(Point::GetRandomPoint(0, 0, this->width, this->height), new Czlowiek(*this, Point()), false);

#ifdef TEST_ILOSC_ORGANIZMOW
	double docelowaPopulacja = TEST_ILOSC_ORGANIZMOW;
#else
	double docelowaPopulacja = procentZaludnienia * width * height;
#endif // TEST_ILOSC_ORGANIZMOW

	docelowaPopulacja = floor(docelowaPopulacja);
	while (l_organizmow < docelowaPopulacja)
	{
		int x = std::rand() % width, y = std::rand() % height;
		if (organizmy[y][x] == nullptr)
		{
			DodajOrganizm(Point(x, y), nullptr, false);
			++l_organizmow;
			int inicjatywa = std::rand() % 10;
			//organizmy[y][x]->SetInicjatywa(inicjatywa);
		}
	}
	zaiinicjujNoweOrganizmy();
	SortujOrganizmy();
	/*while (kolejkaOrganizmow.size() > 0)
	{
		Organizm * org = kolejkaOrganizmow.top();
		kolejkaOrganizmow.pop();
	}*/
}

void Swiat::DodajOrganizm(const Point & polozenie, Organizm * organizm, bool sortuj)
{
	Point wrappedPoint = WrapPoint(polozenie);
	//nielegalna operacja, pole jest ju¿ okupowane
	if (organizmy[wrappedPoint.GetY()][wrappedPoint.GetX()] != nullptr)
		return;
	Organizm * org = organizm;
	if (org == nullptr)
		org = GenerujLosowyOrganizm(wrappedPoint);
	else
		org->SetPozycja(wrappedPoint);

	//org->SetPozycja(WrapPoint(org->GetPozycja()));
	organizmy[wrappedPoint.GetY()][wrappedPoint.GetX()] = org;
	nowoDodaneOrganizmy.push(org);
	//kolejkaOrganizmow.push_back(org);
	/*if (sortuj)
		SortujOrganizmy();*/
}

Organizm * Swiat::GenerujLosowyOrganizm(const Point & polozenie)
{
	//TODO
	Organizm * organizm = nullptr;
	double los = (double)std::rand() / RAND_MAX;

	PrawdopodbienstwaOrganizmow typ = pSUMA;
	double przedzial = 0;
	for (int i = 0; i < pSUMA; ++i)
	{
		przedzial += Prwdpdbnstwo[i];
		if (los <= przedzial)
		{
			typ = PrawdopodbienstwaOrganizmow(i);
			break;
		}
	}
	//przypadek niedko³adnoœci dodawnia liczb zmienno-przecinkowych
	if (przedzial > 0.9999 && typ == pSUMA)
		typ = PrawdopodbienstwaOrganizmow(pSUMA - 1);

	switch (typ)
	{
	case pTrawa:
		organizm = new Trawa(*this, polozenie);
		break;
	case pMlecz:
		organizm = new Mlecz(*this, polozenie);
		break;
	case pGuarana:
		organizm = new Guarana(*this, polozenie);
		break;
	case pWilczeJagody:
		organizm = new WilczeJagody(*this, polozenie);
		break;
	case pBarszczSosnowskiego:
		return new BarszczSosnowskiego(*this, polozenie);
		break;
	case pWilk:
		organizm = new Wilk(*this, polozenie);
		break;
	case pOwca:
		organizm = new Owca(*this, polozenie);
		break;
	case pLis:
		organizm = new Lis(*this, polozenie);
		break;
	case pZolw:
		organizm = new Zolw(*this, polozenie);
		break;
	case pAntylopa:
		return new Antylopa(*this, polozenie);
		break;
	case pSUMA:
	default:
		return nullptr;
	}

	/*if(los <= Prwdpdbnstwo[pMlecz])
		organizm = new Mlecz(*this, polozenie);
	else if(los <= Prwdpdbnstwo[pMlecz]  + Prwdpdbnstwo[pNiesporak])
		organizm = new Niesporaczek(*this, polozenie);

	if (los == 1)
		organizm = new Niesporaczek(*this, polozenie);
	else
		organizm = new Mlecz(*this, polozenie);*/

	return organizm;
}

void Swiat::SortujOrganizmy()
{
	std::stable_sort(kolejkaOrganizmow.begin(), kolejkaOrganizmow.end(), PorownanieInicjatywy());
}

void Swiat::PrzeniesNow(const PrzeniesDo & przeniesDo)
{
	int x1 = przeniesDo.origin.GetX(), y1 = przeniesDo.origin.GetY(),
		x2 = przeniesDo.target.GetX(), y2 = przeniesDo.target.GetY();
	if (organizmy[y1][x1] != nullptr && organizmy[y2][x2] != nullptr)
	{
		ERR << "NIELEGALNA OPERACJA! Proba przeniesienia organizmu(" << x1 << ',' << y1 << ',' << &organizmy[y1][x1]
			<< ") na zajete pole(" << x2 << ',' << y2 << ',' << &organizmy[y2][x2] << ')';
		return;
	}
	else if (organizmy[y1][x1] == nullptr && organizmy[y2][x2] == nullptr)
		return;
	std::swap(organizmy[y1][x1], organizmy[y2][x2]);
	if (organizmy[y1][x1] != nullptr)
		organizmy[y1][x1]->SetPozycja(x1, x2);
	if (organizmy[y2][x2] != nullptr)
		organizmy[y2][x2]->SetPozycja(x2, y2);
}

void Swiat::ZabijNow(const Point & zabij)
{
	Organizm * organizm = organizmy[zabij.GetY()][zabij.GetX()];
	if ( organizm == nullptr)
		return;
	/*for (int i = 0; i < kolejkaOrganizmow.size(); ++i)
	{
		if (kolejkaOrganizmow[i] == organizm)
		{
			kolejkaOrganizmow.erase(kolejkaOrganizmow.begin() + i);
			break;
		}
	}*/
	for (int i = 0; i < doPrzeniesienia.size(); ++i)
	{
		if (doPrzeniesienia[i].origin == zabij)
		{
			doPrzeniesienia.erase(doPrzeniesienia.begin() + i);
			--i;
		}
	}
	organizmy[zabij.GetY()][zabij.GetX()] = nullptr;
	//delete organizm;
}

void Swiat::WalidujOrganizmy()
{
	for (int i = 0; i < kolejkaOrganizmow.size(); ++i)
	{
		Organizm *domniamanePolozenie = GetOrganizm(kolejkaOrganizmow[i]);
		if(domniamanePolozenie != kolejkaOrganizmow[i])
		{
			delete kolejkaOrganizmow[i];
			kolejkaOrganizmow.erase(kolejkaOrganizmow.begin() + i);
			--i;
		}
	}
}

void Swiat::RysujOdswiezonePola()
{
	for (auto pole : polaDoOdswiezenia)
	{
		Organizm * org = this->GetOrganizm(pole);
		if (org == nullptr)
			Konsola::Wypisz(SYMBOL_PUSTEGO_POLA, pole.GetX(), pole.GetY(), KOLORKI_PUSTEGO_POLA);
		else
			org->Rysowanie();
	}
	polaDoOdswiezenia.clear();
}

int Swiat::GetObecnaTura()
{
	return tura;
}

Komentator & Swiat::GetKomentator()
{
	return this->komentator;
}

void Swiat::RozpocznijNowaGre(const int & width, const int & height, bool zaludniaj)
{
	system("cls");//lamerskie wiem, ale jest 2 w nocy ok?
	this->WyzerujWszystkieTablice();
	this->InicjujSwiat(width, height, DOMYSLNE_ZALUDNIENIE, zaludniaj);
}

bool Swiat::ZapiszSwiat(const std::string & sciezkaDoZapisu)
{
	std::ofstream file(KATALOG_ZAPISOW + sciezkaDoZapisu);
	if(!file.good())
		return false;
	file << NAGLOWEK << NEWLINEDLIMITER;
	file << width << ' ' << height << NEWLINEDLIMITER;
	for (auto organizm : kolejkaOrganizmow)
		file << organizm->SaveToString();
	file << KONIEC_PLIKU;
	file.close();
}

bool Swiat::ZaladujSwiat(const std::string & sciezkaDoPlikuZapisu)
{
	std::ifstream file(KATALOG_ZAPISOW + sciezkaDoPlikuZapisu);
	if(!file.good())
		return false;

	Organizm * organizm = nullptr;
	if (!this->SprawdzPoprawnoscNaglowka(file))
		return false;

	int width, heigth;
	file >> width >> height;

	this->RozpocznijNowaGre(width, height, false);

	char c;
	while (!file.eof())
	{
		c = file.peek();
		if (c == '\n')
		{
			file.get(c);
			continue;
		}
		//tu powinno byæ sprawdzanie czy sie trafilo na koniec pliku
		//ale nie chce mi sie tego implementowac
		else if (c == '#') 
		{
			file.close();
			break;
		}
		organizm =  this->ZaladujOrganizm(file);
		if (organizm != nullptr)
			this->DodajOrganizm(organizm->GetPozycja(), organizm);

	}

	this->zaiinicjujNoweOrganizmy();
	return true;
}

void Swiat::WyzerujWszystkieTablice()
{
	this->organizmy.clear();
	this->doPrzeniesienia.clear();
	this->kolejkaOrganizmow.clear();
}

void Swiat::InicjujSwiat(const int & width, const int & height, const double &procentZaludnienia,
	bool zaludniaj)
{
	this->width = width;
	this->height = height;
	this->tura = 1;
	this->komentator.Zaczep(Point(width + 1, 0));
	for (int y = 0; y < height; ++y)
	{
		organizmy.push_back(std::vector<Organizm*>());
		for (int x = 0; x < width; ++x)
			organizmy[y].push_back(nullptr);
	}
	if (zaludniaj)
		ZaludnijSwiat(procentZaludnienia);
}

bool Swiat::SprawdzPoprawnoscNaglowka(std::ifstream & file)
{
	std::string header = NAGLOWEK;
	char c;
	for (int i = 0; i < header.size(); ++i)
	{
		file.get(c);
		if (c != header[i])
			return false;
	}
	return true;
}

Organizm* Swiat::ZaladujOrganizm(std::ifstream & file)
{
	char symbol = ' ';
	int x = -1, y = -1, sila = -1, zdolnosc = 0, cooldown = 0;
	char c;
	std::vector<std::string> buf;
	while (true)
	{
		if (file.peek() == NEWLINEDLIMITER)
			break;
		buf.push_back(this->GetPolePlikuZapisu(file));
	}
	if (buf.size() < pzMINIMUMDLAORGANIZMU)
		return nullptr;
	else if (buf[0].size() > 1)
		return nullptr;
	symbol = buf[pzSymbol][0];
	x = std::stoi(buf[pzX]);
	y = std::stoi(buf[pzY]);
	sila = std::stoi(buf[pzSila]);
	if (buf.size() > pzMINIMUMCZLOWIEKA)
	{
		zdolnosc = std::stoi(buf[pzCzlowiekZdolnoscAktywna]);
		cooldown = std::stoi(buf[pzCzlowiekZdolnoscCooldown]);
	}

	switch (symbol)
	{
	case SYMBOL_CZLOWIEKA:
		return new Czlowiek(*this, Point(x, y), sila, zdolnosc, cooldown);
	case SYMBOL_ANTYLOPY:
		return new Antylopa(*this, Point(x, y), sila);
	case SYMBOL_LISA:
		return new Lis(*this, Point(x, y), sila);
	case SYMBOL_OWCY:
		return new Owca(*this, Point(x, y), sila);
	case SYMBOL_WILKA:
		return new Wilk(*this, Point(x, y), sila);
	case SYMBOL_ZOLWIA:
		return new Zolw(*this, Point(x, y), sila);
	case SYMBOL_BARSZCZU:
		return new BarszczSosnowskiego(*this, Point(x, y), sila);
	case SYMBOL_GUARANA:
		return new Guarana(*this, Point(x, y), sila);
	case SYMBOL_MLECZA:
		return new Mlecz(*this, Point(x, y), sila);
	case SYMBOL_TRWAY:
		return new Trawa(*this, Point(x, y), sila);
	case SYMBOL_WILCZEJ_JAGODY:
		return new WilczeJagody(*this, Point(x, y), sila);
	default:
		return nullptr;
	}
}

std::string Swiat::GetPolePlikuZapisu(std::ifstream & file)
{
	char c;
	std::string pole;
	while (true)
	{
		if (file.eof())
			return pole;

		c = file.peek();
		if (c == DELIMITER)
		{
			file.get(c);
			return pole;
		}
		else if (c == NEWLINEDLIMITER)
			return pole;
		else
		{
			file.get(c);
			pole += c;
		}
	}

	return pole;
}

Swiat::Swiat(const int & width, const int & height, const double &procentZaludnienia)
	:width(width), height(height), tura(1), komentator(Point(width+1, 0))
{
	if (width <= 0 || height <= 0)
		return;

	this->InicjujSwiat(width, height, procentZaludnienia);
	
}

Swiat::~Swiat()
{
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
			if (organizmy[y][x] != nullptr)
				delete organizmy[y][x];
}

bool Swiat::Good() const
{
	return organizmy.size() != 0;
}

bool Swiat::Przenies(Organizm * organizmDoPrzeniesienia, const Point & target)
{
	if (organizmDoPrzeniesienia == nullptr)
		return false;
	Point p = WrapPoint(target);
	// TODO zaimp
	//pole ju¿ okupowane przez inny organizm, nielegalny ruch
	/*if (GetOrganizm(p) != nullptr)
		return false;*/
	//przenies ogranizm
	doPrzeniesienia.emplace_back(organizmDoPrzeniesienia->GetPozycja(), p);
	PrzeniesNow(doPrzeniesienia.front());
	doPrzeniesienia.pop_back();
	return true;
}

bool Swiat::Zabij(Organizm * orgaznizmDoZabicia)
{
	if (orgaznizmDoZabicia == nullptr)
		return false;
	doZabicia.push(orgaznizmDoZabicia->GetPozycja());
	ZabijNow(doZabicia.front());
	doZabicia.pop();
	return true;
}

Organizm * Swiat::GetOrganizm(const Point & point)
{
	Point p = WrapPoint(point);

	return organizmy[p.GetY()][p.GetX()];
}

Organizm * Swiat::GetOrganizm(Organizm * organizm)
{
	return GetOrganizm(organizm->GetPozycja());
}

std::vector<Organizm*> Swiat::GetSasiednieOrganizmy(const Point & polozenie)
{
	/*if(organizm = nullptr)
		return std::vector<Organizm*>();*/
	std::vector<Point> sasiedniePola = Point::GetOffsetByAllUnitVectors(polozenie);
	std::vector<Organizm *> sasiednieOrganizmy;
	for (int i = 0; i < sasiedniePola.size(); ++i)
		sasiednieOrganizmy.push_back(this->GetOrganizm(sasiedniePola[i]));
	return sasiednieOrganizmy;
}

void Swiat::Rysuj()
{
	for(int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
		{
			if (organizmy[y][x] == nullptr)
				Konsola::Wypisz(SYMBOL_PUSTEGO_POLA, x, y, KOLORKI_PUSTEGO_POLA);
			else
				organizmy[y][x]->Rysowanie();
		}
}

void Swiat::Test()
{
	WykonajZadania();
}

void Swiat::WykonajTure()
{
	this->komentator.PowiadomONowejTurze(this->tura);
	for (auto organizm : kolejkaOrganizmow)
	{
		//Konsola::GetKolor(organizm->GetPozycja().GetX(), organizm->GetPozycja().GetY()); //test
#if !WYLACZ_ANIMACJE_RUCHU
#if IGNORUJ_ANIMACJE_ROSLIN
		if (dynamic_cast<Roslina*>(organizm))
		{
			organizm->Akcja();
			continue;
		}
#endif // IGNORUJ_ANIMACJE_ROSLIN
#if WYLAP_ZWIERZE 
		if (dynamic_cast<TYP_ZWIERZA>(organizm))
		{
			int x = 1;
		}
#endif // WYLAP_ZWIERZE

		int x = organizm->GetPozycja().GetX(), y = organizm->GetPozycja().GetY();
		DWORD kolor = Konsola::GetKolor(x, y);
		Konsola::SetKolor(x, y, KOLORKI_AKTYWNEGO_ORGANIZMU);
		std::this_thread::sleep_for(std::chrono::milliseconds(CZAS_TRWANIA_RUCHU/2));

		organizm->Akcja();
		x = organizm->GetPozycja().GetX(), y = organizm->GetPozycja().GetY();
		Rysuj();
		Konsola::SetKolor(x, y, KOLORKI_AKTYWNEGO_ORGANIZMU);
		std::this_thread::sleep_for(std::chrono::milliseconds(CZAS_TRWANIA_RUCHU/2));
		Konsola::SetKolor(x, y, kolor);
		//Rysuj();


#else
		organizm->Akcja();
#endif // WYLACZ_ANIMACJE_RUCHU


	}
	WalidujOrganizmy();
	this->zaiinicjujNoweOrganizmy();
	std::this_thread::sleep_for(std::chrono::milliseconds(CZAS_TRWANIA_RUCHU * 5));

	++tura;
}

void Swiat::OdswiezPole(const Point & pole)
{
	polaDoOdswiezenia.emplace_back(pole);
}

void Swiat::OdswiezPole(const std::vector<Point>& pola)
{
	for (auto pole : pola)
		this->OdswiezPole(pole);
}

bool Swiat::PorownanieInicjatywy::operator()(const Organizm * lewy, const Organizm * prawy) const
{
	return lewy->GetInicjatywa() > prawy->GetInicjatywa();
}
