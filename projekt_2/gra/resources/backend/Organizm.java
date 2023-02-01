package gra.resources.backend;

public abstract class Organizm {
    protected final static int TYP_ZWIERZE = 1;
    protected final static int TYP_ROSLINA = 2;

    protected boolean zywy = true;
	protected int sila;
	protected int inicjatywa;
	protected int typ;
	protected int polog;
	protected int buff = 0;
	protected Wsp wsp;
	protected Swiat swiat;

    public abstract boolean czyTenSamGatunek(Organizm o);

    Organizm(Swiat swiat, int x, int y, int sila, int inicjatywa, int typ, int polog) {
        this.swiat = swiat;
        this.wsp = new Wsp(x, y);
        this.sila = sila;
        this.inicjatywa = inicjatywa;
        this.typ = typ;
        this.polog = polog;
    }

    public abstract void Akcja();
    public abstract boolean Koliduj(Organizm somsiad, boolean czyAtakuje);
    public abstract void kolidujDomyslnie(Organizm somsiad);
    public abstract void inicjujKolizje(Wsp n_wsp);
    public abstract void AktualizujBuffyDebuffy();
    public abstract Organizm dajPotomka(Wsp wsp);
    public abstract char getChar();
    public abstract String getNazwa();

    public void Zabij() { this.zywy = false; }
    public void Przesun(Wsp n_wsp) { this.wsp = n_wsp; }
    public void dodajBuff(int b) { this.buff += b; }
    public void dodajPolog() { return; }
    public boolean czyGotowyDoRozmnazania() { return true; }
    public int getX() { return wsp.x; }
    public int getY() { return wsp.y; }
    public int getS() { return sila + buff; }
    public int getI() { return inicjatywa; }
    public int getTyp() { return typ; }
    public int getPolog() { return polog; }
    public int getBuff() { return buff; }
    public boolean getZ() { return zywy; }
    public Wsp getWsp() { return wsp; }
}
