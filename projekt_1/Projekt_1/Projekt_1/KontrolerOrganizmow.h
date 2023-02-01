#pragma once
#include <fstream>

#include "Swiat.h"
#include "Wsp.h"

#include "Czlowiek.h"
#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"
#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "WilczaJagoda.h"
#include "BarszczSosnowskiego.h"

class KontrolerOrganizmow {
private:
	list<Organizm*> gatunki;
	Swiat* swiat;
public:
	KontrolerOrganizmow(Swiat* swiat);
	void Zaladuj();

	~KontrolerOrganizmow();
};