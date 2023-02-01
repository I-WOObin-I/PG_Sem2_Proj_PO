package gra.resources.backend;
import java.util.ArrayList;
import gra.resources.Rosliny.*;
import gra.resources.Zwierzeta.*;

public class KontrolerOrganizmow {
    private ArrayList<Organizm> gatunki = new ArrayList<Organizm>();

    public KontrolerOrganizmow(Swiat swiat) {
        gatunki.add(new Czlowiek(swiat, 0, 0));
        gatunki.add(new Wilk(swiat, 0, 0));
        gatunki.add(new Owca(swiat, 0, 0));
        gatunki.add(new Lis(swiat, 0, 0));
        gatunki.add(new Zolw(swiat, 0, 0));
        gatunki.add(new Antylopa(swiat, 0, 0));
        gatunki.add(new Trawa(swiat, 0, 0));
        gatunki.add(new Mlecz(swiat, 0, 0));
        gatunki.add(new Guarana(swiat, 0, 0));
        gatunki.add(new WilczaJagoda(swiat, 0, 0));
        gatunki.add(new BarszczSosnowskiego(swiat, 0, 0));
    }
}
