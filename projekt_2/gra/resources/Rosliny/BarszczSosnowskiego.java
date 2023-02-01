package gra.resources.Rosliny;
import gra.resources.Zwierzeta.CyberOwca;
import gra.resources.backend.*;

public class BarszczSosnowskiego extends Roslina {
    private final static int BARSZCZ_SILA = 10;
    private final static char BARSZCZ_CHAR = '$';
    private final static String BARSZCZ_NAZWA = "BarszczSosnowskiego";

    public BarszczSosnowskiego(Swiat swiat, int x, int y) { super(swiat, x, y, BARSZCZ_SILA); }

    public void Akcja() {
        Wsp tmp = new Wsp(this.wsp);		// zabicie wszystkich sasiadujacych zwierzat //
        for (int i = 0; i < swiat.getLiczbeSasiadow() + 1; i++) {
            tmp = swiat.rotacjaSasiadow(this.wsp, tmp);
            Organizm tmp2 = swiat.getOrg(tmp);
            if (tmp2 != null && tmp2.getTyp() == TYP_ZWIERZE && tmp2 instanceof CyberOwca == false) { swiat.usunOrganizm(tmp2); }
        }
        this.domyslnaAkcja();
    }
    public boolean Koliduj(Organizm somsiad, boolean czyAtakuje) {
        if (somsiad.getTyp() == TYP_ZWIERZE && somsiad instanceof CyberOwca == false) {
            if (czyAtakuje == true) {
                swiat.usunOrganizm(somsiad);
                Wsp n_wsp = somsiad.getWsp();
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
        Organizm tmp = new BarszczSosnowskiego(swiat, n_wsp.x, n_wsp.y);
        swiat.DodajOrganizm(tmp);
        return tmp;
    }
    public boolean czyTenSamGatunek(Organizm o) { if (o instanceof BarszczSosnowskiego) { return true; } else return false; }
    public char getChar() { return BARSZCZ_CHAR; }
    public String getNazwa() { return BARSZCZ_NAZWA; }
}
