package gra.resources.Rosliny;
import gra.resources.backend.*;

public class Mlecz extends Roslina {
    private final static int MLECZ_SILA = 0;
    private final static char MLECZ_CHAR = '*';
    private final static String MLECZ_NAZWA = "Mlecz";
    private final static int PROBYROZSIEWU = 3;

    public Mlecz(Swiat swiat, int x, int y) { super(swiat, x, y, MLECZ_SILA); }

    public void Akcja() {
        for(int i=0; i<PROBYROZSIEWU; i++) {
            this.domyslnaAkcja();
        }
    }
    public boolean Koliduj(Organizm somsiad, boolean czyAtakuje) {
        return false;
    }

    public Organizm dajPotomka(Wsp n_wsp) {
        Organizm tmp = new Mlecz(swiat, n_wsp.x, n_wsp.y);
        swiat.DodajOrganizm(tmp);
        return tmp;
    }
    public boolean czyTenSamGatunek(Organizm o) { if (o instanceof Mlecz) { return true; } else return false; }

    public char getChar() { return MLECZ_CHAR; }
    public String getNazwa() { return MLECZ_NAZWA; }

}
