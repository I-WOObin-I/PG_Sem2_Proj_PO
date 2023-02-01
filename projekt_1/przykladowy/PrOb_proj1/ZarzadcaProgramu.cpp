#include "ZarzadcaProgramu.h"
#include <conio.h>
#include "Konsola.h"


void ZarzadcaProgramu::WypiszObecnaTure()
{
	TCHAR msStr[255];
	std::string str = "Obecna tura: " + std::to_string(swiat.GetObecnaTura());
	int i;
	for (i = 0; i <= str.size(); ++i)
	{
		msStr[i] = str[i];
	}
	msStr[i] = '\0';
	SetConsoleTitle(msStr);
	return;
}

void ZarzadcaProgramu::WypiszTytulOkna()
{
	TCHAR nazwaOkna[] = "WOJCIECH DYMEL s172099 - Projekt PO_1";
	SetConsoleTitle(nazwaOkna);
}

std::string ZarzadcaProgramu::WyluskajArgument(const std::string & polecenie, const int & numerArgumentu)
{
	int polozenie = this->ZnajdzPolozenieArgumenut(polecenie, numerArgumentu);
	if(polozenie == -1)
		return std::string();
	std::string arg;
	while (polozenie < polecenie.size() && polecenie[polozenie] != ' ')
		arg += polecenie[polozenie++];

	return arg;
}

int ZarzadcaProgramu::ZnajdzPolozenieArgumenut(const std::string & polecenie, const int & numerArgumentu)
{
	int obecnyArgument = -1;
	int polozenieKursora = 0;
	while (polozenieKursora < polecenie.size())
	{
		if (obecnyArgument == numerArgumentu)
		{
			polecenie[polozenieKursora] != ' ';
			return polozenieKursora;
		}

		if (polecenie[polozenieKursora] == ' ')
			obecnyArgument++;

		polozenieKursora++;
	}
	return -1;
}

ZarzadcaProgramu::ZarzadcaProgramu(Swiat & swiat)
	:swiat(swiat)
{
	wyjdz = false;
}

ZarzadcaProgramu::~ZarzadcaProgramu()
{
}

bool ZarzadcaProgramu::Wyjdz()
{
	return wyjdz;
}

bool ZarzadcaProgramu::PrzyjmijPolecenie()
{
	//this->WypiszObecnaTure();
	this->WypiszTytulOkna();
	char c = _getch();
	if (c != SYMBOL_POLECENIA)
		return true;

	TCHAR polecenie[255] = "";
	int rozmiar = 0;

	//std::string polecenie;
	polecenie[rozmiar] = c;
	rozmiar++;
	while (true)
	{
		
		SetConsoleTitle(polecenie);

		c = _getch();
		if (c == '\r')
			break;
		else if (c == KLAWISZ_USUWANIA)
		{
			if (rozmiar > 0)
			{
				polecenie[rozmiar - 1] = '\0';
				rozmiar--;
			}
			continue;
		}
		polecenie[rozmiar] = c;
		rozmiar++;

	}
	this->WypiszTytulOkna();

	if (rozmiar < 2)
		return false;

	std::string arg1;
	std::string arg2;
	switch (polecenie[1])
	{
	case WYJDZ:
		this->wyjdz = true;
		return false;
	case LOAD:
		arg1 = this->WyluskajArgument(polecenie, 0);
		if (arg1.size() > 0)
		{
			this->swiat.ZaladujSwiat(arg1);
			return false;
		}
		return true;
	case SAVE:
		arg1 = this->WyluskajArgument(polecenie, 0);
		if (arg1.size() > 0)
		{
			this->swiat.ZapiszSwiat(arg1);
			return false;
		}
		return true;
	case NOWA_GRA:
		arg1 = this->WyluskajArgument(polecenie, 0);
		arg2 = this->WyluskajArgument(polecenie, 1);
		if (arg1 == "" || arg2 == "")
			return true;
		int width = std::stoi(arg1);
		int heigth = std::stoi(arg2);
		this->swiat.RozpocznijNowaGre(width, heigth);
		return false;
	}
	return false;
}
