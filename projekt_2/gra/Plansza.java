package gra;

import java.awt.*;
import gra.resources.backend.*;

public abstract class Plansza {
    public abstract void WstawOrganizm(Organizm o, Wsp wsp);
    public abstract void UsunOrganizm(Wsp wsp);

    public abstract void RysujPlansze();
    public abstract void WyczyscPlansze();
    public abstract void resetPanel();

    public abstract boolean czyWPlanszy(Wsp wsp);
    public abstract Wsp losujSasiada(Wsp wsp);
    public abstract Wsp znajdzWolnePole(Wsp wsp);

    public abstract int getSzerokosc();
    public abstract int getWysokosc();
    public abstract Organizm getOrg(Wsp wsp);
    public abstract int getLiczbeSasiadow();
    public abstract Component getJPanel();

    public abstract Wsp rotacjaSasiadow(Wsp wsp, Wsp n_wsp);
    public abstract Wsp znajdzNajblizszyGatunek(Wsp wsp, Organizm o);

}
