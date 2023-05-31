// ALGO2 IS1 212A LAB01
// Michał Sprysak
// sm49406@zut.edu.pl

#include <iostream>
#include <string>
#include <time.h>
#include <random>

using namespace std;

struct proba
{
    char b;
};
template<typename T>
class Wezel
{
public:
    Wezel<T>* nastepny;
    Wezel<T>* poprzedni;
    T klucz;
    Wezel(T klucz)
    {
        this->nastepny = 0;
        this->poprzedni = 0;
        this->klucz = klucz;
    }
};


template<typename T>
class Lista
{
public:
    Wezel<T>* pierwszy, * ostatni;
    int rozmiar;
    Lista()
    {
        this->pierwszy = NULL;
        this->ostatni = NULL;
        this->rozmiar = 0;
    }
    void dodajNaKoniec(T dane);
    void usunListe();
    void dodajNaPoczatek(T dane);
    void usunOstatni();
    void usunPierwszy();
    T zwrocDane(int indeks);

    void podmiana(int indeks, T dane) {
        if (rozmiar<indeks || indeks > rozmiar - 1)
            cout << "\nIndeks poza zakresem\n";
        else
        {
            Wezel<T>* pom = pierwszy;
            for (int i = 0; i < indeks; i++) {
                pom = pom->nastepny;
            }
            pom->klucz = dane;
        }
    }
    Wezel<T>* wyszukajElement(T dane, int (*data_cmp)(T, T)) {
        Wezel<T>* pom = pierwszy;
        for (int i = 0; i < rozmiar; i++) {
            if (data_cmp(dane, pom->klucz) == 0)
                return pom;
            pom = pom->nastepny;
        }
        return NULL;
    }
    bool wyszukajUsun(T dane, int(*data_cmp)(T, T)) {
        Wezel<T>* pom = pierwszy;
        bool flaga = false;
        for (int i = 0; i < rozmiar; i++) {
            if (data_cmp(dane, pom->klucz) == 0) {
                if (pom->poprzedni == NULL) {
                    pom->nastepny->poprzedni = NULL;
                    pierwszy = pom->nastepny;
                }
                else if (pom->nastepny == NULL) {
                    pom->poprzedni->nastepny = NULL;
                    ostatni = pom->poprzedni;
                }
                else if (pom->poprzedni != NULL && pom->nastepny != NULL) {
                    pom->nastepny->poprzedni = pom->poprzedni;
                    pom->poprzedni->nastepny = pom->nastepny;
                }
                rozmiar--;
                delete pom;
                return flaga = true;
            }
            else
                pom = pom->nastepny;
        }
        return false;
    }
    void dodajWymuszeniePorzadku(T dane, int (*data_cmp)(T, T)) {
        Wezel<T>* pomocniczy = pierwszy;
        if (pierwszy == NULL)
            return dodajNaPoczatek(dane);
        else {
            for (int i = 0; i < rozmiar; i++) {
                if (data_cmp(dane, pomocniczy->klucz) > 0) {
                    if (i == rozmiar - 1)
                        return dodajNaKoniec(dane);
                    else
                        pomocniczy = pomocniczy->nastepny;
                }
                else {
                    Wezel<T>* nowyWezel = new Wezel<T>(dane);
                    nowyWezel->nastepny = pomocniczy;
                    nowyWezel->poprzedni = pomocniczy->poprzedni;
                    nowyWezel->nastepny->poprzedni = nowyWezel;
                    nowyWezel->poprzedni->nastepny = nowyWezel;
                    rozmiar++;
                    return;
                }
            }
        }
    }
    string toString() {
        Wezel<T>* pom = pierwszy;
        string str = "Elementy listy: ";
        int i = 0;
        do
        {
            str += to_string(pom->klucz) + ' ';
            pom = pom->nastepny;
            i++;
        } while (i<rozmiar);
        str += "\nRozmiar listy: " + to_string(rozmiar);
        return str;
    }
};

template<typename T>
void Lista<T>::dodajNaPoczatek(T dane) {
    if (pierwszy == NULL || ostatni == NULL) {
        Wezel<T>* nowyWezel = new Wezel<T>(dane);
        pierwszy = nowyWezel;
        ostatni = pierwszy;
        ostatni->nastepny = NULL;
        ostatni->poprzedni = NULL;
    }
    else
    {
        Wezel<T>* nowyWezel = new Wezel<T>(dane);

        nowyWezel->nastepny = pierwszy;
        pierwszy->poprzedni = nowyWezel;

        pierwszy = nowyWezel;
        pierwszy->poprzedni = NULL;
    }
    rozmiar++;
}

template<typename T>
void Lista<T>::dodajNaKoniec(T dane) {
    if (pierwszy == NULL || ostatni == NULL) {
        Wezel<T>* nowyWezel = new Wezel<T>(dane);
        ostatni = nowyWezel;
        pierwszy = ostatni;
        pierwszy->nastepny = NULL;
        pierwszy->poprzedni = NULL;
    }
    else {
        Wezel<T>* nowyWezel = new Wezel<T>(dane);
        nowyWezel->poprzedni = ostatni;
        ostatni->nastepny = nowyWezel;

        ostatni = nowyWezel;
        ostatni->nastepny = NULL;
    }
    rozmiar++;
}
template<typename T>
void Lista<T>::usunOstatni() {
    if (ostatni != NULL) {
        Wezel<T>* pom = ostatni;
        ostatni = ostatni->poprzedni;
        delete pom;
        if (ostatni != NULL)
            ostatni->nastepny = NULL;
        rozmiar--;
    }
}
template<typename T>
void Lista<T>::usunPierwszy() {
    if (pierwszy != NULL) {
        Wezel<T>* pom = pierwszy;
        pierwszy = pierwszy->nastepny;
        delete pom;
        if (pierwszy != NULL)
            pierwszy->poprzedni = NULL;
        rozmiar--;
    }
}
template<typename T>
T Lista<T>::zwrocDane(int indeks)
{
    if (rozmiar < indeks || indeks>rozmiar - 1)
        cout << "\nIndeks poza zakresem\n";
    else {
        Wezel<T>* pom = pierwszy;
        for (int i = 0; i < indeks; i++) {
            pom = pom->nastepny;
        }
        return pom->klucz;
    }
}

template<typename T>
void Lista<T>::usunListe() {
    if (pierwszy != NULL || ostatni != NULL)
    {
        Wezel<T>* pom = pierwszy;
        int i = 0;
        do
        {
            pom = pom->nastepny;
            delete pom->poprzedni;
            i++;
        } while (i < rozmiar - 1);
        rozmiar = 0;
        delete pom;
        pierwszy = NULL;
        ostatni = NULL;
    }
}

int komparator(int obj1, int obj2)
{
    if (obj1 == obj2)
        return 0;
    else if (obj1 < obj2)
        return -1;
    else
        return 1;
}

int main()
{
    Lista <int>* ll = new Lista <int>();
    string str;
    int i = 0;
    cout << "Dodawanie\n";
    do
    {
        ll->dodajNaKoniec(i);
        i++;
    } while (i<20);
    str = ll->toString();
    cout << str;
    cout << "\n\nWyszukaj element\n";
    Wezel<int>* szukaj = ll->wyszukajElement(5, komparator);
    cout << szukaj->klucz << endl;
    cout << "\nWyszukaj i usun\n";
    ll->wyszukajUsun(5, komparator);
    str = ll->toString();
    cout << str;
    cout << "\n\nDodaj z wymuszeniem porzadku\n";
    ll->dodajWymuszeniePorzadku(5, komparator);
    str = ll->toString();
    cout << str;
 
    //const int maxRzad = 6; // maksymalny rzad wielkosci rozmiaru dodawawnych danych
    //Lista <int>* ll1 = new Lista <int>();
    //random_device dev;
    //mt19937 rng(dev());
    //uniform_int_distribution<mt19937::result_type> dist(1, 10000);

    //for (int o = 0; o <= maxRzad; o++) { //petla po rzedach wielkosci
    //    const int r = pow(10, o); //rozmiar danych

    //    //dodawanie do listy
    //    clock_t tPoczatek = clock();
    //    for (int j = 0; j < r; j++)
    //        ll1->dodajNaKoniec(dist(rng));
    //    clock_t tKoniec = clock();

    //    float calkowity = float(tKoniec - tPoczatek) / CLOCKS_PER_SEC;
    //    cout << "Ilosc operacji dodawania" << r << " zajelo: " << calkowity << "s\n";
    //    cout << "Sredni czas na pojedyncza operacje: " << calkowity / r << "s\n";
    //}
    //string st;
    //cout << "\n\n\n\n";
    //st = ll1->toString();
    //cout << st;
    //cout << "\n\n\n\n";
    //
    //for (int o = 0; o <= maxRzad; o++) {
    //    const int m = pow(10, o);
    //    clock_t tPoczatek = clock();
    //    for (int i = 0; i < m; i++) {
    //        ll1->usunListe();
    //        //ll1->wyszukajUsun(dist(rng), komparator);
    //    }
    //    clock_t tKoniec = clock();
    //    float calkowity = float(tKoniec - tPoczatek) / CLOCKS_PER_SEC;
    //    cout << "Ilosc operacji usuwania" << m << " zajelo: " << calkowity << "s\n";
    //    cout << "Sredni czas na pojedyncza operacje: " << calkowity / m << "s\n";

    //}

    return 0;

}
