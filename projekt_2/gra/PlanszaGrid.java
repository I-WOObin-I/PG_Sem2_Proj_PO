package gra;
import gra.resources.backend.Organizm;
import gra.resources.backend.Wsp;
import gra.resources.backend.Swiat;

import java.util.Random;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;


public class PlanszaGrid extends Plansza{
    private final static int LICZBA_SASIADOW = 8;
    private final static int PANEL_WIDTH = 900;
    private final static int PANEL_HEIGHT = 900;

    private int szerokosc;
	private int wysokosc;
    private int rozmiarPola;
	protected Organizm koord[][];
    private JPanel panel;
    private Swiat swiat;

    public PlanszaGrid(int szerokosc, int wysokosc, Swiat swiatw) {
        this.szerokosc = szerokosc;
        this.wysokosc = wysokosc;
        this.rozmiarPola = PANEL_HEIGHT / wysokosc;
        this.swiat = swiatw;
        this.koord = new Organizm [wysokosc][szerokosc];
        for (int i = 0; i < wysokosc; i++) {
            for (int j = 0; j < szerokosc; j++) {
                koord[i][j] = null;
            }
        }
        this.panel = new PlanszaPrzyciskow(szerokosc, wysokosc);
    }

    public void WstawOrganizm(Organizm o, Wsp wsp) {
        if (czyWPlanszy(wsp) == false) { return; }
        else { this.koord[wsp.x][wsp.y] = o; }

        String s = "src/";
        s = s + o.getNazwa();
        s = s + ".png";
        ImageIcon icon = new ImageIcon(driver.class.getResource(s));
        Image img = icon.getImage();
        Image newimg = img.getScaledInstance(rozmiarPola, rozmiarPola, java.awt.Image.SCALE_SMOOTH);
        icon = new ImageIcon(newimg);

        ((PlanszaPrzyciskow) panel).wstawOrganizm(wsp.x, wsp.y, icon);
    }
    public void UsunOrganizm(Wsp wsp) {
        if (czyWPlanszy(wsp) == false) { return; }
        else { this.koord[wsp.x][wsp.y] = null; }
        ((PlanszaPrzyciskow) panel).usunOrganizm(wsp.x, wsp.y);
    }
    
    public void RysujPlansze() { resetPanel(); }
    public void WyczyscPlansze() {
        for (int i = 0; i < szerokosc; i++) {
            for (int j = 0; j < wysokosc; j++) {
                koord[i][j] = null;
            }
        }
    }
    public void resetPanel() { ((PlanszaPrzyciskow) panel).resetPanel(); }

    public boolean czyWPlanszy(Wsp wsp) {
        if (wsp.x >= 0 && wsp.x < this.szerokosc && wsp.y >= 0 && wsp.y < this.wysokosc) { return true; }
        else { return false; }
    }
    public Wsp losujSasiada(Wsp wsp) {
        if (czyWPlanszy(wsp) == false) { return wsp; }
        Random rand = new Random();
        int tmp = rand.nextInt(LICZBA_SASIADOW);
        Wsp n_wsp = new Wsp(wsp);
        n_wsp = rotacjaSasiadow(wsp, n_wsp);
        for (int i = 0; i < tmp; i++) {
            n_wsp = rotacjaSasiadow(wsp, n_wsp);
        }
        return n_wsp;
    }
    public Wsp znajdzWolnePole(Wsp wsp) {
        Wsp tmp = new Wsp(losujSasiada(wsp));
        boolean czyZnalazl = false;
        for (int i = 0; i < LICZBA_SASIADOW; i++) {
            if (getOrg(tmp) == null) { czyZnalazl = true; break; }
            tmp = rotacjaSasiadow(wsp, tmp);
        }
        if (czyZnalazl == true) { return tmp; }
        return wsp;
    }
    
    public int getSzerokosc() { return szerokosc; }
    public int getWysokosc()  { return wysokosc;  }
    public Organizm getOrg(Wsp wsp) { if(czyWPlanszy(wsp)) { return this.koord[wsp.x][wsp.y]; } return null; }
    public int getLiczbeSasiadow() { return LICZBA_SASIADOW; }
    public Component getJPanel() { return panel; }
    
    public Wsp rotacjaSasiadow(Wsp wsp, Wsp n_wsp) {
        if (n_wsp.x == wsp.x && n_wsp.y == wsp.y) { n_wsp.y++; }				// 5 //
        else if (n_wsp.x == wsp.x && n_wsp.y == wsp.y + 1) { n_wsp.x++; }		// 8 //
        else if (n_wsp.x == wsp.x + 1 && n_wsp.y == wsp.y + 1) { n_wsp.y--; }	// 9 //
        else if (n_wsp.x == wsp.x + 1 && n_wsp.y == wsp.y) { n_wsp.y--; }		// 6 //
        else if (n_wsp.x == wsp.x + 1 && n_wsp.y == wsp.y - 1) { n_wsp.x--; }	// 3 //
        else if (n_wsp.x == wsp.x && n_wsp.y == wsp.y - 1) { n_wsp.x--; }		// 2 //
        else if (n_wsp.x == wsp.x - 1 && n_wsp.y == wsp.y - 1) { n_wsp.y++; }	// 1 //
        else if (n_wsp.x == wsp.x - 1 && n_wsp.y == wsp.y) { n_wsp.y++; }		// 4 //
        else if (n_wsp.x == wsp.x - 1 && n_wsp.y == wsp.y + 1) { n_wsp.x++; }	// 7 //
        
        if (czyWPlanszy(n_wsp) == false) { n_wsp = rotacjaSasiadow(wsp, n_wsp); }
        return n_wsp;
    }
    public Wsp znajdzNajblizszyGatunek(Wsp wsp, Organizm o) {
        int maxr = wsp.y;
        int tmp;
        Wsp n_wsp = new Wsp(wsp);
        tmp = wysokosc - wsp.y - 1;     if(tmp > maxr) { maxr = tmp; }
        tmp = wsp.x;                    if(tmp > maxr) { maxr = tmp; }
        tmp = szerokosc - wsp.x - 1;    if(tmp > maxr) { maxr = tmp; }
        for(int r=1; r<=maxr; r++) {
            n_wsp.x = wsp.x;
            n_wsp.y = wsp.y;
            n_wsp.y += r;
            if(czyWPlanszy(n_wsp) && koord[n_wsp.x][n_wsp.y] != null && o.czyTenSamGatunek(getOrg(n_wsp))) { return n_wsp; }
            for(int i=0;i<r;i++) {
                n_wsp.x++;
                if(czyWPlanszy(n_wsp) && koord[n_wsp.x][n_wsp.y] != null && o.czyTenSamGatunek(getOrg(n_wsp))) { return n_wsp; }
            }
            for(int i=0; i<2*r; i++) {
                n_wsp.y--;
                if(czyWPlanszy(n_wsp) && koord[n_wsp.x][n_wsp.y] != null && o.czyTenSamGatunek(getOrg(n_wsp))) { return n_wsp; }
            }
            for(int i=0; i<2*r; i++) {
                n_wsp.x--;
                if(czyWPlanszy(n_wsp) && koord[n_wsp.x][n_wsp.y] != null && o.czyTenSamGatunek(getOrg(n_wsp))) { return n_wsp; }
            }
            for(int i=0; i<2*r; i++) {
                n_wsp.y++;
                if(czyWPlanszy(n_wsp) && koord[n_wsp.x][n_wsp.y] != null && o.czyTenSamGatunek(getOrg(n_wsp))) { return n_wsp; }
            }
            for(int i=0; i<r-1; i++) {
                n_wsp.y++;
                if(czyWPlanszy(n_wsp) && koord[n_wsp.x][n_wsp.y] != null && o.czyTenSamGatunek(getOrg(n_wsp))) { return n_wsp; }
            }
        }
        return wsp;
    }

    public class PlanszaPrzyciskow extends JPanel{
        private Action planszaAkcji[][];
        private JButton planszaPrzyciskow[][];

        public PlanszaPrzyciskow(int szerokosc, int wysokosc) {
            this.setLayout(new GridLayout(wysokosc, szerokosc));
            this.setPreferredSize(new Dimension(PANEL_WIDTH, PANEL_HEIGHT));

            planszaPrzyciskow =    new JButton[wysokosc][szerokosc];
            planszaAkcji = new PrzyciskPlanszy[wysokosc][szerokosc];
            
            for(int i=0; i<wysokosc; i++) {
                for(int j=0;j<szerokosc; j++) {
                    planszaAkcji[i][j] = new PrzyciskPlanszy(j, wysokosc-i-1);
                    planszaPrzyciskow[i][j] = new JButton();
                    planszaPrzyciskow[i][j].setAction(planszaAkcji[i][j]);
                    planszaPrzyciskow[i][j].setBorderPainted(false);
                    planszaPrzyciskow[i][j].setPreferredSize(new Dimension(rozmiarPola, rozmiarPola));

                    if((i+j)%2 == 0)    { planszaPrzyciskow[i][j].setBackground(Color.darkGray);    }
                    else                { planszaPrzyciskow[i][j].setBackground(Color.black);       }

                    add(planszaPrzyciskow[i][j]);
                }
            }
        }


        public void usunOrganizm(int x, int y) {
            planszaPrzyciskow[wysokosc-y-1][x].setIcon(new ImageIcon(driver.class.getResource("src/empty.png")));
        }
        public void wstawOrganizm(int x, int y, ImageIcon icon) {
            planszaPrzyciskow[wysokosc-y-1][x].setIcon(icon);
        }
        public void resetPanel() {
            this.revalidate();
            this.repaint();
        }
        
        public class PrzyciskPlanszy extends AbstractAction{
            private int x, y;
            PrzyciskPlanszy(int xx, int yy) { super(); x = xx; y = yy; }
            public void actionPerformed(ActionEvent e) { swiat.wstawNaPozycji(x, y); }
        }

    }
}
