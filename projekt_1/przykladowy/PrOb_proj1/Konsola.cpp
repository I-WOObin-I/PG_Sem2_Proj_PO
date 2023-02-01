#include "Konsola.h"
#define GetHandle GetStdHandle(STD_OUTPUT_HANDLE)

HANDLE Konsola::uchwytKonsoli = GetHandle;
//DWORD Konsola::bytesWrtn = 0;

HANDLE & Konsola::GetUchwytKonsoli()
{
	return Konsola::uchwytKonsoli;
}

unsigned short Konsola::Kolorki2UShort(const Kolorki::Kolor & kolorTekstu, const Kolorki::Kolor & kolorTla)
{
	return ((unsigned)kolorTla << 4) | (unsigned)kolorTekstu;
}

unsigned short Konsola::GetKolor(const int & x, const int & y)
{
	COORD pos = { x,y };
	HANDLE uchwyt = GetHandle;
	WORD lpAttribute; //odczytane atrybuty
	DWORD numberOfAttrsRead; //liczba odczytanych atrybutów

	ReadConsoleOutputAttribute(uchwyt, &lpAttribute, 1, pos, &numberOfAttrsRead);
	return lpAttribute;
}

void Konsola::SetKolor(const int & x, const int & y, unsigned short kolorki)
{
	COORD poz = { x,y };
	DWORD bytesWritten;
	WriteConsoleOutputAttribute(uchwytKonsoli, &kolorki, 1, poz, &bytesWritten);
}

void Konsola::SetKolor(const int & x, const int & y, const Kolorki::Kolor & kolorTekstu, 
	const Kolorki::Kolor & kolorTla)
{
	SetKolor(x, y, Kolorki2UShort(kolorTekstu, kolorTla));
}

void Konsola::Wypisz(const std::string & string, const int & x, const int & y,
	const Kolorki::Kolor &kolorTekstu, const Kolorki::Kolor &kolorTla)
{

	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD len = string.size();
	DWORD bytesWritten = 0;

	//unsigned short wAttributes = ((unsigned)kolorTla << 4) | (unsigned)kolorTekstu;
	unsigned short * attrArray = new unsigned short[len];
	for (int i = 0; i < len; ++i)
		attrArray[i] = ((unsigned)kolorTla << 4) | (unsigned)kolorTekstu;

	WriteConsoleOutputAttribute(output, attrArray, len, pos, &bytesWritten);
	WriteConsoleOutputCharacter(output, string.c_str(), len, pos, &bytesWritten);
	
	delete[] attrArray;
}

void Konsola::Wypisz(const char & znak, const int & x, const int & y, 
	const Kolorki::Kolor & kolorTekstu, const Kolorki::Kolor & kolorTla)
{
	std::string s;
	s += znak;
	Wypisz(s, x, y, kolorTekstu, kolorTla);
}

Konsola::~Konsola()
{
}
