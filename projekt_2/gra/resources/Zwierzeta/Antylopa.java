package gra.resources.Zwierzeta;
import java.util.Random;
import gra.resources.backend.*;

public class Antylopa extends Zwierze{
    private final static int ANTYLOPA_SILA = 4;
    private final static int ANTYLOPA_INIC = 4;
    private final static char ANTYLOPA_CHAR = 'A';
    private final static int ANTYLOPA_POLOG = 5;
    private final static int ANTYLOPA_PELNOLETNOSC = 10;
    private final static String ANTYLOPA_NAZWA = "Antylopa";
    private final static int SZANSA_NA_UCIECZKE = 50;

    public Antylopa(Swiat swiat, int x, int y) { super(swiat, x, y, ANTYLOPA_SILA, ANTYLOPA_INIC, ANTYLOPA_PELNOLETNOSC); }
    public void Akcja() {
        Wsp n_wsp = new Wsp();
        n_wsp = swiat.losujSasiada(this.wsp);
        n_wsp = swiat.losujSasiada(n_wsp);
        if(n_wsp.x == this.wsp.x && n_wsp.y == this.wsp.y) { n_wsp = swiat.losujSasiada(this.wsp); }

        this.inicjujKolizje(n_wsp);
    }
    public boolean Koliduj(Organizm somsiad, boolean czyAtakuje) {
        if (somsiad.getTyp() == TYP_ZWIERZE) {
            Wsp n_wsp = new Wsp(this.wsp);									// okreslenie		//
            if (czyAtakuje == true) { n_wsp = somsiad.getWsp(); }	        // miejsca walki	//
            Random rand = new Random();
            int tmp = rand.nextInt(100);
            if (tmp < SZANSA_NA_UCIECZKE) {
                Wsp nn_wsp = new Wsp(swiat.znajdzWolnePole(n_wsp));
                if (nn_wsp.x != n_wsp.x || nn_wsp.y != n_wsp.y) {
                    swiat.usunZPlanszy(this.wsp);
                    this.wsp = nn_wsp;
                    swiat.wstawDoPlanszy(this, this.wsp);
                    swiat.usunZPlanszy(somsiad.getWsp());
                    somsiad.Przesun(n_wsp);
                    swiat.wstawDoPlanszy(somsiad, somsiad.getWsp());
                    return true;
                }
            }
        }
        return false;
    }
    public void dodajPolog() { this.polog = ANTYLOPA_POLOG; }
    public Organizm dajPotomka(Wsp n_wsp) {
        Organizm tmp = new Antylopa(swiat, n_wsp.x, n_wsp.y);
        swiat.DodajOrganizm(tmp);
        return tmp;
    }
    public boolean czyTenSamGatunek(Organizm o) { if (o instanceof Antylopa) { return true; } else return false; }
    public char getChar() { return ANTYLOPA_CHAR; }
    public String getNazwa() { return ANTYLOPA_NAZWA; }
}
