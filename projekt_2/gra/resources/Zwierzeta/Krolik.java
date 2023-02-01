package gra.resources.Zwierzeta;

import gra.resources.backend.*;

public class Krolik extends Zwierze {
    private final static int KROLIK_SILA = 2;
    private final static int KROLIK_INIC = 7;
    private final static char KROLIK_CHAR = 'K';
    private final static int KROLIK_POLOG = 2;
    private final static int KROLIK_PELNOLETNOSC = 3;
    private final static String KROLIK_NAZWA = "Krolik";

    public Krolik(Swiat swiat, int x, int y) { super(swiat, x, y, KROLIK_SILA, KROLIK_INIC, KROLIK_PELNOLETNOSC); }

    public boolean Koliduj(Organizm somsiad, boolean czyAtakuje) {
        return false;
    }
    public void dodajPolog() { this.polog = KROLIK_POLOG; }
    public Organizm dajPotomka(Wsp n_wsp) {
        Organizm tmp = new Krolik(swiat, n_wsp.x, n_wsp.y);
        swiat.DodajOrganizm(tmp);
        return tmp;
    }
    public boolean czyTenSamGatunek(Organizm o) { if (o instanceof Krolik) { return true; } else return false; }
    public char getChar() { return KROLIK_CHAR; }
    public String getNazwa() { return KROLIK_NAZWA; }
}