#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Gra.h"
#include "Plansza.h"
#include "Ranking.h"

using namespace std;

class Plansza;
class Gracz{
protected:
	string nazwaGracza;
	Plansza* p;
	int kolejka;
public:
	virtual void ruch(int wylosowana, Plansza* plansza, int poziomTrudnosci)=0;
	virtual int get_kolejka()=0;
	virtual string get_nazwaGracza()=0;
	Gracz(); // konstruktor domyslny
	Gracz(string playerName, Plansza* pl, int queque); // konstruktor z argumentami
	Gracz(Gracz& player); // konstruktor kopiujacy
	virtual ~Gracz(); // wirtualny destruktor
};

class Czlowiek:public Gracz{
public:
	Czlowiek(); // konstruktor domyslny
	Czlowiek(string playerName, Plansza* pl, int queque); // konstruktor z argumentami
	Czlowiek(Czlowiek& human); // konstruktor kopiujacy
	~Czlowiek(); // destruktor
	int get_kolejka(); // metoda pobierajaca kolejke gracza-czlowieka
	string get_nazwaGracza(); // metoda pobieraja nazwe gracza-czlowieka
	void ruch(int wylosowana, Plansza* plansza, int poziomTrudnosci=0); // metoda wykonujaca ruch gracza-czlowieka na planszy
};

class Komputer:public Gracz{
private:
	int pauza;
public:
	Komputer(); // konstruktor
	Komputer(string playerName, int pause, int queque); // konstruktor z argumentami
	Komputer(Komputer& computer); // konstruktor kopiujacy
	~Komputer(); // destruktor
	int get_kolejka(); // metoda pobierajaca kolejke gracza-komputera
	string get_nazwaGracza(); // metoda pobierajaca nazwe gracza-komputera
	void ruch(int wylosowana, Plansza* plansza, int poziomTrudnosci); // metoda wykonujaca ruch gracza-komputera na planszy
};
