#include <iostream>
#include <algorithm>

using namespace std;

template <typename TipKljuca, typename TipVrijednosti>
struct Cvor {
    TipKljuca kljuc;
    TipVrijednosti vrijednost;
    Cvor *lijevi = nullptr;
    Cvor *desni = nullptr;
    Cvor *rod = nullptr;
    int balans = 0;
};

template <typename TipKljuca, typename TipVrijednosti>
class Mapa
{
public:
    Mapa() {}
    virtual ~Mapa() {}
    virtual TipVrijednosti &operator[] (TipKljuca k) =0;
    virtual TipVrijednosti  operator[] (TipKljuca k) const =0;
    virtual void obrisi() =0;
    virtual void obrisi(const TipKljuca &k) =0;
    virtual int brojElemenata() const=0;
};

template <typename TipKljuca, typename TipVrijednosti>
class AVLStabloMapa : public Mapa<TipKljuca, TipVrijednosti>
{
    Cvor<TipKljuca, TipVrijednosti> *korijen;
    int brojEl;
    Cvor<TipKljuca, TipVrijednosti>* &pretragaBST(const TipKljuca &k, Cvor<TipKljuca, TipVrijednosti>* &noviKorjen, Cvor<TipKljuca, TipVrijednosti>* &p) {
        p = noviKorjen;
        while(p != nullptr && k != p->kljuc) {
            if(k < p->kljuc) {
                p = p->lijevi;
            } else  p = p->desni;
        }
        return p;
    }
    Cvor<TipKljuca, TipVrijednosti>* pretragaBST(const TipKljuca &k, Cvor<TipKljuca, TipVrijednosti>* noviKorjen) const {
        while(noviKorjen != nullptr && k != noviKorjen->kljuc) {
            if(k < noviKorjen->kljuc) {
                noviKorjen = noviKorjen->lijevi;
            } else  noviKorjen = noviKorjen->desni;
        }
        return noviKorjen;
    }

    bool brisiCvorBST(const TipKljuca &k, Cvor<TipKljuca, TipVrijednosti>* &noviKorjen) {
        Cvor<TipKljuca, TipVrijednosti>* p = noviKorjen;
        Cvor<TipKljuca, TipVrijednosti>* roditelj = nullptr;

        while(p != nullptr && k != p->kljuc) {
            roditelj = p;
            if(k < p->kljuc) p = p->lijevi;
            else p = p->desni;
        }
        if( p == nullptr) return false;

        Cvor<TipKljuca, TipVrijednosti>* m = nullptr;
        Cvor<TipKljuca, TipVrijednosti>* pm = nullptr;
        Cvor<TipKljuca, TipVrijednosti>* tmp = nullptr;
        if(p->lijevi == nullptr) {
            m = p->desni;
        } else if (p->desni == nullptr) {
            m = p->lijevi;
        } else {
            pm = p;
            m = p->lijevi;
            tmp = m->desni;
            while(tmp != nullptr) {
                pm = m;
                m = tmp;
                tmp = m->desni;
            }
            if(pm != p ) {
                pm->desni = m->lijevi;
                m->lijevi = p->lijevi;
            }
            m->desni = p->desni;
        }
        if(roditelj == nullptr) noviKorjen = m;
        else {
            if(p == roditelj->lijevi) {
                roditelj->lijevi = m;
            } else {
                roditelj->desni = m;
            }
        }
        if(m != nullptr) m->rod = roditelj;
        delete p;
        p = nullptr;
        return true;
    }

    void obrisiSve(Cvor<TipKljuca, TipVrijednosti>* &korje) {
        Cvor<TipKljuca, TipVrijednosti>* noviKorjen = korje;
        if(noviKorjen == nullptr) return;
        obrisiSve(korje->lijevi);
        obrisiSve(korje->desni);
        delete noviKorjen;
    }

    int height(Cvor<TipKljuca,TipVrijednosti>* &pok) {                                                                  //
        if (pok == nullptr) return 0;
        return pok->balans;
    }

    int getBalans(Cvor<TipKljuca,TipVrijednosti>* &pok) {
        if (pok == nullptr) return 0;
        return height(pok->lijevi) - height(pok->desni);
    }

    void kopirajBST(Cvor<TipKljuca, TipVrijednosti>* &prviKorjen, Cvor<TipKljuca, TipVrijednosti>* drugiKorjen) {
        if (drugiKorjen == nullptr) return;

        Cvor<TipKljuca, TipVrijednosti> *p = drugiKorjen;

        prviKorjen = new Cvor<TipKljuca, TipVrijednosti>();
        prviKorjen->kljuc = p->kljuc;
        prviKorjen->vrijednost = p->vrijednost;
        prviKorjen->balans = p->balans;
        prviKorjen->lijevi = nullptr;
        prviKorjen->desni = nullptr;

        kopirajBST(prviKorjen->lijevi, p->lijevi);
        kopirajBST(prviKorjen->desni, p->desni);
        if (prviKorjen->lijevi != nullptr) prviKorjen->lijevi->rod = prviKorjen;
        if (prviKorjen->desni != nullptr) prviKorjen->desni->rod = prviKorjen;
        brojEl++;
    }

    Cvor<TipKljuca, TipVrijednosti>* rightRotate(Cvor<TipKljuca, TipVrijednosti>* &x) {
        Cvor<TipKljuca, TipVrijednosti>* y = x->lijevi;
        Cvor<TipKljuca, TipVrijednosti>* T2 = y->desni;

        y->desni = x;
        x->lijevi = T2;
        y->rod = x->rod;
        if(x != nullptr) x->rod = y;
        if(T2!= nullptr) T2->rod = x;



        //std::cout << "Desila se desna rotacija!" << std::endl;

        x->balans = std::max(height(x->lijevi), height(x->desni));
        y->balans = std::max(height(y->lijevi), height(y->desni));

        if(y->rod == nullptr) {
            korijen = y;
        } else {
            Cvor<TipKljuca, TipVrijednosti>* glavni = y->rod;
            glavni->lijevi = y;
        }

        return y;
    }

    Cvor<TipKljuca, TipVrijednosti>* leftRotate(Cvor<TipKljuca, TipVrijednosti>* &x) {
        Cvor<TipKljuca, TipVrijednosti> *y = x->desni;
        Cvor<TipKljuca, TipVrijednosti> *T2 = y->lijevi;



        y->lijevi = x;
        x->desni = T2;
        y->rod = x->rod;
        if (x != nullptr) x->rod = y;
        if (T2 != nullptr) T2->rod = x;


        x->balans = std::max(height(x->lijevi), height(x->desni));
        y->balans = std::max(height(y->lijevi), height(y->desni));

        if (y->rod == nullptr) {
            korijen = y;
        } else {
            Cvor<TipKljuca, TipVrijednosti> *glavni = y->rod;
            glavni->desni = y;
        }

        return x;
    }



    void azurirajStabloDodavanje(Cvor<TipKljuca, TipVrijednosti>* &cvor, Cvor<TipKljuca, TipVrijednosti>* &roditelj) {
        Cvor<TipKljuca, TipVrijednosti>* x = cvor;
        if(x == nullptr) return;
        if(roditelj == nullptr) return;
        Cvor<TipKljuca, TipVrijednosti>* z = roditelj;
        if(x == z->lijevi) {
            z->balans++;
        } else z->balans--;

        bool desiloSe = false;
        int balance = getBalans(x);
        if (balance > 1 && z->kljuc < z->lijevi->kljuc) {
            desiloSe = true;
            rightRotate(z);
        }
        if (balance < -1 && z->kljuc > z->desni->kljuc) {
            desiloSe = true;
            leftRotate(z);
        }
        if (balance > 1 && z->kljuc > z->lijevi->kljuc) {
            desiloSe = true;
            z->lijevi = leftRotate(z->lijevi);
            rightRotate(z);
        }
        if (balance < -1 && z->kljuc < z->desni->kljuc) {
            desiloSe = true;
            z->desni = rightRotate(z->desni);
            leftRotate(z);
        }

        if(!desiloSe) azurirajStabloDodavanje(z, z->rod);
    }


    void umetniBST(Cvor<TipKljuca, TipVrijednosti>* &prviKorjen, Cvor<TipKljuca, TipVrijednosti>* &cvorN) {
        Cvor<TipKljuca, TipVrijednosti>* y = nullptr;
        Cvor<TipKljuca, TipVrijednosti>* x = prviKorjen;
        while(x != nullptr) {
            y = x;
            if(cvorN->kljuc < x->kljuc)x = x->lijevi;
            else x = x->desni;
        }

        if(y == nullptr) prviKorjen = cvorN;
        else {
            if(cvorN->kljuc < y->kljuc) y->lijevi = cvorN;
            else y->desni = cvorN;
        }
        cvorN->rod = y;

        if(y != nullptr && y->lijevi != nullptr && y->desni != nullptr) {
            y->balans = 0;
        } else azurirajStabloDodavanje(x, y);
    }

public:
    AVLStabloMapa() {
        korijen=nullptr;
        brojEl=0;
    }
    AVLStabloMapa(const AVLStabloMapa<TipKljuca, TipVrijednosti> &b ) : korijen(nullptr), brojEl(0) {
        kopirajBST(korijen, b.korijen);
    }
    AVLStabloMapa<TipKljuca, TipVrijednosti> &operator=(const AVLStabloMapa<TipKljuca, TipVrijednosti> &b) {
        if (this==&b) return *this;
        obrisiSve(korijen);
        brojEl = 0;
        korijen = nullptr;
        kopirajBST(korijen, b.korijen);
        return *this;
    }
    ~AVLStabloMapa() {
        obrisiSve(korijen);
        korijen = nullptr;
        brojEl = 0;
    }
    TipVrijednosti &operator[] (TipKljuca k) {
        Cvor<TipKljuca, TipVrijednosti> *pomoc = pretragaBST(k, korijen);
        if(pomoc == nullptr) {
            pomoc = new Cvor<TipKljuca, TipVrijednosti>();
            pomoc->kljuc = k;
            pomoc->lijevi = nullptr;
            pomoc->desni = nullptr;
            pomoc->balans = 0;
            pomoc->vrijednost = TipVrijednosti();
            umetniBST(korijen, pomoc);
            brojEl++;
        }
        return pomoc->vrijednost;
    }
    TipVrijednosti  operator[] (TipKljuca k) const {
        Cvor<TipKljuca, TipVrijednosti> *pomoc = pretragaBST(k, korijen);
        if (pomoc == nullptr) return TipVrijednosti();
        else return pomoc->vrijednost;
    }
    void obrisi() {
        obrisiSve(korijen);
        korijen = nullptr;
        brojEl = 0;
    }
    void obrisi(const TipKljuca &k) {
        Cvor<TipKljuca, TipVrijednosti> *pomoc = nullptr;
        pretragaBST(k, korijen, pomoc);
        if(pomoc != nullptr) {
            brisiCvorBST(pomoc->kljuc, korijen);
            pomoc = nullptr;
            brojEl--;
        }
    }
    int brojElemenata() const {
        return brojEl;
    }
};

// Binarno stablo
template <typename TipKljuca, typename TipVrijednosti>
class BinStabloMapa : public Mapa<TipKljuca, TipVrijednosti> {
    Cvor<TipKljuca, TipVrijednosti> *korijen;
    int brojEl;
    Cvor<TipKljuca, TipVrijednosti>* &pretragaBST(const TipKljuca &k, Cvor<TipKljuca, TipVrijednosti>* &noviKorjen, Cvor<TipKljuca, TipVrijednosti>* &p) {
        p = noviKorjen;
        while(p != nullptr && k != p->kljuc){
            if(k < p->kljuc){
                p = p->lijevi;
            }
            else  p = p->desni;
        }
        return p;
    }
    Cvor<TipKljuca, TipVrijednosti>* pretragaBST(const TipKljuca &k, Cvor<TipKljuca, TipVrijednosti>* noviKorjen) const {
        while(noviKorjen != nullptr && k != noviKorjen->kljuc){
            if(k < noviKorjen->kljuc){
                noviKorjen = noviKorjen->lijevi;
            }
            else  noviKorjen = noviKorjen->desni;
        }
        return noviKorjen;
    }

    bool brisiCvorBST(const TipKljuca &k, Cvor<TipKljuca, TipVrijednosti>* &noviKorjen) {
        Cvor<TipKljuca, TipVrijednosti>* p = noviKorjen;
        Cvor<TipKljuca, TipVrijednosti>* roditelj = nullptr;

        while(p != nullptr && k != p->kljuc){
            roditelj = p;
            if(k < p->kljuc) p = p->lijevi;
            else p = p->desni;
        }
        if( p == nullptr) return false;

        Cvor<TipKljuca, TipVrijednosti>* m = nullptr;
        Cvor<TipKljuca, TipVrijednosti>* pm = nullptr;
        Cvor<TipKljuca, TipVrijednosti>* tmp = nullptr;
        if(p->lijevi == nullptr){
            m = p->desni;
        }
        else if (p->desni == nullptr){
            m = p->lijevi;
        }
        else {
            pm = p;
            m = p->lijevi;
            tmp = m->desni;
            while(tmp != nullptr){
                pm = m;
                m = tmp;
                tmp = m->desni;
            }
            if(pm != p ){
                pm->desni = m->lijevi;
                m->lijevi = p->lijevi;
            }
            m->desni = p->desni;
        }
        if(roditelj == nullptr) noviKorjen = m;
        else {
            if(p == roditelj->lijevi) {
                roditelj->lijevi = m;
            }
            else {
                roditelj->desni = m;
            }
        }
        if(m != nullptr) m->rod = roditelj;
        delete p;
        p = nullptr;
        return true;
    }

    void obrisiSve(Cvor<TipKljuca, TipVrijednosti>* &korje) {
        Cvor<TipKljuca, TipVrijednosti>* noviKorjen = korje;
        if(noviKorjen == nullptr) return;
        obrisiSve(korje->lijevi);
        obrisiSve(korje->desni);
        delete noviKorjen;
    }
    void kopirajBST(Cvor<TipKljuca, TipVrijednosti>* &prviKorjen, Cvor<TipKljuca, TipVrijednosti>* drugiKorjen){
        if (drugiKorjen == nullptr) return;

        Cvor<TipKljuca, TipVrijednosti>* p = drugiKorjen;

        prviKorjen = new Cvor<TipKljuca, TipVrijednosti>();
        prviKorjen->kljuc = p->kljuc;
        prviKorjen->vrijednost = p->vrijednost;
        prviKorjen->lijevi = nullptr;
        prviKorjen->desni = nullptr;
        
        kopirajBST(prviKorjen->lijevi, p->lijevi);
        kopirajBST(prviKorjen->desni, p->desni);
        if(prviKorjen->lijevi != nullptr) prviKorjen->lijevi->rod = prviKorjen;
        if(prviKorjen->desni  != nullptr) prviKorjen->desni->rod = prviKorjen;
        brojEl++;
    } 
    void umetniBST(Cvor<TipKljuca, TipVrijednosti>* &prviKorjen, Cvor<TipKljuca, TipVrijednosti>* &cvorN){
        Cvor<TipKljuca, TipVrijednosti>* y = nullptr;
        Cvor<TipKljuca, TipVrijednosti>* x = prviKorjen;
        while(x != nullptr){
            y = x;
            if(cvorN->kljuc < x->kljuc)x = x->lijevi;
            else x = x->desni;
        }
        if(y == nullptr) prviKorjen = cvorN;
        else {
            if(cvorN->kljuc < y->kljuc) y->lijevi = cvorN;
            else y->desni = cvorN;
        }
        cvorN->rod = y;
    }
public:
    BinStabloMapa() { korijen=nullptr; brojEl=0; }
    BinStabloMapa(const BinStabloMapa<TipKljuca, TipVrijednosti> &b ) : korijen(nullptr), brojEl(0) {
        kopirajBST(korijen, b.korijen);
    }
    BinStabloMapa<TipKljuca, TipVrijednosti> &operator=(const BinStabloMapa<TipKljuca, TipVrijednosti> &b) {
        if (this==&b) return *this;
        obrisiSve(korijen);
        brojEl = 0;
        korijen=nullptr;
        kopirajBST(korijen, b.korijen);
        return *this;
    }
    ~BinStabloMapa() { obrisiSve(korijen); korijen = nullptr; brojEl = 0; }
    TipVrijednosti &operator[] (TipKljuca k) {
        Cvor<TipKljuca, TipVrijednosti> *pomoc = pretragaBST(k, korijen);
        if(pomoc == nullptr){
            pomoc = new Cvor<TipKljuca, TipVrijednosti>();
            pomoc->kljuc = k;
            pomoc->lijevi = nullptr;
            pomoc->desni = nullptr;
            pomoc->vrijednost = TipVrijednosti();
            umetniBST(korijen, pomoc);
            brojEl++;
        }
        return pomoc->vrijednost;
    }
    TipVrijednosti  operator[] (TipKljuca k) const {
        Cvor<TipKljuca, TipVrijednosti> *pomoc = pretragaBST(k, korijen);
        if (pomoc == nullptr) return TipVrijednosti();
        else return pomoc->vrijednost;
    }
    void obrisi() {
        obrisiSve(korijen);
        korijen = nullptr;
        brojEl = 0;
    }
    void obrisi(const TipKljuca &k) {
        Cvor<TipKljuca, TipVrijednosti> *pomoc = nullptr;
        pretragaBST(k, korijen, pomoc);
        if(pomoc != nullptr) {
            brisiCvorBST(pomoc->kljuc, korijen);
            pomoc = nullptr;
            brojEl--;
        } 
    }
    int brojElemenata() const { return brojEl; }
};




int main()
{
    // testiranje efikasnost binarnog i avl stabla
    AVLStabloMapa <int, int> m;
    BinStabloMapa <int, int> b;
    
    clock_t vrijeme1 = clock();
    int vel = 100;
    for (int i(0); i<vel; i++) {
        m[i] = i;                 // trpanje podataka u avl
    }
    
    clock_t vrijeme2 = clock();
    int ukvrijeme1 = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja dodavanja rng elemenata (prosjecan slucaj) - avl: " << ukvrijeme1 << " ms." << std::endl; 
    
    for (int i(0); i<vel; i++) {
        b[i] = i;                 // trpanje podataka u binarno
    }
    
    clock_t vrijeme4 = clock();
    int ukvrijeme2 = (vrijeme4 - vrijeme2) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja dodavanja rng elemenata (prosjecan slucaj) - binarno: " << ukvrijeme2 << " ms." << std::endl;
    
    // Dodavanje i brisanje novih cvorova treba biti brze za avl u odnosu na binarno
    
    return 0;
}
