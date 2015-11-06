#include "Gra.h"

Gra::Gra(){
	gracz[0]=NULL;
	gracz[1]=NULL;
	p=new Plansza();
	round=0;
}
Gra::Gra(Gra& g){
	gracz[0]=g.gracz[0];
	gracz[1]=g.gracz[1];
	p=g.p;
	round=g.round;
}
Gra::~Gra(){
	delete gracz[0];
	delete gracz[1];
	delete p;
}
void Gra::start(){
	system("title Gomoku");
	int menu=43;
	int menu1=34;
	string nazwa, nazwa1, nazwa2, nazwaPliku;
	int poziomTrudnosci=76;

	while(menu!=5){
		system("cls");
		cout << "===================================" << endl;
		cout << "============ GRA GOMOKU ===========" << endl;
		cout << "===================================" << endl;
		cout << "Wybierz opcje:" << endl;
		cout << "1. Nowa gra" << endl;
		cout << "2. Wczytaj zapisana gre" << endl;
		cout << "3. Zasady gry" << endl;
		cout << "4. Ranking graczy" << endl;
		cout << "5. Zakoncz gre" << endl;
		cout << "Autor: Dawid Kuczer ;)" << endl;
		cin >> menu;
		while(cin.fail() || menu>5 || menu<1){
			cout << "Bledne dane, podaj jeszcze raz: " << endl;
			cin.clear();
			cin.sync();
			cin >> menu;
		}
		switch(menu){
		case 1:
			cout << endl;
			cout << "Wybierz typ rozgrywki:" << endl;
			cout << "1. Gracz vs. komputer" << endl;
			cout << "2. Gracz vs. gracz" << endl;
			cout << "3. Powrot do glownego menu" << endl;
			cin >> menu1;
			while(cin.fail() || menu1>3 || menu1<1){
				cout << "Bledne dane, podaj jeszcze raz: " << endl;
				cin.clear();
				cin.sync();
				cin >> menu1;
			}
			switch(menu1){
			case 1:
				cout << endl;
				cout << "Podaj nazwe gracza:" << endl;
				cin >> nazwa;
				cout << "Podaj poziom trudnosci:" << endl;
				cout << "1.Latwy" << endl;
				cout << "2.Trudny" << endl;
				cin >> poziomTrudnosci;
				while(cin.fail() || poziomTrudnosci>2 || poziomTrudnosci<1){
					cout << "Bledne dane, podaj jeszcze raz: " << endl;
					cin.clear();
					cin.sync();
					cin >> poziomTrudnosci;
				}
				
				gracz[0]=new Czlowiek(nazwa, p, 1);
				gracz[1]=new Komputer("KOMPUTER", 0, 2);

				tura(nazwa, "KOMPUTER", poziomTrudnosci);
				continue;
			case 2:
				cout << endl;
				cout << "Podaj nazwe pierwszego gracza:" << endl;
				cin >> nazwa1;
				cout << endl;
				cout << "Podaj nazwe drugiego gracza:" << endl;
				cin >> nazwa2;
				
				gracz[0]=new Czlowiek(nazwa1, p, 1);
				gracz[1]=new Czlowiek(nazwa2, p, 2);
				
				tura(nazwa1, nazwa2, poziomTrudnosci);
				continue;
			case 3:
				continue;
			}
		case 2:
			cout << "Podaj nazwe pliku gry (z rozszerzeniem), ktora chcesz wczytac:" << endl;
			cin >> nazwaPliku;
			wczytajGre(nazwaPliku);
			continue;
		case 3:
			cout << endl;
			cout << "Gra rozgrywana jest na planszy 15x15 pol." << endl;
			cout << "Kazdy z dwoch graczy ma do dyspozycji kamienie:" << endl;
			cout << "Jeden koloru bialego, drugi - czarnego," << endl;
			cout << "ktore ukladaja na przemian na wolnych polach planszy." << endl;
			cout << "Celem gry jest ulozenie na planszy DOKLADNIE PIECIU" << endl;
			cout << "(nie wiecej) kamieni swojego koloru w ciaglej linii" << endl;
			cout << "-- poziomej, pionowej lub ukosnej." << endl;
			cout << "Pierwszy gracz, ktory tego dokona, zostaje zwyciezca." << endl;
			cout << "Jesli nie uda sie to nikomu (plansza zostanie zapelniona), nastepuje remis." << endl;
			cout << endl;
			system("pause");
			continue;
		case 4:
			cout << endl;
			cout << "Hala zwyciezcow" << endl;
			pokazRanking();
			system("pause");
			continue;
		}
	}
}

void Gra::tura(string nazwa1, string nazwa2, int poziomTrudnosci){
	string nazwaPliku;

	cout << "Podaj nazwe pliku (bez rozszerzenia), do ktorego ma byc zapisywana gra:"<< endl;
	cin >> nazwaPliku;
	do{
			gracz[round%2]->ruch(gracz[round%2]->get_kolejka(), p, poziomTrudnosci);
			round++;
			zapiszGre(nazwaPliku, round, poziomTrudnosci, nazwa1, nazwa2);
	}while(p->koniecGry(p->plansza)==false);
	p->rysujPlansze(p->plansza);
	cout << "Gracz: " << gracz[(round-1)%2]->get_nazwaGracza() << " wygral gre ;)" << endl;
	system("pause");
	fstream Plik;
	Plik.open("Lista.txt", ios::out | ios::app);
	Plik << gracz[(round-1)%2]->get_nazwaGracza() << ' ' << round << endl;
	Plik.close();
	exit(0);
}
	

void Gra::zapiszGre(string nazwaPliku, int nrTury, int poziomTrudnosci, string nazwa1, string nazwa2){
	fstream Plik;
	nazwaPliku+=".txt";
	
	do{
		Plik.open(nazwaPliku, ios::trunc | ios::out);
		if(!Plik.is_open()){
			cout << "Bledna nazwa pliku. Podaj jeszcze raz:" << endl;
			cin >> nazwaPliku;
			nazwaPliku+=".txt";
		}
	}while(!Plik.is_open());
	Plik << nazwa1 << ' ' << nazwa2 << ' ' << nrTury << ' ' << poziomTrudnosci << endl;
	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			Plik << p->get_plansza(i, j) << ' ';
		}
		Plik << endl;
	}
	Plik.close();
}
void Gra::wczytajGre(string nazwaPliku){
	fstream Plik;
	do{
		Plik.open(nazwaPliku, ios::in);
		if(!Plik.is_open()){
			cout << "Bledna nazwa pliku. Podaj jeszcze raz:" << endl;
			cin >> nazwaPliku;
		}
	}while(!Plik.is_open());
	string nazwa1, nazwa2;
	int pomNrTury;
	int pozTrudnosci;
	Plik >> nazwa1 >> nazwa2 >> pomNrTury >> pozTrudnosci;
	round=pomNrTury;
	if(nazwa1!="KOMPUTER" && nazwa2!="KOMPUTER") {
		gracz[0]=new Czlowiek(nazwa1, p, 1);
		gracz[1]=new Czlowiek(nazwa2, p, 2);
	}
	else if(nazwa1!="KOMPUTER" && nazwa2=="KOMPUTER"){
		gracz[0]=new Czlowiek(nazwa1, p, 1);
		gracz[1]=new Komputer(nazwa2, 0, 2);
	}
	p=new Plansza(Plik);
	Plik.close();
	tura(nazwa1, nazwa2, pozTrudnosci);
}

void Gra::pokazRanking(){
	string nazwaPliku;
	Ranking* wsk=new Ranking;
	fstream Plik;
	do{
		cout << "Podaj nazwe pliku z rankingiem:" << endl;
		cin >> nazwaPliku;
		Plik.open(nazwaPliku, ios::in);
	}while(!Plik.is_open());
	wsk->wczytajRanking(Plik);
	wsk->sortujRanking();
	wsk->wypiszRanking();
	Plik.close();
}
