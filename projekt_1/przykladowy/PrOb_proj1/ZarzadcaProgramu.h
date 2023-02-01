#pragma once
#include "Swiat.h"

#define SYMBOL_POLECENIA ':'
#define POLOZENIE_KONSOLI Point(0,0)
#define KLAWISZ_USUWANIA '\b'
#define KLAWISZ_AKCPETACJI '\r'

#define WYJDZ		'q'
#define LOAD		'o'
#define SAVE		'w'
#define NOWA_GRA	'n'

class ZarzadcaProgramu
{
private:
	Swiat & swiat;
	bool wyjdz;
	void WypiszObecnaTure();
	void WypiszTytulOkna();
	std::string WyluskajArgument(const std::string &polecenie, const int &numerArgumentu = 0);
	//zwraca polzenie argumentu
	//zwraca -1 gdy brak argumentu o tym numerze
	int ZnajdzPolozenieArgumenut(const std::string &polecenie, const int &numerArgumentu = 0);
public:
	ZarzadcaProgramu(Swiat & swiat);
	~ZarzadcaProgramu();

	bool Wyjdz();

	bool PrzyjmijPolecenie();

};

