package gra.resources.backend;
import java.util.Random;

public abstract class Roslina extends Organizm {
    protected final static int SZANSA_ROZMN = 25;

    public Roslina(Swiat swiat, int x, int y, int sila) { super(swiat, x, y, sila, 0, TYP_ROSLINA, 0); }

    @Override
    public void Akcja() {
        domyslnaAkcja();
    }
    public void domyslnaAkcja() {
        Random rand = new Random();
        int tmp2 = rand.nextInt(100);
        if (tmp2 <= SZANSA_ROZMN) {
            Wsp n_wsp = new Wsp(swiat.losujSasiada(this.wsp));
            this.inicjujKolizje(n_wsp);
        }
    }
    public void inicjujKolizje(Wsp n_wsp) { // nie zachodzi zadna kolizja miedzy roslinami tego samego gatunku //
        if (swiat.getOrg(n_wsp) != null) {
            Organizm somsiad = swiat.getOrg(n_wsp);
            if (this.Koliduj(somsiad, true) == false && somsiad.Koliduj(this, false) == false && this.czyTenSamGatunek(somsiad) == false) {
                this.kolidujDomyslnie(somsiad);
            }
        }
        else { this.dajPotomka(n_wsp); }
    }
    public void kolidujDomyslnie(Organizm somsiad) { // domsylna kolizja jest wywolywana tylko dla atakujacego //
        if (this.getS() >= somsiad.getS()) {
            swiat.usunOrganizm(somsiad);
            Wsp n_wsp = new Wsp(somsiad.getWsp());
            this.dajPotomka(n_wsp);
            swiat.DodajLogWalki(new LogWalki(somsiad.getX(), somsiad.getY(), this.getNazwa(), somsiad.getNazwa(), "zabil"));
        }
        else {
            String s = new String("");
            if (somsiad.getTyp() == TYP_ZWIERZE) { s = "zjadl"; }
            else { s = "zabil"; }
            swiat.DodajLogWalki(new LogWalki(somsiad.getX(), somsiad.getY(), somsiad.getNazwa(), this.getNazwa(), s));
        }
    }
    @Override
    public void AktualizujBuffyDebuffy() {}
}
