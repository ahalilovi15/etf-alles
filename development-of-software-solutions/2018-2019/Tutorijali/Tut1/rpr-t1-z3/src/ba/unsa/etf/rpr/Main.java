package ba.unsa.etf.rpr;

public class Main {

    public static void main(String[] args) {
        Sat s = new Sat(15, 30, 45);
        s.Ispisi();
        s.Sljedeci();
        s.Ispisi();
        s.PomjeriZa(-48);
        s.Ispisi();
        s.Postavi(0, 0, 0);
        s.Ispisi();
    }
}
