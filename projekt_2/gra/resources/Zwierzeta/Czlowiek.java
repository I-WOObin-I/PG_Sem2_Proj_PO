package gra.resources.Zwierzeta;
import gra.resources.backend.*;


public class Czlowiek extends Zwierze{
    private final static int CZLOWIEK_SILA = 5;
    private final static int CZLOWIEK_INIC = 4;
    private final static char CZLOWIEK_CHAR = '8';
    private final static int CZLOWIEK_PELNOLETNOSC = 10;
    private final static String CZLOWIEK_NAZWA = "Czlowiek";
    private final static String TARCZA_NAPIS = "Tarcza Alzura";
    private final static int CZAS_DZIALANIA_TARCZY = 5;
    private final static int COOLDOWN_TARCZY = 5;
    private final static int PRZYCISK_TARCZY = 83;
    private final static int KEY_UP = 38;
    private final static int KEY_DOWN = 40;
    private final static int KEY_LEFT = 37;
    private final static int KEY_RIGHT = 39;
    protected int input = 0;
    private int czasTarczy = 0;

    public Czlowiek(Swiat swiat, int x, int y) {
        super(swiat, x, y, CZLOWIEK_SILA, CZLOWIEK_INIC, CZLOWIEK_PELNOLETNOSC);
    }

    public void Akcja() {
        Wsp n_wsp = new Wsp(this.wsp);
            if(input == 0) { return; }
            if (input == KEY_UP) { n_wsp.y++; }
            else if (input == KEY_DOWN) { n_wsp.y--; }
            else if (input == KEY_LEFT) { n_wsp.x--; }
            else if (input == KEY_RIGHT) { n_wsp.x++; }
            else if (input == PRZYCISK_TARCZY) {
            if (this.czasTarczy == 0) {
            swiat.DodajLogWalki(new LogWalki(this.getX(), this.getY(), TARCZA_NAPIS, "AKTYWOWANA", "")); 
            this.czasTarczy = CZAS_DZIALANIA_TARCZY + COOLDOWN_TARCZY;
            }
        }
        if (swiat.czyWPlanszy(n_wsp) == false) { n_wsp = this.wsp; }
        this.input = 0;
        this.inicjujKolizje(n_wsp);
    }
    public boolean Koliduj(Organizm somsiad, boolean czyAtakuje) {
        if (this.czasTarczy > COOLDOWN_TARCZY && somsiad.getTyp() == TYP_ZWIERZE) {
            Wsp n_wsp = this.wsp;
            Wsp nn_wsp = this.wsp;
            if (czyAtakuje == true) { n_wsp = somsiad.getWsp(); }	// n_wsp - miejsce walki //
            nn_wsp = swiat.losujSasiada(n_wsp);
            somsiad.inicjujKolizje(nn_wsp);
            swiat.usunZPlanszy(wsp);
            this.wsp = n_wsp;
            swiat.wstawDoPlanszy(this, this.wsp);
            return true;
        }
        return false;
    }
    public void dodajPolog() {}
    public Organizm dajPotomka(Wsp n_wsp) {
        Organizm tmp = new Czlowiek(swiat, n_wsp.x, n_wsp.y);
        swiat.DodajOrganizm(tmp);
        return tmp;
    }
    public boolean czyTenSamGatunek(Organizm o) { return false; }
    public void AktualizujBuffyDebuffy() {
        if (this.czasTarczy > 0) {
            czasTarczy--;
            if(this.czasTarczy == COOLDOWN_TARCZY) {
                swiat.DodajLogWalki(new LogWalki(this.getX(), this.getY(), TARCZA_NAPIS, "DEZAKTYWOWANA", ""));
            }
            if(this.czasTarczy == 0) {
                swiat.DodajLogWalki(new LogWalki(this.getX(), this.getY(), TARCZA_NAPIS, "ZREGENEROWANA", ""));
            }
        }
    }
    public char getChar() { return CZLOWIEK_CHAR; }
    public String getNazwa() { return CZLOWIEK_NAZWA; }
    public void ustawInput(int in) { this.input = in; }
}