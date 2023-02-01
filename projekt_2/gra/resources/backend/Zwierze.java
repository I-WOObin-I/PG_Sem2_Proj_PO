package gra.resources.backend;

public abstract class Zwierze extends Organizm {
    public Zwierze(Swiat swiat, int x, int y, int sila, int inicjatywa, int pelnoletnsoc) { super(swiat, x, y, sila, inicjatywa, TYP_ZWIERZE, pelnoletnsoc); }

    @Override
    public void Akcja() {
        domyslaAkcja();
    }
    public void domyslaAkcja() { 
        Wsp n_wsp = new Wsp();
        n_wsp = swiat.losujSasiada(this.wsp);
        this.inicjujKolizje(n_wsp);
    }
    @Override
    public void inicjujKolizje(Wsp n_wsp) {
        if (swiat.getOrg(n_wsp) != null) {
            Organizm somsiad = swiat.getOrg(n_wsp);
            if (this.czyTenSamGatunek(somsiad) == true) {
                this.Kopulacja(somsiad);
                n_wsp = this.wsp;
            }
            else {
                if (this.Koliduj(somsiad, true) == false && somsiad.Koliduj(this, false) == false) {
                    this.kolidujDomyslnie(somsiad);
                }
            }
        }
        else {
            swiat.usunZPlanszy(this.wsp);
            this.wsp = n_wsp;
            swiat.wstawDoPlanszy(this, this.wsp);
        }
    }
    @Override
    public void kolidujDomyslnie(Organizm somsiad) { // domsylna kolizja jest wywolywana tylko dla atakujacego //
        if (this.getS() >= somsiad.getS()) {
            String s = new String("");
            if (somsiad.getTyp() == TYP_ROSLINA) { s = "zjadl"; }
            else { s = "zabil"; }

            swiat.usunOrganizm(somsiad);
            swiat.usunZPlanszy(this.wsp);
            this.wsp.x = somsiad.getWsp().x;
            this.wsp.y = somsiad.getWsp().y;
            swiat.wstawDoPlanszy(this, this.wsp);
            swiat.DodajLogWalki(new LogWalki(somsiad.getX(), somsiad.getY(), this.getNazwa(), somsiad.getNazwa(), s));
        }
        else {
            swiat.usunOrganizm(this);
            swiat.DodajLogWalki(new LogWalki(somsiad.getX(), somsiad.getY(), somsiad.getNazwa(), this.getNazwa(), "zabil"));
        }
    }
    @Override
    public void AktualizujBuffyDebuffy() {
        if (this.polog > 0) { this.polog--; }
    }
    public void Kopulacja(Organizm somsiad) {		// nowy organizm nie rodzi sie jesli zaden z rodzicow nie ma wolnego miejsca obok siebie //
        if (this.czyGotowyDoRozmnazania() && somsiad.czyGotowyDoRozmnazania()) {
            Wsp n_wsp = new Wsp(somsiad.getWsp());
            Wsp nn_wsp = new Wsp(swiat.znajdzWolnePole(this.wsp));
            if (nn_wsp.x == this.wsp.x && nn_wsp.y == this.wsp.y) {
                nn_wsp = swiat.znajdzWolnePole(n_wsp);
                if (nn_wsp.x != n_wsp.x || nn_wsp.y != n_wsp.y) {
                    this.dajPotomka(nn_wsp);
                    this.dodajPolog();
                    somsiad.dodajPolog();
                }
            }
            else {
                this.dajPotomka(nn_wsp);
                this.dodajPolog();
                somsiad.dodajPolog();
            }
        }
    }
    @Override
    public boolean czyGotowyDoRozmnazania() { if (polog == 0) { return true; } else return false; }
}
