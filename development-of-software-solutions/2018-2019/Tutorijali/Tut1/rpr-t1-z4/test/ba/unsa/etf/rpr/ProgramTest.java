package ba.unsa.etf.rpr;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class ProgramTest {

    @Test
    void provjeriPodatkePredmeta() {
        Program program = new Program();
        assertEquals(true, program.ProvjeriPodatkePredmeta("MLTI", 1, 1));
        program.KreirajPredmet("MLTI", 1, 1);
        assertEquals(false, program.ProvjeriPodatkePredmeta("MLTI", 1, 1));
        assertEquals(false, program.ProvjeriPodatkePredmeta(null, 1,1));
        assertEquals(false, program.ProvjeriPodatkePredmeta("RPR", 1,1));
        assertEquals(false, program.ProvjeriPodatkePredmeta("RPR", 2,0));
        assertEquals(true, program.ProvjeriPodatkePredmeta("RPR", 2, 2));
    }

    @Test
    void provjeriPodatkeStudenta() {
        Program program = new Program();
        assertEquals(false, program.ProvjeriPodatkeStudenta(null, "nermin", 17825));
        assertEquals(false, program.ProvjeriPodatkeStudenta("Krdzic", "", 17825));
        assertEquals(true, program.ProvjeriPodatkeStudenta("Krdzic", "Nermin", 17825));
        program.DodajStudenta("Krdzic", "Nermin", 17825);
        assertEquals(false, program.ProvjeriPodatkeStudenta("Hasic", "Hasan", 17825));
        assertEquals(true, program.ProvjeriPodatkeStudenta("Krdzic", "nermin", 17826));


    }

    @Test
    void imaPredmet() {
        Program program = new Program();
        assertEquals(false, program.ImaPredmet("awkward"));
        program.KreirajPredmet("awkward", 1, 2);
        assertEquals(true, program.ImaPredmet("awkward"));
        assertEquals(true, program.ImaPredmet("Awkward"));
    }

    @Test
    void imaStudent() {
        Program program = new Program();
        assertEquals(false, program.ImaStudent(17665));
        program.DodajStudenta("Hasic", "Hasan", 17999);
        assertEquals(true, program.ImaStudent(17999));
    }

    @Test
    void kreirajPredmet() {
        // ova metoda je provjerena metodom ImaPredmet()
    }

    @Test
    void dodajStudenta() {
        //Ova metoda je provjerena metodom ImaStudent()
    }

    @Test
    void upisiStudentaNaPredmet() {
        Program program = new Program();
        program.DodajStudenta("Krdzic", "Nermin", 17825);
        program.DodajStudenta("Masovic", "Haris", 17696);
        program.DodajStudenta("xxxxx", "Faris", 17777);
        program.KreirajPredmet("MLTI", 1, 2);
        Student student1 = program.getStudenti()[0];
        Student student2 = program.getStudenti()[1];
        Student student3 = program.getStudenti()[2];
        Predmet predmet = program.getPredmeti()[0];
        assertEquals(false, predmet.Upisan(student1));
        program.UpisiStudentaNaPredmet(17825, "");
        assertEquals(false, predmet.Upisan(student1));
        program.UpisiStudentaNaPredmet(17825, "mlti");
        assertEquals(true, predmet.Upisan(student1));
        program.UpisiStudentaNaPredmet(17696, "mlti");
        assertEquals(true, predmet.Upisan(student2));
        program.UpisiStudentaNaPredmet(17777, "mlti");
        assertEquals(false, predmet.Upisan(student3));
    }

    @Test
    void ispisiStudentaSaPredmeta() {
        Program program = new Program();
        program.DodajStudenta("Krdzic", "Nermin", 17825);
        program.DodajStudenta("Masovic", "Haris", 17696);
        program.KreirajPredmet("MLTI", 1, 2);
        Student student1 = program.getStudenti()[0];
        Student student2 = program.getStudenti()[1];
        Predmet predmet = program.getPredmeti()[0];
        program.UpisiStudentaNaPredmet(17825, "mlti");
        assertEquals(true, predmet.Upisan(student1));
        program.UpisiStudentaNaPredmet(17696, "mlti");
        assertEquals(true, predmet.Upisan(student2));
        program.IspisiStudentaSaPredmeta(17825, "mlti");
        assertEquals(false, predmet.Upisan(student1));
        assertEquals(true, predmet.Upisan(student2));
        program.IspisiStudentaSaPredmeta(17696, "mlti");
        assertEquals(false, predmet.Upisan(student2));

    }

    @Test
    void obrisiStudenta() {
        Program program = new Program();
        program.DodajStudenta("Krdzic", "Nermin", 17825);
        program.DodajStudenta("Masovic", "Haris", 17696);
        program.KreirajPredmet("MLTI", 1, 2);
        Student student1 = program.getStudenti()[0];
        Student student2 = program.getStudenti()[1];
        Predmet predmet = program.getPredmeti()[0];
        program.UpisiStudentaNaPredmet(17825, "mlti");
        assertEquals(true, predmet.Upisan(student1));
        program.UpisiStudentaNaPredmet(17696, "mlti");
        assertEquals(true, predmet.Upisan(student2));
        program.ObrisiStudenta(17825);
        assertEquals(false, program.ImaStudent(17825));
    }

    @Test
    void obrisiPredmet() {
        Program program = new Program();
        program.KreirajPredmet("mlti", 1, 1);
        assertEquals(true, program.ImaPredmet("mlti"));
        program.ObrisiPredmet("Mlti");
        assertEquals(false, program.ImaPredmet("mLti"));
    }

    @Test
    void ispisiSpisakStudenata() {
        // provjereno u klasi PredmetTest u funkciji toString()
    }
}