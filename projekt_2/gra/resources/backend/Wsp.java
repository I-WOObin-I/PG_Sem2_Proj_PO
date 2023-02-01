package gra.resources.backend;

public class Wsp {
    public int x = 0;
    public int y = 0;
    public Wsp(int x, int y) { this.x = x; this.y = y; }
    public Wsp() { this.x = 0; this.y = 0; }
    public Wsp(Wsp wsp) { this.x = wsp.x; this.y = wsp.y; }
}
