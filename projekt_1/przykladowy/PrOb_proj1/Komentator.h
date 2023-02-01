#pragma once
#include <string>
#include "Point.h"
#include "Kolorki.h"
//#include "Organizm.h"

class Organizm;

#define MAX_WYSOKOSC 20
#define MAX_DLUGOSC_KOMUNIKATU
#define KOLORKI_KOMENTATORA Kolorki::black, Kolorki::white
#define KOLORKI_GUMKI_KOMENTATORA Kolorki::black, Kolorki::black

class Komentator
{
private:
	Point punktZaczepienia;
	unsigned int obecnyWiersz;
	void WymazWiersz(const int &wiersz);
	void WypiszWiersz(const std::string &komunikat);
public:
	Komentator(const Point &punktZaczepienia);
	
	void Zaczep(const Point &punktZaczepienia);

	void PowiadomONowejTurze(const int &licznikTury);
	void PowiadomOSmierciOrganizmu(Organizm * umierajacy, Organizm * zabijajacy);
	void PowiadomOUniku(Organizm * uniknal, Organizm * tenCoAtakowal);



	~Komentator();
};

