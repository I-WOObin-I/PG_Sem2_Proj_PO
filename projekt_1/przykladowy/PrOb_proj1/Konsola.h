#pragma once
#include <string>
#include <Windows.h>
#include "Kolorki.h"

class Konsola
{
	//statyczne pola które zawsze s¹ u¿ywane
	static HANDLE uchwytKonsoli;
	//static DWORD bytesWrtn;
public:

	HANDLE & GetUchwytKonsoli();

	//konwersja enum na 8 bitowy zapis kodu
	static unsigned short Kolorki2UShort(const Kolorki::Kolor &kolorTekstu, const Kolorki::Kolor &kolorTla);

	//pobranie koloru
	static unsigned short GetKolor(const int &x, const int &y);

	//zmiana koloru pojedyñczego bitu
	static void SetKolor(const int &x, const int &y, unsigned short kolorki);
	static void SetKolor(const int &x, const int &y, const Kolorki::Kolor & kolorTekstu,
		const Kolorki::Kolor &kolorTla);

	//wypisywnaie
	static void Wypisz(const std::string &string, const int &x, const int &y,
		const Kolorki::Kolor &kolorTekstu = Kolorki::white, 
		const Kolorki::Kolor &kolorTla = Kolorki::black);
	static void Wypisz(const char &znak, const int &x, const int &y,
		const Kolorki::Kolor &kolorTekstu = Kolorki::white,
		const Kolorki::Kolor &kolorTla = Kolorki::black);

	virtual ~Konsola() = 0;
};

