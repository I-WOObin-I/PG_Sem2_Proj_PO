package gra.resources.Zwierzeta;

import gra.resources.Rosliny.BarszczSosnowskiego;
import gra.resources.backend.*;

public class CyberOwca extends Zwierze {
    private final static int CYBEROWCA_SILA = 11;
    private final static int CYBEROWCA_INIC = 4;
    private final static char CYBEROWCA_CHAR = 'C';
    private final static int CYBEROWCA_POLOG = 5;
    private final static int CYBEROWCA_PELNOLETNOSC = 10;
    private final static String CYBEROWCA_NAZWA = "CyberOwca";

    public CyberOwca(Swiat swiat, int x, int y) { super(swiat, x, y, CYBEROWCA_SILA, CYBEROWCA_INIC, CYBEROWCA_PELNOLETNOSC); }
    public void Akcja() {
        Organizm tmp = new BarszczSosnowskiego(swiat, 0, 0);
        Wsp t_wsp = new Wsp(swiat.znajdzNajblizszyGatunek(this.wsp, tmp));
        if(t_wsp.x == this.wsp.x && t_wsp.y == this.wsp.y) { this.domyslaAkcja(); return; }
        Wsp n_wsp = new Wsp(this.wsp);
        if      (t_wsp.x > this.wsp.x)   { n_wsp.x++; }
        else if (t_wsp.x < this.wsp.x)   { n_wsp.x--; }
        if      (t_wsp.y > this.wsp.y)   { n_wsp.y++; }
        else if (t_wsp.y < this.wsp.y)   { n_wsp.y--; }
        this.inicjujKolizje(n_wsp);
    }
    public boolean Koliduj(Organizm somsiad, boolean czyAtakuje) {
        if(somsiad instanceof BarszczSosnowskiego) {
            if(czyAtakuje == true) { kolidujDomyslnie(somsiad);         }
            else                   { somsiad.kolidujDomyslnie(this);    }
            return true;
        }
        return false;
    }
    public void dodajPolog() { this.polog = CYBEROWCA_POLOG; }
    public Organizm dajPotomka(Wsp n_wsp) {
        Organizm tmp = new CyberOwca(swiat, n_wsp.x, n_wsp.y);
        swiat.DodajOrganizm(tmp);
        return tmp;
    }
    public boolean czyTenSamGatunek(Organizm o) { if (o instanceof CyberOwca) { return true; } else { return false; } }
    public char getChar() { return CYBEROWCA_CHAR; }
    public String getNazwa() { return CYBEROWCA_NAZWA; }
}
