package gra.resources.Zwierzeta;

import gra.resources.backend.*;

public class Owca extends Zwierze {
    private final static int OWCA_SILA = 4;
    private final static int OWCA_INIC = 4;
    private final static char OWCA_CHAR = 'O';
    private final static int OWCA_POLOG = 5;
    private final static int OWCA_PELNOLETNOSC = 10;
    private final static String OWCA_NAZWA = "Owca";

    public Owca(Swiat swiat, int x, int y) { super(swiat, x, y, OWCA_SILA, OWCA_INIC, OWCA_PELNOLETNOSC); }

    public boolean Koliduj(Organizm somsiad, boolean czyAtakuje) {
        return false;
    }
    public void dodajPolog() { this.polog = OWCA_POLOG; }
    public Organizm dajPotomka(Wsp n_wsp) {
        Organizm tmp = new Owca(swiat, n_wsp.x, n_wsp.y);
        swiat.DodajOrganizm(tmp);
        return tmp;
    }
    public boolean czyTenSamGatunek(Organizm o) { if (o instanceof Owca) { return true; } else { return false; } }
    public char getChar() { return OWCA_CHAR; }
    public String getNazwa() { return OWCA_NAZWA; }
}
