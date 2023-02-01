package gra;
import java.util.Random;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.plaf.ColorUIResource;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import gra.resources.backend.Organizm;
import gra.resources.backend.Wsp;
import gra.resources.backend.Swiat;

import gra.resources.Rosliny.*;
import gra.resources.Zwierzeta.*;

public class PlanszaHEX extends Plansza{
    private final static int LICZBA_SASIADOW = 6;
    private final static int ROZMIAR_PLANSZY = 900;

    private int promien;
    private int srednica;
    private int promienPlanszy;
    private int rozmiarPola;
	protected Organizm koord[][];
    private JPanel panel;
    private Swiat swiat;

    public PlanszaHEX(int promien, Swiat swiatw) {
        this.promien = promien;
        this.srednica = promien*2 - 1;
        this.promienPlanszy = srednica*2 + 1;
        this.rozmiarPola = 900/promienPlanszy;
        this.swiat = swiatw;
        this.koord = new Organizm [srednica][srednica];
        for (int i = 0; i < srednica; i++) {
            for (int j = 0; j < srednica; j++) {
                koord[i][j] = null;
            }
        }
        this.panel = new PlanszaPrzyciskow();
    }
    
    public class PlanszaPrzyciskow extends JPanel{
        private Action planszaAkcji[][];
        private JButton planszaPrzyciskow[][];

        public PlanszaPrzyciskow() {
            this.setLayout(new GridLayout(promienPlanszy, promienPlanszy));
            this.setPreferredSize(new Dimension(ROZMIAR_PLANSZY, ROZMIAR_PLANSZY));

            ImageIcon Vicon = new ImageIcon(driver.class.getResource("src/Vborder.png"));
            ImageIcon Iicon = new ImageIcon(driver.class.getResource("src/Iborder.png"));
            ImageIcon Aicon = new ImageIcon(driver.class.getResource("src/Aborder.png"));
            Image img, newimg;
            img = Vicon.getImage();
            newimg = img.getScaledInstance(rozmiarPola,rozmiarPola, java.awt.Image.SCALE_SMOOTH);
            Vicon = new ImageIcon(newimg);  
            img = Iicon.getImage();
            newimg = img.getScaledInstance(rozmiarPola,rozmiarPola, java.awt.Image.SCALE_SMOOTH);
            Iicon = new ImageIcon(newimg);
            img = Aicon.getImage();
            newimg = img.getScaledInstance(rozmiarPola,rozmiarPola, java.awt.Image.SCALE_SMOOTH);
            Aicon = new ImageIcon(newimg);

            planszaPrzyciskow = new JButton[promienPlanszy][promienPlanszy];
            planszaAkcji = new PrzyciskPlanszy[srednica][srednica];

            int ii, jj;
            Wsp tmp1, tmp2;
            for(int i=0; i<promienPlanszy; i++) {
                for(int j=0;j<promienPlanszy; j++) {
                    planszaPrzyciskow[i][j] = new JButton();
                    planszaPrzyciskow[i][j].setBackground(Color.darkGray);
                    planszaPrzyciskow[i][j].setBorderPainted(false);
                    planszaPrzyciskow[i][j].setPreferredSize(new Dimension(rozmiarPola, rozmiarPola));
                    if(i%2==0) {
                        if((promien%2 + j%2 + i/2)%2 == 0)    { planszaPrzyciskow[i][j].setIcon(Aicon); }
                        else                                  { planszaPrzyciskow[i][j].setIcon(Vicon); }
                    }
                    else {
                        if((promien%2 + j%2 + i/2)%2 == 1)    { planszaPrzyciskow[i][j].setIcon(Iicon); }
                        else {
                            if((i/2 - (promien-1)) == j/2 ) { planszaPrzyciskow[i][j].setBackground(Color.CYAN); }
                            
                            //tmp1 = new Wsp(i,j); tmp2 = hexToWsp(tmp1); ii = tmp2.x; jj = promien - tmp2.y - 1;
                            //planszaAkcji[ii][jj] = new PrzyciskPlanszy(ii, jj);
                            //planszaPrzyciskow[ii][jj].setAction(planszaAkcji[ii][jj]);
                        }
                    }
                    add(planszaPrzyciskow[i][j]);
                }
            }
        }


        public void usunOrganizm(int x, int y) {
            planszaPrzyciskow[y-1][x].setIcon(new ImageIcon(driver.class.getResource("src/empty.png")));
        }
        public void wstawOrganizm(int x, int y, ImageIcon icon) {
            planszaPrzyciskow[y-1][x].setIcon(icon);
        }
        public void resetPanel() {
            this.revalidate();
            this.repaint();
            //this.setVisible(false);
            //this.setVisible(true);
        }
        
        public class PrzyciskPlanszy extends AbstractAction{
            private int x, y;
            PrzyciskPlanszy(int xx, int yy) { super(); x = xx; y = yy; }
            public void actionPerformed(ActionEvent e) {
                Object source = e.getSource();
                swiat.wstawNaPozycji(x, y);
            }
        }

        private Wsp wspToHex(Wsp wsp) {
            int x, y;
            x = wsp.x*2 + wsp.y;
            y = wsp.y*2;
            Wsp n_wsp = new Wsp(x, y);
            return n_wsp;
        }
        private Wsp hexToWsp(Wsp wsp) {
            int x, y;
            x = wsp.x - wsp.y/2; x = x/2;
            y = wsp.y/2;
            Wsp n_wsp = new Wsp(x, y);
            return n_wsp;
        }

    }



    public void WstawOrganizm(Organizm o, Wsp wsp) {
        if (wsp.x < 0 || wsp.x >= this.promien || wsp.y < 0 || wsp.y >= this.promien) {
            //cout << endl << "koordy x/y wyszly poza plansze: " << wsp.x << ", " << wsp.y << endl;
            System.out.print("\nkoordy x/y wyszly poza plansze: " + wsp.x + ", " + wsp.y + "\n");
            return;
        }
        else {
            this.koord[wsp.x][wsp.y] = o;
        }
        String s = "src/";
        s = s + o.getNazwa();
        s = s + ".png";
        ImageIcon icon = new ImageIcon(driver.class.getResource(s));
        Image img = icon.getImage();
        Image newimg = img.getScaledInstance(26,26, java.awt.Image.SCALE_SMOOTH);
        icon = new ImageIcon(newimg);
        ((PlanszaPrzyciskow) panel).wstawOrganizm(wsp.x, wsp.y, icon);
    }
    public void UsunOrganizm(Wsp wsp) {
        if (wsp.x < 0 || wsp.x >= this.promien || wsp.y < 0 || wsp.y >= this.promien) {
            //cout << endl << "koordy x/y wyszly poza plansze: " << wsp.x << ", " << wsp.y << endl;
            System.out.print("\nkoordy x/y wyszly poza plansze: " + wsp.x + ", " + wsp.y + "\n");
            return;
        }
        else {
            this.koord[wsp.x][wsp.y] = null;
        }
        ((PlanszaPrzyciskow) panel).usunOrganizm(wsp.x, wsp.y);
    }
    
    public void RysujPlansze() {
        resetPanel();
        /*
        //cout << " O=";
        System.out.print(" O=");
        for (int j = 0; j < this.promien; j++) {
            //cout << "==";
            System.out.print("==");
        }
        //cout << "O" << endl;
        System.out.print("O\n");
        for (int i = this.promien - 1; i >= 0; i--) {
            //if (i >= 10) { cout << i << " "; }
            //else { cout << " " << i << " "; }
            //cout << " | ";
            System.out.print(" | ");
            for (int j = 0; j < this.promien; j++) {
                if (koord[j][i] == null) { /*cout << PUSTE_POLE << " "; System.out.print(PUSTE_POLE + " "); }
                else { /*cout << this.koord[j][i].getChar() << " "; System.out.print(this.koord[j][i].getChar() + " "); }
            }
            //cout << "| ";
            //cout << endl;
            System.out.print("| \n");
        }
        //cout << "   ";
        //for (int j = 0; j < this.promien; j++) {
        //	if (j >= 10) { cout << j; }
        //	else { cout << j << " "; }
        //}
        //cout << " O=";
        System.out.print(" O=");
        for (int j = 0; j < this.promien; j++) {
            //cout << "==";
            System.out.print("==");
        }
        //cout << "O";
        //cout << "\n\n";
        System.out.print("O\n\n");
        //cout << "  ";
        //for (int j = 0; j < this.width; j++) { cout << j << " "; }
        //cout << endl;
        /**/
    }
    public void WyczyscPlansze() {
        for (int i = 0; i < promien; i++) {
            for (int j = 0; j < promien; j++) {
                koord[i][j] = null;
            }
        }
    }
    public void resetPanel() {
        ((PlanszaPrzyciskow) panel).resetPanel();
    }

    public boolean czyWPlanszy(Wsp wsp) {
        if (wsp.x >= 0 && wsp.x < this.promien && wsp.y >= 0 && wsp.y < this.promien) { return true; }
        else { return false; }
    }
    public Wsp losujSasiada(Wsp wsp) {
        //System.out.println("losowanie sasiada...");
        //System.out.println("stare wsp: " + wsp.x + ", " + wsp.y);
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
    
    public int getSzerokosc() { return promien; }
    public int getWysokosc()  { return promien;  }
    public Organizm getOrg(Wsp wsp) { return this.koord[wsp.x][wsp.y]; }
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
        
        //System.out.println("nowe wsp: " + n_wsp.x + ", " + n_wsp.y);
        //if(n_wsp.y > 32) { return wsp; }
        if (czyWPlanszy(n_wsp) == false) { n_wsp = rotacjaSasiadow(wsp, n_wsp); }
        return n_wsp;
    }
    public Wsp znajdzNajblizszyGatunek(Wsp wsp, Organizm o) {
        int maxr = wsp.y;
        int tmp;
        Wsp n_wsp = new Wsp(wsp);
        tmp = promien - wsp.y - 1;     if(tmp > maxr) { maxr = tmp; }
        tmp = wsp.x;                    if(tmp > maxr) { maxr = tmp; }
        tmp = promien - wsp.x - 1;    if(tmp > maxr) { maxr = tmp; }
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
}
