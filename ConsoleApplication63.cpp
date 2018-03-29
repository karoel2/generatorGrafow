#include "stdafx.h"
#include "iostream"
#include "cstdlib"
#include "algorithm"
#include "vector"
#include "stdio.h"
#include "cstdio"
#include "list"
using namespace std;
int n, x;
int tab[1000000][2];
bool prz;
vector<int>OUTDa, OUTDb, OUTLa, OUTLb, wyj, wyja, INa, INb, INc;
struct stacja {
	int numer;
	int odl;
};
list <stacja> lista;
void dosmt(stacja &X, int &suma, int a, int b, int &c) {
	suma += X.odl;
	if (suma > b) {
		suma -= X.odl;
		c = b - suma;
	}
}
void yt(stacja &X, int c) {
	X.odl -= c;
}
int dodaj(int a, int b) {
	int suma = 0, c = 0;
	if (lista.empty() == true) {
		stacja temp;
		temp.numer = a;
		temp.odl = b;
		lista.push_back(temp);
		temp.numer = n;
		temp.odl = x - b;
		lista.push_back(temp);
		return 0;
	}
	else {
		for (list<stacja>::iterator it = lista.begin(); it != lista.end(); ++it) {
			dosmt(*it, suma, a, b, c);
			if (c != 0) {
				yt(*it, c);
				stacja temp;
				temp.numer = a;
				temp.odl = c;
				lista.insert(it, temp);
				return 0;
			}
		}
		stacja temp;
		temp.numer = a;
		temp.odl = b - suma;
		lista.push_back(temp);
		return 0;
	}
}
void ustaw(stacja &X, int &a) {
	a = X.numer;
}
void wypiszz() {
	int a = 1;
	for (list<stacja>::iterator it = lista.begin(); it != lista.end(); ++it) {
		printf("%d %d %d\n", a, it->numer, it->odl);
		ustaw(*it, a);
	}
}void tr(stacja &X, int &k) {
	k = X.odl;
}
int dodawaj(int a, int b, int c) {
	if (((b + a) - x) % 2 == 1) {
		printf("NIE\n");
		exit(0);
	}
	int odle = ((b + a) - x) / 2;
	int r = a - odle;
	int y;
	for (list<stacja>::iterator it = lista.begin(); it != lista.end(); ++it) {
		tr(*it, y);
		if (y == r) {
			INa.push_back(odle);
			INb.push_back(c);
			INc.push_back(it->odl);
			return 0;
		}
	}
	INa.push_back(odle);
	INb.push_back(c);
	INc.push_back(0);
	wyj.push_back(r);
	return 0;
}
void wyjj() {
	bool wartownik;
	int k;
	for (int i = 0; i < wyj.size(); i++) {
		wartownik = false;
		for (list<stacja>::iterator yt = lista.begin(); yt != lista.end(); ++yt) {
			tr(*yt, k);
			if (k == wyj[i]) {
				for (int i = 0; i < wyj.size(); i++) {
					if (INc[i] == 0) {
						ustaw(*yt, INc[i]);
						wartownik = true;
						break;
					}
				}
			}
		}
		if (wartownik == false) {
			printf("NIE\n");
			exit(0);
		}
	}
}
void suma(int w) {
	if (x == 0) x = tab[w][0] + tab[w][1];
	else if (tab[w][0] + tab[w][1] < x) {
		x = tab[w][0] + tab[w][1];
	}
}
int przypadek() {
	for (int i = 1; i < n - 2; i++) {
		if (abs(tab[i][0] - tab[i][1]) != abs(tab[i - 1][0] - tab[i - 1][1])) {
			prz = true;
			return 0;
		}
	}
	for (int i = 1; i < n - 2; i++) {
		if (tab[i][0] == tab[i][1]) {
			prz = true;
			return 0;
		}
	}
	if (tab[0][0] < tab[0][1]) {
		x = tab[0][0];
	}
	else x = tab[0][1];
	prz = false;
	return 0;
}
void load() {
	scanf_s("%d", &n);
	for (int i = 0; i < n - 2; i++) {
		scanf_s("%d", &tab[i][0]);
	}
	for (int i = 0; i < n - 2; i++) {
		scanf_s("%d", &tab[i][1]);
		suma(i);
	}
	przypadek();
}
void dodaj(int a, int b, int c) {
	if (a + b == x) {
		dodaj(c + 2, a);

	}
	else if (abs(a - b) == x) {
		if (a > b) {
			OUTLa.push_back(c);
			OUTLb.push_back(b);
		}
		else {
			OUTDa.push_back(c);
			OUTDb.push_back(a);
		}
	}
	else if (abs(a - b) < x) {
		dodawaj(a, b, c + 2);
	}
	else {
		cout << "NIE\n";
		exit(0);
	}
}
void dod(int a, int b, int c) {
	if (a > b) {
		OUTLa.push_back(c);
		OUTLb.push_back(b);
	}
	else {
		OUTDa.push_back(c);
		OUTDb.push_back(a);
	}
}
void wypisz() {
	for (int i = 0; i <OUTDa.size(); i++) {
		printf("%d %d %d\n", OUTDa[i] + 2, 1, OUTDb[i]);
	}
	for (int i = 0; i <OUTLa.size(); i++) {
		printf("%d %d %d\n", OUTLa[i] + 2, n, OUTLb[i]);
	}
	for (int i = 0; i <INa.size(); i++) {
		printf("%d %d %d\n", INc[i], INb[i], INa[i]);
	}
	for (int i = INa.size() - 1; i >= 0; i--) {
		printf("%d %d %d\n", INc[i], INb[i], INa[i]);
	}
}
int main()
{
	load();
	if (prz == true) {
		for (int i = 0; i < n - 2; i++) {
			int a = tab[i][0], b = tab[i][1];
			dodaj(a, b, i);
		}
	}
	else {
		for (int i = 0; i < n - 2; i++) {
			int a = tab[i][0], b = tab[i][1];
			dod(a, b, i);
		}
	}
	wyjj();
	cout << "TAK\n";
	wypisz();
	wypiszz();
	return 0;
}