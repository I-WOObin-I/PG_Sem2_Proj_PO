#pragma once
#include "Zwierze.h"

#define SILA_CZLOWIEKA			5
#define INICJATYWA_CZLOWIEKA	4
#define SYMBOL_CZLOWIEKA		'@'
#define KOLORKI_CZLOWIEKA		Kolorki::white, Kolorki::red

//U�YWA� MA�YCH LITER
#define CZLEK_KIER_NORTH		'w'
#define CZLEK_KIER_EAST			'd'
#define CZLEK_KIER_SOUTH		's'
#define CZLEK_KIER_WEST			'a'
#define CZLEK_ZDOLNOSC			'f'
#define CZLEK_PASS				' '		//gracz si� nie rusza, czeka

#define CZAS_TRWANIA_ZDOLNOSCI_SPECJALNEJ	5
#define COOLDOWN_ZDOLNOSCI_SPECJALNEJ		5


class Czlowiek :
	public Zwierze
{
private:
	int pozostalyCzasZdolnosci,
		cooldownZdolnosci;
	//aktywuje zdolno�� dost�pn� je�eli jest to mo�liwe (brak cooldown)
	//zwraca false je�eli nie uda�o si� aktywowa� zdolno�ci
	bool AktywyujZdolnoscSpecjalna();
	//wykonuje efekty zdolno�ci specjalnej
	void ZdolnoscSpecjalna();

	void TuraZdolnosci();
public:
	Czlowiek(Swiat & swiat, const Point & polozenie);
	Czlowiek(Swiat & swiat, const Point & polozenie, const int &sila,
		const int &zdolnosc, const int &cooldown);

	Organizm * wygenerujKopie(const Point & polozenie) override;
	bool CzyTenSamGatunek(Organizm *organizm) override;

	Point GetPoleDocelowe() override;

	void Akcja() override;

	std::string GetNazwa() const override;

	std::string SaveToString() const override;

	~Czlowiek();
};

