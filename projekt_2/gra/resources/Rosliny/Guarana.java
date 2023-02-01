package gra.resources.Rosliny;

import gra.resources.backend.*;

public class Guarana extends Roslina{
    private final static int GUARANA_SILA = 0;
    private final static char GUARANA_CHAR = '@';
    private final static String GUARANA_NAZWA = "Guarana";
    private final static int BUFF = 3;

    public Guarana(Swiat swiat, int x, int y) { super(swiat, x, y, GUARANA_SILA); }

    public boolean Koliduj(Organizm somsiad, boolean czyAtakuje) {
        if (somsiad.getTyp() == TYP_ZWIERZE) {
            somsiad.dodajBuff(BUFF);
            if (czyAtakuje == false) {
                swiat.usunOrganizm(this);
                swiat.usunZPlanszy(somsiad.getWsp());
                somsiad.Przesun(this.wsp);
                swiat.wstawDoPlanszy(somsiad, somsiad.getWsp());
            }
            swiat.DodajLogWalki(new LogWalki(somsiad.getX(), somsiad.getY(), somsiad.getNazwa(), this.getNazwa(), "zjadl"));
            return true;
        }
        return false;
    }

    public Organizm dajPotomka(Wsp n_wsp) {
        Organizm tmp = new Guarana(swiat, n_wsp.x, n_wsp.y);
        swiat.DodajOrganizm(tmp);
        return tmp;
    }
    public boolean czyTenSamGatunek(Organizm o) { if (o instanceof Guarana) { return true; } else return false; }

    public char getChar() { return GUARANA_CHAR; }
    public String getNazwa() { return GUARANA_NAZWA; }
}
