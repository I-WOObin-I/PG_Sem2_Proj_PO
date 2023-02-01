package gra.resources.Zwierzeta;

import gra.resources.backend.*;

public class Lis extends Zwierze {
    private final static int LIS_SILA = 3;
    private final static int LIS_INIC = 7;
    private final static char LIS_CHAR = 'L';
    private final static int LIS_POLOG = 5;
    private final static int LIS_PELNOLETNOSC = 10;
    private final static String LIS_NAZWA = "Lis";

    public Lis(Swiat swiat, int x, int y) { super(swiat, x, y, LIS_SILA, LIS_INIC, LIS_PELNOLETNOSC); }

    public void Akcja() {

        Wsp n_wsp = new Wsp(swiat.losujSasiada(this.wsp));
        for (int i = 0; i < swiat.getLiczbeSasiadow(); i++) {
            if (swiat.getOrg(n_wsp) == null || swiat.getOrg(n_wsp).getS() <= this.sila) { break; }
            n_wsp = swiat.rotacjaSasiadow(this.wsp, n_wsp);
        }
    
        this.inicjujKolizje(n_wsp);
    }
    public boolean Koliduj(Organizm somsiad, boolean czyAtakuje) {
        return false;
    }
    public void dodajPolog() { this.polog = LIS_POLOG; }
    public Organizm dajPotomka(Wsp n_wsp) {
        Organizm tmp = new Lis(swiat, n_wsp.x, n_wsp.y);
        swiat.DodajOrganizm(tmp);
        return tmp;
    }
    public boolean czyTenSamGatunek(Organizm o) { if (o instanceof Lis) { return true; } else return false; }
    public char getChar() { return LIS_CHAR; }
    public String getNazwa() { return LIS_NAZWA; }
}
