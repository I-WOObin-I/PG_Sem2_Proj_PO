package gra.resources.Zwierzeta;

import gra.resources.backend.*;

public class Wilk extends Zwierze{
    private final static int WILK_SILA = 9;
    private final static int WILK_INIC = 5;
    private final static char WILK_CHAR = 'W';
    private final static int WILK_POLOG = 5;
    private final static int WILK_PELNOLETNOSC = 10;
    private final static String WILK_NAZWA = "Wilk";

    public Wilk(Swiat swiat, int x, int y) { super(swiat, x, y, WILK_SILA, WILK_INIC, WILK_PELNOLETNOSC); }

    public boolean Koliduj(Organizm somsiad, boolean czyAtakuje) {
        return false;
    }
    public void dodajPolog() { this.polog = WILK_POLOG; }
    public Organizm dajPotomka(Wsp n_wsp) {
        Organizm tmp = new Wilk(swiat, n_wsp.x, n_wsp.y);
        swiat.DodajOrganizm(tmp);
        return tmp;
    }
    public boolean czyTenSamGatunek(Organizm o) { if (o instanceof Wilk) { return true; } else { return false; } }
    public char getChar() { return WILK_CHAR; }
    public String getNazwa() { return WILK_NAZWA; }

}
