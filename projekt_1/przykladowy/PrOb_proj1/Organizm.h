#pragma once
#include "Swiat.h"
#include "Konsola.h"
#include "Point.h"

//forward declaration
class Swiat;

//#define SYMBOL_ORGANIZMU '~'
//#define KOLORKI_ORGANIZMU Kolorki::white, Kolorki::black
#define DELIMITER ';'
#define NEWLINEDLIMITER '\n'


class Organizm
{
	char symbolOrganizmu;
	Kolorki::Kolor kolorSymbolu, kolorTla;

	Point polozenie;
	int inicjatywa;
	bool zywy;

protected:
	int sila;
	Swiat & swiat;
public:
	Organizm(Swiat & swiat, const Point & polozenie, const char &symbol, const int &sila,
		const int &inicjatywa, const Kolorki::Kolor &kolorFrontu, const Kolorki::Kolor &kolorTla);
	virtual void Akcja() = 0;
	//zwaraca true je¿eli this zwalnia pole na którym sta³o czy poprzez œmieræ czy unik
	//zwrara false je¿eli this dalej okupuje obecne pole czy przez obronê czy odbiciê ataku
	virtual bool Kolizja(Organizm * organizmAtakujacy) = 0;
	/*virtual void Umrzyj();
	virtual void PrzeniesSie(const Point & gdzie);*/
	void Rysowanie();

	Point GetPozycja() const;
	void SetPozycja(const int &x, const int &y);
	void SetPozycja(const Point &nowePolozenie);
	int GetInicjatywa() const;
	int GetSila() const;
	void OffsetSile(const int &przesuniecie);
	virtual ~Organizm();

	//zwraca czy organizm jest ¿ywy
	bool Zywy();
	//zwraca true je¿eli organizm umar³ po ataku lub zwolni³ pole
	//zwraca false je¿eli organizm dalej ¿yje i pozosta³ na swoim polu z jakiegoœ powodu
	//typu godmode
	virtual bool Umrzyj(Organizm * zabijajacy);
	//zwraca true je¿eli organizm odbi³ atak
	//false je¿eli nie
	virtual bool CzyOdbilAtak(Organizm *atakujacy);
	//powinno zwracaæ true je¿eli spotka³y siê 2 organizmy tego samego gatunku
	//virtual bool CzyTenSamGatunek(Organizm *odpytujacy) = 0;

	//Zwraca organizm swojego typu np wilka czy mlecza
	virtual Organizm * wygenerujKopie(const Point & polozenie) = 0;

	virtual std::string GetNazwa() const;

	virtual std::string ToString() const;


	void SetInicjatywa(const int &inicjatywa)
	{
		this->inicjatywa = inicjatywa;
	}

	virtual std::string SaveToString() const;

	//zwraca symbol przez jaki reprezentowany jest organizm
	char GetSymbol() const;
};

