package gra.resources.Rosliny;

import gra.resources.backend.*;

public class WilczaJagoda extends Roslina{
    private final static int WJAG_SILA = 0;
    private final static char WJAG_CHAR = '%';
    private final static String WJAG_NAZWA = "WilczaJagoda";

    public WilczaJagoda(Swiat swiat, int x, int y) { super(swiat, x, y, WJAG_SILA); }

    public boolean Koliduj(Organizm somsiad, boolean czyAtakuje) {
        if (somsiad.getTyp() == TYP_ZWIERZE) {
            if (czyAtakuje == true) {
                swiat.usunOrganizm(somsiad);
                Wsp n_wsp = new Wsp(somsiad.getWsp());
                this.dajPotomka(n_wsp);
                swiat.DodajLogWalki(new LogWalki(somsiad.getX(), somsiad.getY(), this.getNazwa(), somsiad.getNazwa(), "zabil"));
            }
            else {
                swiat.usunOrganizm(somsiad);
                swiat.DodajLogWalki(new LogWalki(somsiad.getX(), somsiad.getY(), this.getNazwa(), somsiad.getNazwa(), "zabil"));
            }
            return true;
        }
        return false;
    }
    public Organizm dajPotomka(Wsp n_wsp) {
        Organizm tmp = new WilczaJagoda(swiat, n_wsp.x, n_wsp.y);
        swiat.DodajOrganizm(tmp);
        return tmp;
    }
    public boolean czyTenSamGatunek(Organizm o) { if (o instanceof WilczaJagoda) { return true; } else return false; }
    public char getChar() { return WJAG_CHAR; }
    public String getNazwa() { return WJAG_NAZWA; }
    
}
