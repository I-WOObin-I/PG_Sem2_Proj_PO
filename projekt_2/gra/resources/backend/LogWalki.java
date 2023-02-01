package gra.resources.backend;

public class LogWalki {
    private int x;
	private int y;
	private String nazwa1;
	private String nazwa2;
	private String coZrobil;

    public LogWalki(int x, int y, String n1, String n2, String coZ) {
        this.x = x;
        this.y = y;
        this.nazwa1 = n1;
        this.nazwa2 = n2;
        this.coZrobil = coZ;
    }
    public int getX() { return x; }
    public int getY() { return y; }
    public String getOrg1() { return nazwa1; }
    public String getOrg2() { return nazwa2; }
    public String getCoZrobil() { return coZrobil; }
}
