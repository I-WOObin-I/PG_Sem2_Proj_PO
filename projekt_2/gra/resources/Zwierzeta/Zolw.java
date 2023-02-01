package gra.resources.Zwierzeta;
import java.util.Random;
import gra.resources.backend.*;

public class Zolw extends Zwierze{
    private final static int ZOLW_SILA = 2;
    private final static int ZOLW_INIC = 1;
    private final static char ZOLW_CHAR = 'Z';
    private final static int ZOLW_POLOG = 5;
    private final static int ZOLW_PELNOLETNOSC = 10;
    private final static String ZOLW_NAZWA = "Zolw";
    private final static int SZANSA_NA_RUCH = 25;
    private final static int SILA_ODBICIA = 5;

    public Zolw(Swiat swiat, int x, int y) { super(swiat, x, y, ZOLW_SILA, ZOLW_INIC, ZOLW_PELNOLETNOSC); }

    public void Akcja() {
        Random rand = new Random();
        int tmp = rand.nextInt(100);
        if (tmp < SZANSA_NA_RUCH) {
            this.domyslaAkcja();
        }
    }
    public boolean Koliduj(Organizm somsiad, boolean czyAtakuje) {
        if (czyAtakuje == false && this.getS() < somsiad.getS() && somsiad.getS() < SILA_ODBICIA) { return true; }
        else { return false; }
    }
    public void dodajPolog() { polog = ZOLW_POLOG; }
    public Organizm dajPotomka(Wsp n_wsp) {
        Organizm tmp = new Zolw(swiat, n_wsp.x, n_wsp.y);
        swiat.DodajOrganizm(tmp);
        return tmp;
    }
    public boolean czyTenSamGatunek(Organizm o) { if (o instanceof Zolw) { return true; } else return false; }
    public char getChar() { return ZOLW_CHAR; }
    public String getNazwa() { return ZOLW_NAZWA; }
}
