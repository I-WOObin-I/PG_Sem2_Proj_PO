package gra.resources.backend;
import gra.OknoGry;
import gra.PlanszaGrid;
import gra.driver;
import gra.resources.Rosliny.*;
import gra.resources.Zwierzeta.*;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;
import javax.swing.*;
import javax.swing.JLabel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.io.FileWriter;
import javax.swing.JPanel;
import gra.*;


public class Swiat {
    private static final int LICZBA_LOGOW = 10;

    private Plansza plansza;
    private OknoGry oknoGry;
	private ArrayList<Organizm> organizmy = new ArrayList<Organizm>();
    private ArrayList<Organizm> gatunki = new ArrayList<Organizm>();
	private Stack<Organizm> organizmyMartwe = new Stack<Organizm>();
	private Stack<Organizm> organizmyNoworodki = new Stack<Organizm>();
	private Stack<LogWalki> logiWalki = new Stack<LogWalki>();
    private Czlowiek czlowiek = null;
    private JPanel panelLogi;
    private JPanel panelGatunki;
    private Wsp wstawGatunekWsp = new Wsp();

	private void AktualizujOrganizmy() {
        for(int i=0 ; i<organizmy.size() ; i++) {
            Organizm tmp = organizmy.get(i);
            if (tmp.getZ() == false) { continue; }
            tmp.AktualizujBuffyDebuffy();
            tmp.Akcja();
        }
    }
	private void UrodzNoworodki() {
        while (organizmyNoworodki.empty() == false) {
            Organizm tmp = organizmyNoworodki.peek();
            if (organizmy.isEmpty() == true) { organizmy.add(tmp); }
            else {
                int i = 0;
                for (; i<organizmy.size() ; i++) { 
                    Organizm tmp2 = organizmy.get(i);
                    if (tmp.getI() > tmp2.getI()) { organizmy.add(i, tmp); break; }
                }
                 if (i == organizmy.size()) { organizmy.add(tmp); }
            }
            plansza.WstawOrganizm(tmp, tmp.getWsp());
            organizmyNoworodki.pop();
        }
    }
	private void usunMartwe() {
        while (true) {
            if (!organizmyMartwe.empty()) {
                organizmy.remove(organizmyMartwe.peek());
                organizmyMartwe.pop();
            }
            else { break; }
        }
    }
    private void zapiszListeGatunkow() {
        gatunki.add(new BarszczSosnowskiego(this, 0, 0)); 
        gatunki.add(new Guarana(this, 0, 0));
        gatunki.add(new Mlecz(this, 0, 0));
        gatunki.add(new Trawa(this, 0, 0));
        gatunki.add(new WilczaJagoda(this, 0, 0));
        gatunki.add(new Antylopa(this, 0, 0));
        gatunki.add(new CyberOwca(this, 0, 0));
        gatunki.add(new Czlowiek(this, 0, 0));
        gatunki.add(new Krolik(this, 0, 0));
        gatunki.add(new Lis(this, 0, 0));
        gatunki.add(new Owca(this, 0, 0));
        gatunki.add(new Wilk(this, 0, 0));
        gatunki.add(new Zolw(this, 0, 0));
    }
    //////////

    public Swiat(int szerokosc, int wysokosc) {
        plansza = new PlanszaGrid(szerokosc, wysokosc, this);
        panelLogi = new PanelLogi();
        oknoGry = new OknoGry(plansza, this);
        zapiszListeGatunkow();
        panelGatunki = new PanelGatunki();
    }
    public Swiat(int promien) {
        plansza = new PlanszaHEX(promien, this);
        panelLogi = new PanelLogi();
        oknoGry = new OknoGry(plansza, this);
        zapiszListeGatunkow();
        panelGatunki = new PanelGatunki();
    }

	public void przejdzTure() {
        AktualizujOrganizmy();
        usunMartwe();
        UrodzNoworodki();
        RysujLogi();
        RysujSwiat();
        oknoGry.focus();
    }
	
    public void DodajOrganizmAdmin(Organizm o) {
        if(plansza.getOrg(o.getWsp()) != null) {
            usunOrganizm(plansza.getOrg(o.getWsp()));
        }
        this.DodajOrganizm(o);
    }
	public void DodajOrganizm(Organizm o) {
        if(plansza.czyWPlanszy(o.getWsp()) == false) { return; }
        if(o instanceof Czlowiek) { czlowiek = (Czlowiek) o; }
        organizmyNoworodki.push(o);
    }
	public void usunOrganizm(Organizm o) {
        plansza.UsunOrganizm(o.getWsp());
        o.Zabij();
        if(o instanceof Czlowiek) { czlowiek = null; }
        organizmyMartwe.push(o);
    }
	public void wstawDoPlanszy(Organizm o, Wsp wsp) {
        plansza.WstawOrganizm(o, wsp);
    }
	public void usunZPlanszy(Wsp wsp) {
        plansza.UsunOrganizm(wsp);
    }
	public void Zeznik() {
        UrodzNoworodki();
        for (int i=0; i<organizmy.size(); i++) {
            usunOrganizm(organizmy.get(i));
        }
        usunMartwe();
    }

	public void RysujSwiat() {
        //system("CLS");
        //cout << endl << "Michal Lubinski, 184603" << endl;
        //System.out.print("\nMichal Lubinski, 184603\n");
        plansza.RysujPlansze();
    }
	public void RysujLogi() {
        ((PanelLogi) panelLogi).RysujLogi();
    }
    public void DodajLogWalki(LogWalki log) {
        logiWalki.push(log);
    }

	public boolean czyWPlanszy(Wsp wsp) {
        if (plansza.czyWPlanszy(wsp)) { return true; }
        return false;
    }
	public Wsp losujSasiada(Wsp wsp) { return plansza.losujSasiada(wsp); }
	public Wsp znajdzWolnePole(Wsp wsp) { return plansza.znajdzWolnePole(wsp); }
	public Wsp rotacjaSasiadow(Wsp wsp, Wsp n_wsp) { return plansza.rotacjaSasiadow(wsp, n_wsp); }

	public int getSzerokosc() { return plansza.getSzerokosc(); }
	public int getWysokosc() { return plansza.getWysokosc(); }
	public Organizm getOrg(Wsp wsp) { return plansza.getOrg(wsp); }
	public int getLiczbeSasiadow() { return plansza.getLiczbeSasiadow(); }
    public OknoGry getOknoGry() { return oknoGry; }
    public Component getPanelLogi() { return panelLogi; }
    public Component getPanelGatunki() {return panelGatunki; }
    public Wsp znajdzNajblizszyGatunek(Wsp wsp, Organizm o) { return plansza.znajdzNajblizszyGatunek(wsp, o); }
    public void wstawNaPozycji(int x, int y) {
        wstawGatunekWsp.x = x;
        wstawGatunekWsp.y = y;
        oknoGry.pokazGatunki();
    }
    public void wstawNaPozycji2(int i) {
        Organizm tmp = gatunki.get(i);
        tmp.dajPotomka(wstawGatunekWsp);
        oknoGry.pokazMenu();
        przejdzTure();
    }

	public void Zapisz() throws IOException {
            FileWriter writer = new FileWriter("zapis.txt");
            String s = "";
            s += plansza.getSzerokosc(); s += "\n";
            s += plansza.getWysokosc(); s += "\n";
            writer.write(s);
            for(int i=0 ; i<organizmy.size() ; i++) {
                s = "";
                Organizm tmp = organizmy.get(i);
                if (tmp.getZ() == false) { continue; }
                s += tmp.getChar();
                s += "\n";
                s += tmp.getX(); s += "\n"; s += tmp.getY();
                s += "\n"; s += tmp.getBuff(); s += "\n";
                writer.write(s);
            }
            DodajLogWalki(new LogWalki(0, 0, "ZAPISANO", "", ""));
            writer.close();
            oknoGry.focus();
    }
    public void Zaladuj() throws IOException {
        Zeznik();
        Scanner scanner = new Scanner(new File("zapis.txt"));
        int szerokosc, wysokosc;
        szerokosc = scanner.nextInt();
        wysokosc = scanner.nextInt();
        int x, y, b;
        char c;
        String s = "";
        Wsp wsp = new Wsp();
        Organizm tmp2;
        while(scanner.hasNext()) {
            s = scanner.nextLine();
            s = scanner.nextLine();
            c = s.charAt(0);
            x = scanner.nextInt();
            y = scanner.nextInt();
            b = scanner.nextInt();
            wsp.x = x; wsp.y = y;
            for (int i=0; i<gatunki.size() ; i++) { 
                Organizm tmp = gatunki.get(i);
                if(tmp.getChar() == c) {
                    tmp2 = tmp.dajPotomka(wsp);
                    tmp2.dodajBuff(b);
                    this.DodajOrganizm(tmp2);
                }
            }
        }
        DodajLogWalki(new LogWalki(0, 0, "ZALADOWANO", "", ""));
        this.przejdzTure();
    }
    public void wyslijInputDoCzlowieka(int input) {
        if(czlowiek == null) { return; }
        czlowiek.ustawInput(input);
    }

    public class PanelLogi extends JPanel{
        private JLabel panel[];
        public PanelLogi() {
            this.setLayout(new GridLayout(LICZBA_LOGOW, 1));
            this.setPreferredSize(new Dimension(400, 500));
            panel = new JLabel[LICZBA_LOGOW];
            //String s = "";
            for(int i=0; i<LICZBA_LOGOW; i++) {
                //s+=j; s+=wysokosc-i-1;
                panel[i] = new JLabel();
                panel[i].setText("");
                if((i)%2 == 0) { panel[i].setBackground(Color.LIGHT_GRAY); }
                else { panel[i].setBackground(Color.DARK_GRAY); }
                add(panel[i]);
                //s="";
            }
        }
        public void RysujLogi() {
            for(int i=0;i<LICZBA_LOGOW;i++) {
                panel[i].setText("");
            }
            LogWalki log;
            int i = 0;
            String s;
            while (logiWalki.empty() != true) {
                log = logiWalki.peek();
                if (i < LICZBA_LOGOW) {
                    //cout << "na polu " << log.getX() << ", " << log.getY() << " " << log.getOrg1() << " " << log.getCoZrobil() << " " << log.getOrg2() << endl;
                    s = "  ";
                    s += "na polu ";
                    s += log.getX();
                    s += ", ";
                    s += log.getY();
                    s += " ";
                    s += log.getOrg1();
                    s += " ";
                    s += log.getCoZrobil();
                    s += " ";
                    s += log.getOrg2();
                    panel[i].setText(s);
                }
                logiWalki.pop();
                i++;
            }
            this.revalidate();
            this.repaint();
        }
    }
    public class PanelGatunki extends JPanel{
        private JButton panel[];
        private Action panelAkcji[];

        public PanelGatunki() {
            this.setLayout(new GridLayout(gatunki.size(), 1));
            this.setPreferredSize(new Dimension(400, 500));
            panel = new JButton[gatunki.size()];
            panelAkcji = new PrzyciskGatunku[gatunki.size()];
            for(int i=0; i<gatunki.size(); i++) {
                Organizm tmp = gatunki.get(i);
                String s = "src/";
                s = s + tmp.getNazwa();
                s = s + ".png";
                ImageIcon icon = new ImageIcon(driver.class.getResource(s));
                Image img = icon.getImage();
                Image newimg = img.getScaledInstance(26,26, java.awt.Image.SCALE_SMOOTH);
                icon = new ImageIcon(newimg);
                panelAkcji[i] = new PrzyciskGatunku(i);
                panel[i] = new JButton();
                panel[i].setAction(panelAkcji[i]);
                panel[i].setIcon(icon);
                add(panel[i]);
            }
        }

        public class PrzyciskGatunku extends AbstractAction{
            private int i;
            PrzyciskGatunku(int ii) { super(); i = ii; }
            public void actionPerformed(ActionEvent e) {
                Object source = e.getSource();
                wstawNaPozycji2(i);
            }
        }
    }
}
