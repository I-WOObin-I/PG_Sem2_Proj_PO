#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>

#include "KontrolerOrganizmow.h"

#define PLANE_WIDTH 30
#define PLANE_HEIGHT 30

using namespace std;

int main() {
	//cout << "podaj wymiary: ";
	//int n, m;
	//cin >> n >> m;
	Swiat* swiat = new Swiat(PLANE_WIDTH, PLANE_HEIGHT);
	KontrolerOrganizmow* KontrOrg = new KontrolerOrganizmow(swiat);
	swiat->DodajOrganizm(new Wilk(swiat, 2, 3));
	swiat->DodajOrganizm(new Wilk(swiat, 1, 3));
	swiat->DodajOrganizm(new Owca(swiat, 4, 6));
	swiat->DodajOrganizm(new Antylopa(swiat, 15, 10));
	swiat->DodajOrganizm(new Guarana(swiat, 2, 25));
	swiat->DodajOrganizm(new Lis(swiat, 3, 5));
	swiat->DodajOrganizm(new Mlecz(swiat, 25, 2));
	swiat->DodajOrganizm(new Trawa(swiat, 12, 27));
	swiat->DodajOrganizm(new WilczaJagoda(swiat, 9, 10));
	swiat->DodajOrganizm(new Zolw(swiat, 15, 15));
	swiat->DodajOrganizm(new BarszczSosnowskiego(swiat, 15, 29));
	swiat->DodajOrganizm(new Guarana(swiat, 25, 25));
	swiat->DodajOrganizm(new Czlowiek(swiat, 28, 28));
	char in;
	for (;;) {
		swiat->przejdzTure();
		Sleep(100);
		in = _getch();
		if (in == 's') { swiat->Zapisz(); }
		else if (in == 'l') { KontrOrg->Zaladuj(); }
		fflush(stdin);
	}

	return 0;
}