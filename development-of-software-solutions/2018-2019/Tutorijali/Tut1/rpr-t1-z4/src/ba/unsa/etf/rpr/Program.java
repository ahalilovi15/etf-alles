package ba.unsa.etf.rpr;

import java.util.Scanner;

public class Program {
    private Predmet[] predmeti = null;
    private Student[] studenti = null;
    public Predmet[] getPredmeti() {
        return predmeti;
    }

    public void setPredmeti(Predmet[] predmeti) {
        this.predmeti = predmeti;
    }

    public Student[] getStudenti() {
        return studenti;
    }

    public void setStudenti(Student[] studenti) {
        this.studenti = studenti;
    }

    public Boolean ProvjeriPodatkePredmeta(String nazivPredmeta, Integer sifraPredmeta, int maxBrojStudenata){
        if(nazivPredmeta == null || nazivPredmeta.isEmpty()){
            System.out.println("Niste unijeli naziv predmeta!");
            return false;
        }
        if(predmeti == null || predmeti.length == 0) return true;
        for(Predmet p : predmeti) {
            if (p.getNazivPredmeta().equalsIgnoreCase(nazivPredmeta)) {
                System.out.println("Predmet vec postoji!");
                return false;
            } else if (p.getSifraPredmeta().equals(sifraPredmeta)) {
                System.out.println("Poklapanje sifre predmeta!");
                return false;
            }
        }
        if(maxBrojStudenata == 0){
            System.out.println("Maximalan broj studenata na predmetu ne moze biti nula!");
            return false;
        }
        return true;
    }
    public Boolean ProvjeriPodatkeStudenta(String prezime, String ime, Integer brojIndexa){
        if(prezime == null || prezime.isEmpty()){
            System.out.println("Niste unijeli prezime studenta!");
            return false;
        }
        if(ime == null || ime.isEmpty()){
            System.out.println("Niste unijeli ime studenta!");
            return false;
        }
        if(studenti == null || studenti.length == 0)
            return true;
        for(Student s : studenti)
            if(s.getBrojIndexa().equals(brojIndexa)){
                System.out.println("Poklapanje broja indexa!");
                return false;
            }
        return true;
    }
    public Boolean ImaPredmet(String nazivPredmeta){
        if(predmeti == null || predmeti.length == 0) return false;
        for(Predmet p : predmeti)
            if(p.getNazivPredmeta().equalsIgnoreCase(nazivPredmeta)){
                return true;
            }
            return false;
    }
    public Boolean ImaStudent(Integer brojIndexa){
        if(studenti == null || studenti.length == 0) return false;
        for(Student s : studenti)
            if(s.getBrojIndexa().equals(brojIndexa)) return true;
        return false;
    }

    public void KreirajPredmet (String nazivPredmeta, Integer sifraPredmeta, int maxBrojStudenata){
        if(!ProvjeriPodatkePredmeta(nazivPredmeta, sifraPredmeta, maxBrojStudenata)) return;
        if(predmeti == null || predmeti.length == 0){
            predmeti = new Predmet[1];
            predmeti[0] = new Predmet(nazivPredmeta, sifraPredmeta, maxBrojStudenata);
            return;
        }
        Predmet[] novi = new Predmet[predmeti.length + 1];
        for(int i = 0; i < predmeti.length; i++)
            novi[i] = predmeti[i];
        novi[predmeti.length] = new Predmet(nazivPredmeta, sifraPredmeta, maxBrojStudenata);
        predmeti = novi;
    }
    public void DodajStudenta(String prezime, String ime, Integer brojIndexa){
        if(!ProvjeriPodatkeStudenta(prezime, ime, brojIndexa)) return;
        if(studenti == null || studenti.length == 0){
            studenti = new Student[1];
            studenti[0] = new Student(ime, prezime, brojIndexa);
            return;
        }
        Student[] novi = new Student[studenti.length + 1];
        for(int i = 0; i < studenti.length; i++)
            novi[i] = studenti[i];
        novi[studenti.length] = new Student(ime, prezime, brojIndexa);
        studenti = novi;
    }
    public void UpisiStudentaNaPredmet(Integer brojIndexa, String nazivPredmeta){
        if(!ImaStudent(brojIndexa)){
            System.out.println("Student nije nadjen!");
            return;
        }
        for(Student s : studenti)
            if(s.getBrojIndexa().equals(brojIndexa)) {
                if(predmeti == null || predmeti.length == 0) {
                    System.out.println("Nema kreiranih predmeta!");
                    break;
                }
                else
                    for (Predmet p : predmeti)
                        if (p.getNazivPredmeta().equalsIgnoreCase(nazivPredmeta)) {
                            p.Upisi(s);
                            return;
                        }
            }
    }
    public void IspisiStudentaSaPredmeta(Integer brojIndexa, String nazivPredmeta){
        if(!ImaStudent(brojIndexa)){
            System.out.println("Student nije nadjen!");
            return;
        }
        for(Student s : studenti)
            if(s.getBrojIndexa().equals(brojIndexa)) {
                if(predmeti == null || predmeti.length == 0) {
                    System.out.println("Nema kreiranih predmeta!");
                    return;
                }
                else
                    for (Predmet p : predmeti)
                        if (p.getNazivPredmeta().equalsIgnoreCase(nazivPredmeta)) {
                            p.Ispisi(s);
                            return;
                        }
            }
    }
    public void ObrisiStudenta(Integer brojIndexa){
        if(!ImaStudent(brojIndexa)){
            System.out.println("Student nije nadjen!");
            return;
        }
        for(Student s : studenti)
            if(s.getBrojIndexa().equals(brojIndexa))
                for(Predmet p : predmeti)
                    if(p.Upisan(s)) p.Ispisi(s);
        Student[] novi = new Student[studenti.length - 1];
        int j = 0;
        for(int i = 0; i < novi.length; i++){
            if(!studenti[j].getBrojIndexa().equals(brojIndexa)){
                novi[i] = studenti[j];
                j++;
            }
            else {
                j++;
                novi[i] = studenti[j];
                j++;
            }
        }
        studenti = novi;
    }
    public void ObrisiPredmet(String nazivPredmeta){
        if(!ImaPredmet(nazivPredmeta)){
            System.out.println("Predmet nije nadjen!");
            return;
        }
        Predmet[] novi = new Predmet[predmeti.length - 1];
        int j = 0;
        for(int i = 0; i < novi.length; i++){
            if(!predmeti[j].getNazivPredmeta().equalsIgnoreCase(nazivPredmeta)){
                novi[i] = predmeti[j];
                j++;
            }
            else j++;
        }
        predmeti = novi;
    }
    public void IspisiSpisakStudenata(String nazivPredmeta){
        for(Predmet p : predmeti)
            if(p.getNazivPredmeta().equalsIgnoreCase(nazivPredmeta)){
                System.out.println(p);
                return;
            }
    }
    public void DodavanjeStudenta(){
        try{
            System.out.println("Unesite prezime");
            Scanner scanner = new Scanner(System.in);
            String prezime = scanner.nextLine();
            System.out.println("Unesite ime");
            scanner = new Scanner(System.in);
            String ime = scanner.nextLine();
            System.out.println("Unesite brojIndexa");
            scanner = new Scanner(System.in);
            Integer brojIndexa = scanner.nextInt();
            DodajStudenta(prezime, ime, brojIndexa);
        } catch(Exception e){
            System.out.println(e.toString());
        }
    }
    public void KreiranjePredmeta(){
        try{
            System.out.println("Unesite naziv predmeta");
            Scanner scanner = new Scanner(System.in);
            String nazivPredmeta = scanner.nextLine();
            System.out.println("Unesite sifru predmeta");
            scanner = new Scanner(System.in);
            Integer sifraPredmeta = scanner.nextInt();
            System.out.println("Unesite maximalan broj studenata na predmetu");
            scanner = new Scanner(System.in);
            int maxBrojStudenata = scanner.nextInt();
            KreirajPredmet(nazivPredmeta, sifraPredmeta, maxBrojStudenata);
        } catch (Exception e){
            System.out.println(e.toString());
        }
    }
    public void UpisStudentaNaPredmet(){
        try{
            System.out.println("Unesite index studenta");
            Scanner scanner = new Scanner(System.in);
            Integer brojIndexa = scanner.nextInt();
            System.out.println("Unesite naziv predmeta");
            scanner = new Scanner(System.in);
            String nazivPredmeta = scanner.nextLine();
            UpisiStudentaNaPredmet(brojIndexa, nazivPredmeta);
        } catch (Exception e){
            System.out.println(e.toString());
        }
    }
    public void IspisStudentaSaPredmeta(){
        try{
            System.out.println("Unesite index studenta");
            Scanner scanner = new Scanner(System.in);
            Integer brojIndexa = scanner.nextInt();
            System.out.println("Unesite naziv predmeta");
            scanner = new Scanner(System.in);
            String nazivPredmeta = scanner.nextLine();
            IspisiStudentaSaPredmeta(brojIndexa, nazivPredmeta);
        } catch (Exception e){
            System.out.println(e.toString());
        }
    }
    public void BrisanjeStudenta(){
        try{
            System.out.println("Unesite index studenta");
            Scanner scanner = new Scanner(System.in);
            Integer brojIndexa = scanner.nextInt();
            ObrisiStudenta(brojIndexa);
        } catch (Exception e){
            System.out.println(e.toString());
        }
    }
    public void BrisanjePredmeta(){
        try{
            System.out.println("Unesite naziv predmeta");
            Scanner scanner = new Scanner(System.in);
            String nazivPredmeta = scanner.nextLine();
            ObrisiPredmet(nazivPredmeta);
        } catch (Exception e){
            System.out.println(e.toString());
        }
    }
    public void Ispis(){
        try{
            System.out.println("Unesite naziv premeta");
            Scanner scanner = new Scanner(System.in);
            String nazivPredmeta = scanner.nextLine();
            IspisiSpisakStudenata(nazivPredmeta);
        } catch (Exception e){
            System.out.println(e.toString());
        }
    }

    public static void main(String[] args) {
        Program program = new Program();
        program.DodajStudenta("Krdzic", "Nermin", 17825);
        program.DodajStudenta("Masovic", "Haris", 17696);
        program.DodajStudenta("xxxxx", "Faris", 17777);
        program.KreirajPredmet("MLTI", 1, 1);
        program.KreirajPredmet("RPR", 2, 2);
        int izbor = 1;
        while(izbor != 0){
            System.out.println("Unesite:");
            System.out.println("1. za, Dodavanje studenta");
            System.out.println("2. za, Kreiranje predmeta");
            System.out.println("3. za, Upis studenta na predmet");
            System.out.println("4. za, Ispis studenta sa predmeta");
            System.out.println("5. za, Brisanje studenta");
            System.out.println("6. za, Brisanje predmeta");
            System.out.println("7. za, Ispis spiska studenata sa navedenog predmeta");
            System.out.println("0. za, Izlaz iz aplikacije.");
            Scanner scanner = new Scanner(System.in);
            izbor = scanner.nextInt();
            switch (izbor){
                case 0:
                    return;
                case 1:
                    program.DodavanjeStudenta();
                    break;
                case 2:
                    program.KreiranjePredmeta();
                    break;
                case 3:
                    program.UpisStudentaNaPredmet();
                    break;
                case 4:
                    program.IspisStudentaSaPredmeta();
                    break;
                case 5:
                    program.BrisanjeStudenta();
                    break;
                case 6:
                    program.BrisanjePredmeta();
                    break;
                case 7:
                    program.Ispis();
                    break;
            }
        }
    }
}
