#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Gra.h"
#include "Gracz.h"
#include "Ranking.h"

using namespace std;

const int N=15; // ilosc rzedow i kolumn planszy

class Plansza{
public:
	char plansza[N][N];
	static int licznik;
	Plansza(); // konstruktor domyslny
	Plansza(fstream& Plik); // konstruktor przyjmujacy jako argument wywolania plik z gra
	~Plansza(); // destruktor
	friend ostream& operator<<(ostream &wypisz, Plansza& pl); // przeciazony operator wyjscia dzialajacy na plikach
	char get_plansza(int, int); // metoda pobierajaca wybrana komorke planszy
	void set_plansza(int, int, int); // metoda ustawiajaca wybrana komorke planszy
	void rysujPlansze(char tab[N][N]); // metoda rysujaca plansze
	bool koniecGry(char tab[N][N]); // metoda sprawdzajaca wszystkie warunki zwyciestwa
	void setColor(int c); // metoda zmieniajaca kolor wypisywanego tekstu w oknie konsoli
};
