// ALGO2 IS1 212A LAB02
// Michał Sprysak
// sm49406@zut.edu.pl

#include <iostream>
#include <string>
#include <time.h>
#include <random>

using namespace std;

template <typename T>
class Array
{
public:
	T* array;
	int rozmiar;
	int maxRozmiar;
	Array() {
		this->rozmiar = 0;
		this->maxRozmiar = 1;
		this->array = NULL;

	}
	void dodajElement(T dane) {
		if (array == NULL)
			array = new T[1];
		if (rozmiar == maxRozmiar) {
			T* pom = new T[maxRozmiar * 2];
			for (int i = 0; i < rozmiar; i++)
			{
				pom[i] = array[i];
			}
			pom[rozmiar] = dane;
			rozmiar++;
			maxRozmiar *= 2;
			delete[] array;
			array = pom;
		}
		else {
			array[rozmiar] = dane;
			rozmiar++;
		}
	}
	T zwroc(int indeks) {
		if (indeks > rozmiar || indeks < 0)
			cout << "Nieprawidlowy indeks";
		else {
			return array[indeks];
		}
	}
	void podmiana(int indeks, T dane) {
		if (indeks > rozmiar || indeks < 0)
			cout << "Nieprawidlowy indeks";
		else {
			array[indeks] = dane;
		}
	}
	void usunTablice() {
		delete[] array;
		array = NULL;
		rozmiar = 0;
		maxRozmiar = 1;
	}
	string toString() {
		string str;
		if (array != NULL) {
			str = "Rozmiar tablicy: " + to_string(rozmiar) + "\nMaksymalny rozmiar tablicy: " + to_string(maxRozmiar) + "\n";
			str += "Elementy tablicy:\n";
			int i = 0;
			do
			{
				str += to_string(array[i]) + " ";
				i++;
			} while (i < rozmiar);
			str += "\n\n";
		}
		else
			str += "Tablica jest pusta\n\n";
		return str;
	}
	void bubbleSort() {
		for (int i = 0; i < rozmiar - 1; i++)
			for (int j = 0; j < rozmiar - i - 1; j++)
				if (array[j] > array[j + 1])
					swap(array[j], array[j + 1]);
	}
};



int main()
{
	string str;
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> dist1(1, 350);
	Array<int>* da = new Array<int>();

	// DODAWANIE ELEMENTU
	for (int i = 0; i < 30; i++)
		da->dodajElement(dist1(rng));
	//WYPIS
	str = da->toString();
	cout << str;
	//BUBBLE SORT
	da->bubbleSort();
	str = da->toString();
	cout << str;
	// PODMIANA
	da->podmiana(9, 876);
	str = da->toString();
	cout << str;
	// ZWRACANIE
	cout << "Zwrocony element\n";
	cout << da->zwroc(9) << endl;;
	//USUWANIE TABLICY
	da->usunTablice();
	str = da->toString();
	cout << str;
    return 0;
}

