package gra;
import gra.resources.backend.Swiat;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.IOException;
import java.awt.event.ActionEvent;


public class OknoGry extends JFrame implements KeyListener{
    protected int szerokoscPlanszy=0;
    protected int wysokoscPlanszy=0;
    private Plansza plansza;
    private Swiat swiat;
    private JPanel panelMenu;


    public OknoGry(Plansza planszaW, Swiat swiatw) {
        super("Michal Lubinski, 184603");
        plansza = planszaW;
        swiat = swiatw;
        panelMenu = new PanelMenu();
        szerokoscPlanszy = plansza.getWysokosc();
        wysokoscPlanszy = plansza.getSzerokosc();

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300, 100);
 		setLocation(2500,50);
        setLayout(new BorderLayout());
        
        JPanel prawaKolumna = new JPanel();
        prawaKolumna.setLayout(new GridLayout(2, 1));
        prawaKolumna.setPreferredSize(new Dimension(400, 700));
        prawaKolumna.setBackground(Color.LIGHT_GRAY);
        prawaKolumna.add(panelMenu);
        prawaKolumna.add(swiat.getPanelLogi());

        add(prawaKolumna, BorderLayout.LINE_END);
        add(plansza.getJPanel(), BorderLayout.LINE_START);
        addKeyListener(this);

        pack();
 		setVisible(true);
        setFocusable(true);
    }

    public void pokazGatunki() {
        getContentPane().removeAll();
        add(plansza.getJPanel(), BorderLayout.LINE_START);
        JPanel prawaKolumna = new JPanel();
        prawaKolumna.setLayout(new GridLayout(2, 1));
        prawaKolumna.setPreferredSize(new Dimension(400, 700));
        prawaKolumna.setBackground(Color.LIGHT_GRAY);
        prawaKolumna.add(swiat.getPanelGatunki());
        add(prawaKolumna, BorderLayout.LINE_END);
        revalidate();
        repaint();
    }
    public void pokazMenu() {
        getContentPane().removeAll();
        add(plansza.getJPanel(), BorderLayout.LINE_START);
        JPanel prawaKolumna = new JPanel();
        prawaKolumna.setLayout(new GridLayout(2, 1));
        prawaKolumna.setPreferredSize(new Dimension(400, 700));
        prawaKolumna.setBackground(Color.LIGHT_GRAY);
        prawaKolumna.add(panelMenu);
        prawaKolumna.add(swiat.getPanelLogi());
        add(prawaKolumna, BorderLayout.LINE_END);
        revalidate();
        repaint();
    }
    public void focus() { requestFocus(); }


        
    @Override
    public void keyPressed(KeyEvent e) {
        swiat.wyslijInputDoCzlowieka((int)e.getKeyCode());
        swiat.przejdzTure();
    }
    @Override
    public void keyReleased(KeyEvent e) {}
    @Override
    public void keyTyped(KeyEvent e) {}

    public class PanelMenu extends JPanel{
        private Action turaB;
        private Action zapiszB;
        private Action zaladujB;

        PanelMenu() {
            this.setPreferredSize(new Dimension(400, 300));
            turaB    = new TuraB("przejdz ture");
            zapiszB  = new ZapiszB("zapisz gre");
            zaladujB = new ZaladujB("zaladuj zapis");

            JButton b1 = new JButton("przejdz ture");
            JButton b2 = new JButton("zapisz");
            JButton b3 = new JButton("zapisz");
            b1.setAction(turaB);
            b2.setAction(zapiszB);
            b3.setAction(zaladujB);
            add(b1);
            add(b2);
            add(b3);
            setBackground(Color.LIGHT_GRAY);
        }

        public class TuraB extends AbstractAction{
            TuraB(String s) { super(s); }
            public void actionPerformed(ActionEvent e) { swiat.przejdzTure(); }
        }
        public class ZapiszB extends AbstractAction{
            ZapiszB(String s) { super(s); }
            public void actionPerformed(ActionEvent e) {
                try { swiat.Zapisz(); }
                catch (IOException e1) { e1.printStackTrace(); }
            }
        }
        public class ZaladujB extends AbstractAction{
            ZaladujB(String s) { super(s); }
            public void actionPerformed(ActionEvent e) {
                try { swiat.Zaladuj(); }
                catch (IOException e1) { e1.printStackTrace(); }
            }
        }
    }
}
