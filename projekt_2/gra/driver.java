package gra;
import gra.resources.backend.*;
import gra.resources.Rosliny.*;
import gra.resources.Zwierzeta.*;

import javax.swing.*;
import java.awt.*;

public class driver extends JFrame {
    private static final int PLANE_WIDTH = 30;
    private static final int PLANE_HEIGHT = PLANE_WIDTH;
    private static Swiat swiat;

    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                swiat = new Swiat(PLANE_WIDTH, PLANE_HEIGHT);
                /**/
                swiat.DodajOrganizm(new Wilk(swiat, 2, 3));
                swiat.DodajOrganizm(new Wilk(swiat, 1, 3));
                swiat.DodajOrganizm(new Owca(swiat, 4, 6));
                swiat.DodajOrganizm(new Antylopa(swiat, 15, 10));
                swiat.DodajOrganizm(new Guarana(swiat, 2, 25));
                swiat.DodajOrganizm(new Lis(swiat, 3, 5));
                swiat.DodajOrganizm(new Mlecz(swiat, 25, 2));
                swiat.DodajOrganizm(new Trawa(swiat, 12, 27));
                swiat.DodajOrganizm(new WilczaJagoda(swiat, 9, 10));
                swiat.DodajOrganizm(new Zolw(swiat, 15, 15));
                swiat.DodajOrganizm(new BarszczSosnowskiego(swiat, 15, 29));
                swiat.DodajOrganizm(new Guarana(swiat, 25, 25));
                swiat.DodajOrganizm(new CyberOwca(swiat, 11, 22));
                //swiat.DodajOrganizm(new CyberOwca(swiat, 18, 22));
                swiat.DodajOrganizm(new Czlowiek(swiat, 20, 20));
                /*
                swiat.DodajOrganizm(new Wilk(swiat, 0, 0));
                swiat.DodajOrganizm(new Owca(swiat, 0, 4));
                swiat.DodajOrganizm(new Antylopa(swiat, 4, 0));
                swiat.DodajOrganizm(new Mlecz(swiat, 4, 4));
                /**/
                swiat.przejdzTure();
            }
        });
    }
}
