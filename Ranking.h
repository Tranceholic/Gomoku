#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Gra.h"
#include "Gracz.h"
#include "Plansza.h"

using namespace std;

class Element{
private:
	string nazwaGracza;
	int nrTury;
	int pozTrud;
public:
	Element* next;
	string get_nazwaGracza(); // metoda pobierajaca nazwe gracza
	int get_nrTury(); // metoda pobieracaja numer tury
	friend ostream& operator<<(ostream &wypisz, const Element &elem); // przeciazany operator wyjscia dzialajacy na plikach
	Element(); // konstruktor domyslny
	Element(string nazwaGracz, int nrTur); // konstruktor z argumentami
	Element(Element& el); // konstruktor kompiujacy
	~Element(); // destruktor
};

class Ranking{
public:
	Element* head;
	Element* wsk;
	void wczytajRanking(fstream& Plik); // metoda wczytujaca liste zwyciezcow z pliku o podanej nazwie
	void wypiszRanking(); // metoda wypisujaca liste zwyciezcow
	void sortujRanking(); // metoda sortujaca liste zwyciezcow
	Ranking(); // konstruktor domyslny
	~Ranking(); // destruktor
};
