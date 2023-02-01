#pragma once
#include <queue>
#include <vector>
#include "Organizm.h"
#include "Point.h"
#include "Komentator.h"

//forward declaration
class Organizm;

//domyœlne statystyki Swiata
#define DOMYSLNE_ZALUDNIENIE 0.20

class Swiat
{
private:
	int width, height;
	int tura;
	//struktura s³u¿¹ca do przechowywania informacji jaki organizm ma byæ
	//przeniesiony i dok¹d
	struct PrzeniesDo
	{
		Point origin, target;
		PrzeniesDo(const Point & origin, const Point & target)
			:origin(origin), target(target) {};
	};
	//struktura s³u¿¹ca do porz¹dkowania organizmów w kolejce priorytetowej
	struct PorownanieInicjatywy
	{
		bool operator()(const Organizm * lewy, const Organizm * prawy) const;
	};
	//tablica 2 wymiarowa swiata
	std::vector< std::vector< Organizm* > > organizmy;
	//kolejka organizmow do zabicia po zakonczeniu obecnego ruchu
	std::queue<Point> doZabicia;
	//kolejka organizmow do przesuniecia po zakonczeniu obecnego ruchu
	std::vector<PrzeniesDo> doPrzeniesienia;
	//kolejka organizmow 
	std::vector<Organizm*> kolejkaOrganizmow;
	//kolejka dodania do kolejki
	std::queue<Organizm*> nowoDodaneOrganizmy;
	//przenosi oczekuj¹ce organizmy do kolejkiOrganizmow
	void zaiinicjujNoweOrganizmy();

	//wykonuje przeniesienia i zabicia
	void WykonajZadania();
	//zapetla punkt na mapie
	Point WrapPoint(const Point & point);
	//zaludnia swiat
	void ZaludnijSwiat(const double &procentZaludnienia);

	//Generuje losowy organizm, nie umieszczajac go na swiecie
	Organizm * GenerujLosowyOrganizm(const Point &polozenie);
	//Sortuje kolejke organizmow po inicjatywie zachowuj¹c starszeñstwo
	void SortujOrganizmy();

	void PrzeniesNow(const PrzeniesDo & przeniesDo);
	void ZabijNow(const Point & zabij);

	//Iteruje po kolejkaOrganizmow i sprawdza czy wszystkie Organizmy znajduja siê na poprawnym polu
	//Je¿eli któryœ nie jest to jest usuwany z kolejki
	void WalidujOrganizmy();

	std::vector<Point> polaDoOdswiezenia;

	Komentator komentator;

	void WyzerujWszystkieTablice();
	void InicjujSwiat(const int & width, const int & height, const double &procentZaludnienia,
		bool zaludniaj = true);

	bool SprawdzPoprawnoscNaglowka(std::ifstream & file);
	Organizm* ZaladujOrganizm(std::ifstream & file);
	std::string GetPolePlikuZapisu(std::ifstream & file);

public:
	Swiat(const int &width, const int &height, const double &procentZaludnienia = DOMYSLNE_ZALUDNIENIE);
	~Swiat();

	bool Good() const;

	//oznacza organizm jako do przeniesienia po zakonczeniu obecnego ruchu
	bool Przenies(Organizm * organizmDoPrzeniesienia, const Point &target);
	//oznacza organizm jako do zabicia po zakonczeniu obecnego ruchu
	bool Zabij(Organizm * orgaznizmDoZabicia);
	//zwraca wskaznik organizmu stojacego na tym polu lub nullptr je¿eli pole jest puste
	Organizm * GetOrganizm(const Point & point);
	//zwraca pole na które wskazuje organizm
	Organizm * GetOrganizm(Organizm * organizm);

	std::vector<Organizm*> GetSasiednieOrganizmy(const Point & polozenie);

	//Dodaje organizm do swiata
	//je¿eli organizm jest nullptr to generuje losowy organizm wed³ug domyœlnego prawdopodobieñstwa
	//bool sortuj decyduje o tym czy kolejkaOrganizmów ma byæ sortowana wed³ug inicjatywy po dodaniu
	void DodajOrganizm(const Point &polozenie, Organizm* organizm = nullptr, bool sortuj = true);

	void Rysuj();

	void Test();

	void WykonajTure();

	void OdswiezPole(const Point &pole);
	void OdswiezPole(const std::vector<Point> &pola);
	void RysujOdswiezonePola();

	int GetObecnaTura();

	Komentator & GetKomentator();

	void RozpocznijNowaGre(const int &width, const int &height, bool zaludniaj = true);

	bool ZapiszSwiat(const std::string &sciezkaDoZapisu);

	bool ZaladujSwiat(const std::string &sciezkaDoPlikuZapisu);

	////publiczne bo u¿yjwaj¹ tego organizmy
	//Komentator komentator;

};

