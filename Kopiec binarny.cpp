// ALGO2 IS1 212A LAB06
// Michał Sprysak
// sm49406@zut.edu.pl

#include <iostream>
#include <string>
#include <random>
#include <time.h>

using namespace std;

template <typename T>
class BH {
public:

    T* arr;
    unsigned int size = 0; //aktualny rozmiar
    unsigned int maxSize = 1; //maksymalny mozliwy rozmiar
    BH() {
        this->arr = new T[maxSize];
    }
    int parent(int id) {
        return (id - 1) / 2;
    }
    int leftChild(int id) {
        return 2 * id + 1;
    }
    int rightChild(int id) {
        return 2 * id + 2;
    }


    void Down(int id);
    void addElement(T dane);
    void Up(int id);

    void delR() {
        if (size == 0) return;
        T deleteEl = arr[0];
        arr[0] = arr[size - 1];
        size--;
        Down(0);
    }


    void clearHeap() {
        size = 0;
        maxSize = 1;
        delete[] arr;
        arr = nullptr;
        arr = new T[size];
    }
    string toString() {
        string str;
        if (size == 0) {
            str = "Kopiec binarny jest pusty\n";

            str += "Rozmiar: " + to_string(size);
            str += "\nMaksymalny rozmiar: " + to_string(maxSize);
        }
        else
        {
            str += "Rozmiar: " + to_string(size);
            str += "\nMaksymalny rozmiar: " + to_string(maxSize) + "\n";
            for (int i = 0; i < size; i++)
            {
                str += " | " + to_string(arr[i]) + " |\n";
            }
        }
        root();
        return str;
    }
    void root() {
        string str;
        if (size != 0)
            cout << "Korzen: " + to_string(arr[0]) + "\n";
        else
        {
            return;
        }

    }
};
template<typename T>
void BH<T>::Up(int id) {
    int parentId = parent(id);
    if (id > 0 && arr[id] < arr[parentId]) {
        swap(arr[id], arr[parentId]);
        Up(parentId);
    }
}
template<typename T>
void BH<T>::addElement(T dane) {
    if (size == maxSize) {
        maxSize *= 2;
        T* newArr = new T[maxSize];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        newArr[size] = dane;
        size++;
        arr = newArr;
    }
    else
    {
        arr[size] = dane;
        size++;
    }
    Up(size - 1);
}

template<typename T>
void BH<T>::Down(int id) {
    int leftC = leftChild(id);
    int rightC = rightChild(id);
    if (rightC < size)
    {
        if (arr[leftC] >= arr[rightC] && arr[id] >= arr[rightC])
        {
            swap(arr[id], arr[rightC]);
            Down(rightC);
        }
        else if (arr[leftC] <= arr[rightC] && arr[id] >= arr[leftC])
        {
            swap(arr[id], arr[leftC]);
            Down(leftC);
        }
    }
    else if (rightC == size && arr[id] >= arr[leftC])
    {
        swap(arr[id], arr[leftC]);
        Down(leftC);
    }
    return;
}


int main()
{
    const int MAX_ORDER = 7;
    BH<int>* bh = new BH<int>;

    random_device rng;
    mt19937 mt(rng());
    uniform_int_distribution<int> ds1(1, 10000);

    for (int o = 0; o < MAX_ORDER; o++)
    {
        const int n = pow(10, o);

        clock_t t1 = clock();
        for (int i = 0; i < n; i++)
        {
            bh->addElement(ds1(mt));
        }
        clock_t t2 = clock();
        double czasDodawania = (double)(t2 - t1) / CLOCKS_PER_SEC;
        double sredniCzasDodawania = (double)(czasDodawania / n);

        cout << "###########" << endl;
        cout << "#DODAWANIE#" << endl;
        cout << "###########" << endl << endl;
        cout << "Czas dodawnia wszystkich elementow: " << czasDodawania << " s\n";
        cout << "Sredni czas dodawania pojedynczego elementu: " << sredniCzasDodawania << " s\n";
        cout << "Ilosc dodanych elementow: " << n << "\n";

        clock_t td1 = clock();
        for (int i = 0; i < n; i++)
        {
            bh->delR();
        }
        clock_t td2 = clock();
        double czasUsuwania = (double)(td2 - td1) / CLOCKS_PER_SEC;
        double sredniCzasUsuwania = (double)(czasUsuwania / n);
        cout << "\n##########" << endl;
        cout << "#USUWANIE#" << endl;
        cout << "##########" << endl << endl;
        cout << "Czas pobrania i usuniecia kopca : " << czasUsuwania << " s\n";
        cout << "Sredni czas pobrania i usuniecia pojedynczego elementu kopca: " << sredniCzasUsuwania << "s\n";
        cout << "\n\n";
        bh->clearHeap();
    }
    delete bh;
    return 0;




    //BH<int>* o1 = new BH<int>;
    //string str;
    //o1->addElement(21);
    //o1->addElement(5);
    //o1->addElement(33);
    //o1->addElement(35);
    //o1->addElement(78);
    //o1->addElement(9);
    //o1->addElement(2);
    //o1->addElement(12);
    //o1->addElement(66);
    //o1->addElement(10);
    //o1->addElement(0);
    //o1->addElement(29);
    ////o1->clearHeap();
    //o1->delR();
    //str = o1->toString();
    //cout << str;
    //return 0;
}
