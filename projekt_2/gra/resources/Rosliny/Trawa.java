package gra.resources.Rosliny;

import gra.resources.backend.*;

public class Trawa extends Roslina{
    private final static int TRAWA_SILA = 0;
    private final static char TRAWA_CHAR = '"';
    private final static String TRAWA_NAZWA = "Trawa";

    public Trawa(Swiat swiat, int x, int y) { super(swiat, x, y, TRAWA_SILA); }
    public boolean Koliduj(Organizm somsiad, boolean czyAtakuje) {
        return false;
    }

    public Organizm dajPotomka(Wsp n_wsp) {
        Organizm tmp = new Trawa(swiat, n_wsp.x, n_wsp.y);
        swiat.DodajOrganizm(tmp);
        return tmp;
    }
    public boolean czyTenSamGatunek(Organizm o) { if (o instanceof Trawa) { return true; } else return false; }

    public char getChar() { return TRAWA_CHAR; }
    public String getNazwa() { return TRAWA_NAZWA; }

}
