package ba.unsa.etf.rpr;

import static org.junit.jupiter.api.Assertions.*;

class PredmetTest {

    @org.junit.jupiter.api.Test
    public void upisan() {
        Predmet predmet = new Predmet("RPR", 1, 2);
        Student student = new Student("Nermin", "Krdzic", 17825);
        assertEquals(false, predmet.Upisan(student));
        predmet.Upisi(student);
        assertEquals(true, predmet.Upisan(student));
    }

    @org.junit.jupiter.api.Test
    void upisi() {
        Predmet predmet = new Predmet("RPR", 1, 2);
        Student student = new Student("Nermin", "Krdzic", 17825);
        predmet.Upisi(student);
        assertEquals(true, predmet.Upisan(student));
    }

    @org.junit.jupiter.api.Test
    void ispisi() {
        Predmet predmet = new Predmet("RPR", 1, 2);
        Student student = new Student("Nermin", "Krdzic", 17825);
        predmet.Upisi(student);
        predmet.Upisi(new Student("Masovic", "Haris", 17696));
        predmet.Upisi(new Student("xxxxx", "Faris", 17777));
        assertEquals(2, predmet.getStudenti().length);
        predmet.Ispisi(student);
        assertEquals(1, predmet.getStudenti().length);
    }

    @org.junit.jupiter.api.Test
    void _toString() {
        Predmet predmet = new Predmet("RPR", 1, 3);
        predmet.Upisi(new Student("Nermin", "Krdzic", 17825));
        predmet.Upisi(new Student("Haris", "Masovic", 17696));
        predmet.Upisi(new Student("Faris", "xxxxx", 17777));
        assertEquals("1. Krdzic Nermin (17825)\n2. Masovic Haris (17696)\n3. xxxxx Faris (17777)\n", predmet.toString());
    }
}