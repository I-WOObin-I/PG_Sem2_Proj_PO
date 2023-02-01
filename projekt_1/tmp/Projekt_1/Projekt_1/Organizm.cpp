#pragma once
#include "Organizm.h"

using namespace std;

Organizm::Organizm(Swiat* swiat, int x, int y, int sila, int inicjatywa, int typ, int polog) : 
	swiat(swiat),
	wsp(x,y),
	sila(sila),
	inicjatywa(inicjatywa),
	typ(typ),
	polog(polog)
{}

void Organizm::Zabij() { this->zywy = false; }
void Organizm::Przesun(Wsp n_wsp) { this->wsp = n_wsp; }
void Organizm::dodajBuff(int b) { this->buff += b; }

void Organizm::dodajPolog() { return; }
bool Organizm::czyGotowyDoRozmnazania() { return true; }

int Organizm::getX() { return wsp.x; }
int Organizm::getY() { return wsp.y; }
int Organizm::getS() { return sila + buff; }
int Organizm::getI() { return inicjatywa; }
int Organizm::getTyp() { return typ; }
int Organizm::getPolog() { return polog; }
int Organizm::getBuff() { return buff; }
bool Organizm::getZ() { return zywy; }
Wsp Organizm::getWsp() { return wsp; }

Organizm::~Organizm() {}
