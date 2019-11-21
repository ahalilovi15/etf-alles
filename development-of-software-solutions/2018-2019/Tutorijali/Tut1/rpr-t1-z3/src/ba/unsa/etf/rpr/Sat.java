
package ba.unsa.etf.rpr;

import java.io.PrintStream;

public class Sat {
    int sati;
    int minute;
    int sekunde;

    Sat(int sati, int minute, int sekunde) {
        this.Postavi(sati, minute, sekunde);
    }

    public void Postavi(int sati, int minute, int sekunde) {
        this.sati = sati;
        this.minute = minute;
        this.sekunde = sekunde;
    }

    public void Sljedeci() {
        ++this.sekunde;
        if (this.sekunde == 60) {
            this.sekunde = 0;
            ++this.minute;
        }

        if (this.minute == 60) {
            this.minute = 0;
            ++this.sati;
        }

        if (this.sati == 24) {
            this.sati = 0;
        }

    }

    public void Prethodni() {
        --this.sekunde;
        if (this.sekunde == -1) {
            this.sekunde = 59;
            --this.minute;
        }

        if (this.minute == -1) {
            this.minute = 59;
            --this.sati;
        }

        if (this.sati == -1) {
            this.sati = 23;
        }

    }

    void PomjeriZa(int pomak) {
        int i;
        if (pomak > 0) {
            for(i = 0; i < pomak; ++i) {
                this.Sljedeci();
            }
        } else {
            for(i = 0; i < -pomak; ++i) {
                this.Prethodni();
            }
        }

    }

    public final int DajSate() {
        return this.sati;
    }

    public final int DajMinute() {
        return this.minute;
    }

    public final int DajSekunde() {
        return this.sekunde;
    }

    public final void Ispisi() {
        System.out.println(Integer.toString(this.sati) + ":" + Integer.toString(this.minute) + ":" + Integer.toString(this.sekunde));
    }
}
