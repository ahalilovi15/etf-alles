package ba.unsa.etf.rpr.tutorijal02;

public class Interval {
    private double pocetnaTacka;
    private double krajnjaTacka;
    private boolean pocetnaPripada;
    private boolean krajnjaPripada;

    public double getPocetnaTacka() {
        return pocetnaTacka;
    }

    public void setPocetnaTacka(double pocetnaTacka) {
        this.pocetnaTacka = pocetnaTacka;
    }

    public double getKrajnjaTacka() {
        return krajnjaTacka;
    }

    public void setKrajnjaTacka(double krajnjaTacka) {
        this.krajnjaTacka = krajnjaTacka;
    }

    public boolean isPocetnaPripada() {
        return pocetnaPripada;
    }

    public void setPocetnaPripada(boolean pocetnaPripada) {
        this.pocetnaPripada = pocetnaPripada;
    }

    public boolean isKrajnjaPripada() {
        return krajnjaPripada;
    }

    public void setKrajnjaPripada(boolean krajnjaPripada) {
        this.krajnjaPripada = krajnjaPripada;
    }

    public Interval(double pocetnaTacka, double krajnjaTacka, boolean pocetnaPripada, boolean krajnjaPripada) throws IllegalArgumentException{
        if(pocetnaTacka > krajnjaTacka) throw new IllegalArgumentException();
        setPocetnaTacka(pocetnaTacka);
        setKrajnjaTacka(krajnjaTacka);
        setPocetnaPripada(pocetnaPripada);
        setKrajnjaPripada(krajnjaPripada);
    }

    public Interval(){
        setKrajnjaTacka(0);
        setKrajnjaTacka(0);
        setPocetnaPripada(false);
        setKrajnjaPripada(false);
    }

    public boolean isIn(double tacka){
        if((tacka == pocetnaTacka && isPocetnaPripada()) || (tacka == krajnjaTacka && isKrajnjaPripada()) || (tacka > pocetnaTacka && tacka < krajnjaTacka)) return true;
        return false;
    }

    public boolean isNull(){
        if(getPocetnaTacka() == getKrajnjaTacka() && getPocetnaTacka() == 0 && !isPocetnaPripada() && !isKrajnjaPripada()) return true;
        return false;
    }

    public Interval intersect(Interval interval){
        Interval nova = new Interval();
        //setovanje prve tacke
        if(getPocetnaTacka() > interval.getPocetnaTacka()) {
            nova.setPocetnaTacka(getPocetnaTacka());
            nova.setPocetnaPripada(isPocetnaPripada());
        }
        else if(getPocetnaTacka() < interval.getPocetnaTacka()){
           nova.setPocetnaTacka(interval.getPocetnaTacka());
           nova.setPocetnaPripada(interval.isPocetnaPripada());
        }
        if(getPocetnaTacka() == interval.getPocetnaTacka()){
            nova.setPocetnaTacka(getPocetnaTacka());
            if(isPocetnaPripada() && interval.isPocetnaPripada())
                nova.setPocetnaPripada(true);
            else nova.setPocetnaPripada(false);
        }
        //setovanje druge tacke
        if(getKrajnjaTacka() < interval.getKrajnjaTacka()){
            nova.setKrajnjaTacka(getKrajnjaTacka());
            nova.setKrajnjaPripada(isKrajnjaPripada());
        }
        if(getKrajnjaTacka() > interval.getKrajnjaTacka()){
            nova.setKrajnjaTacka(interval.getKrajnjaTacka());
            nova.setKrajnjaPripada(interval.isKrajnjaPripada());
        }
        if(getKrajnjaTacka() == interval.getKrajnjaTacka()){
            nova.setKrajnjaTacka(getKrajnjaTacka());
            if(isKrajnjaPripada() && interval.isKrajnjaPripada())
                nova.setKrajnjaPripada(true);
            else nova.setKrajnjaPripada(false);
        }
        return nova;
    }

    public static Interval intersect(Interval interval1, Interval interval2){
        Interval nova = new Interval();
        //setovanje prve tacke
        if(interval1.getPocetnaTacka() > interval2.getPocetnaTacka()) {
            nova.setPocetnaTacka(interval1.getPocetnaTacka());
            nova.setPocetnaPripada(interval1.isPocetnaPripada());
        }
        else if(interval1.getPocetnaTacka() < interval2.getPocetnaTacka()){
            nova.setPocetnaTacka(interval2.getPocetnaTacka());
            nova.setPocetnaPripada(interval2.isPocetnaPripada());
        }
        if(interval1.getPocetnaTacka() == interval2.getPocetnaTacka()){
            nova.setPocetnaTacka(interval1.getPocetnaTacka());
            if(interval1.isPocetnaPripada() && interval2.isPocetnaPripada())
                nova.setPocetnaPripada(true);
            else nova.setPocetnaPripada(false);
        }
        //setovanje druge tacke
        if(interval1.getKrajnjaTacka() < interval2.getKrajnjaTacka()){
            nova.setKrajnjaTacka(interval1.getKrajnjaTacka());
            nova.setKrajnjaPripada(interval1.isKrajnjaPripada());
        }
        if(interval1.getKrajnjaTacka() > interval2.getKrajnjaTacka()){
            nova.setKrajnjaTacka(interval2.getKrajnjaTacka());
            nova.setKrajnjaPripada(interval2.isKrajnjaPripada());
        }
        if(interval1.getKrajnjaTacka() == interval2.getKrajnjaTacka()){
            nova.setKrajnjaTacka(interval1.getKrajnjaTacka());
            if(interval1.isKrajnjaPripada() && interval2.isKrajnjaPripada())
                nova.setKrajnjaPripada(true);
            else nova.setKrajnjaPripada(false);
        }
        return nova;
    }

    @Override
    public boolean equals(Object obj) {
        Interval interval = (Interval) obj;
        if(getPocetnaTacka() == interval.getPocetnaTacka() && getKrajnjaTacka() == interval.getKrajnjaTacka()
                && isPocetnaPripada() == interval.isPocetnaPripada() && isKrajnjaPripada() == interval.isKrajnjaPripada())
            return true;
        return false;
    }

    @Override
    public String toString() {
        if(getPocetnaTacka() == 0 && getKrajnjaTacka() == 0)
            return "()";
        String string = "";
        if(isPocetnaPripada()) string += "[";
        else string += "(";
        string += Double.toString(pocetnaTacka) + "," + Double.toString(krajnjaTacka);
        if(isKrajnjaPripada()) string += "]";
        else string += ")";
        return string;
    }

}
