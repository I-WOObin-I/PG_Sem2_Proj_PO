#include <cstdlib>
#include <ctime>
#include "Konsola.h"
#include "Point.h"
#include "Niesporaczek.h"
#include "LogError3.h"
#include "ZarzadcaProgramu.h"

#include <conio.h>

#define rozmiar 20
int main()
{
	TCHAR nazwaOkna[] = "WOJCIECH DYMEL s172099 - Projekt PO_1";
	SetConsoleTitle(nazwaOkna);

	LogError3::EmptyLog();
	ERR << "START PROGRAMU";
	std::srand(std::time(nullptr));
	Swiat swiat(rozmiar, rozmiar);
	ZarzadcaProgramu zarz(swiat);
	std::string polecenie;
	while (!zarz.Wyjdz())
	{
		swiat.Rysuj();
		if (!zarz.PrzyjmijPolecenie())
			continue;
		swiat.WykonajTure();

	}


	
	ERR << "KONIEC PROGRAMU";
	return 0;
}