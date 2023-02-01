#pragma once
//TESTOWE
//#define TEST_ILOSC_ORGANIZMOW 40
#define WYLACZ_ANIMACJE_RUCHU true
#define IGNORUJ_ANIMACJE_ROSLIN true
#define WYLAP_ZWIERZE true
#define TYP_ZWIERZA Antylopa*
//STALE
#define SYMBOL_PUSTEGO_POLA '.'
#define KOLORKI_PUSTEGO_POLA Kolorki::white, Kolorki::black
#define KOLORKI_AKTYWNEGO_ORGANIZMU Kolorki::black, Kolorki::white
#define CZAS_TRWANIA_RUCHU 1		//w milisekundach
#define POLOZENIE_KOMENTATORA 22,0
//ZAPISYWANIE I WCZYTANIE
#define KATALOG_ZAPISOW "saves/"
#define NAGLOWEK "#!/dymel/prob1/savefile"
#define KONIEC_PLIKU "#!/dymel/prob1/savefile/end"
enum POLA_ZAPISU
{
	pzSymbol = 0,
	pzX,
	pzY,
	pzSila,
	pzMINIMUMDLAORGANIZMU,
	pzCzlowiekZdolnoscAktywna = pzMINIMUMDLAORGANIZMU,
	pzCzlowiekZdolnoscCooldown,
	pzMINIMUMCZLOWIEKA
};