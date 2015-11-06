#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include "Plansza.h"
#include "Gracz.h"
#include "Ranking.h"

using namespace std;

class Ranking;
class Gracz;
class Plansza;
class Gra{
private:
	Gracz* gracz[2];
	Plansza* p;
	int round;
public:
	Gra(); // konstruktor domyslny
	Gra(Gra& g); // konstruktor kopiujacy
	~Gra(); // destruktor
	void start(); // metoda odpowiadajaca za rozpoczecie gry (wybor opcji i inne wodotryski)
	void tura(string, string, int); // metoda odpowiadajaca za przeprowadzenie jednej tury gry
	void zapiszGre(string nazwaPliku, int nrTury, int poziomTrudnosci, string nazwa1, string nazwa2); // metoda zapisujaca aktualny stan gry do pliku
	void wczytajGre(string nazwaPliku); // metoda wczytujaca zapisany stan gry z pliku
	void pokazRanking(); // metoda wypisujaca liste z najlepszymi graczami
};
