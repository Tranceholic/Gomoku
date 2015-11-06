#include "Gracz.h"

Gracz::Gracz():nazwaGracza(""), p(NULL), kolejka(0){}

Gracz::Gracz(string playerName, Plansza* pl, int queque){
	this->nazwaGracza=playerName;
	this->p=pl;
	this->kolejka=queque;
}

Gracz::Gracz(Gracz& player){
	this->nazwaGracza=player.nazwaGracza;
	this->p=player.p;
	this->kolejka=player.kolejka;
}

Gracz::~Gracz(){}

Czlowiek::Czlowiek():Gracz(){}

Czlowiek::Czlowiek(string playerName, Plansza* pl, int queque):Gracz(playerName, pl, queque){}

Czlowiek::Czlowiek(Czlowiek& human):Gracz(human.nazwaGracza, human.p, human.kolejka){}

Czlowiek::~Czlowiek(){}

int Czlowiek::get_kolejka(){
	return kolejka;
}

int Komputer::get_kolejka(){
	return kolejka;
}

string Czlowiek::get_nazwaGracza(){
	return nazwaGracza;
}

string Komputer::get_nazwaGracza(){
	return "KOMPUTER";
}
Komputer::Komputer():Gracz(){
	this->nazwaGracza="KOMPUTER";
	this->pauza=0;
}

Komputer::Komputer(string playerName, int pause, int queque):Gracz(playerName, p, queque){
	this->pauza=pause;
}

Komputer::Komputer(Komputer& computer):Gracz(computer.nazwaGracza, computer.p, computer.kolejka){
	this->pauza=computer.pauza;
}

Komputer::~Komputer(){}

void Czlowiek::ruch(int wylosowana, Plansza* pl, int poziomTrudnosci){
	
	int rzad;
	char kolumna;
	
	pl->rysujPlansze(pl->plansza);
	cout << "Podaj rzad i kolumne(rzad-cyfra, kolumna-duza litera):" << endl;
	cin >> rzad >> kolumna;
	while(cin.fail() || rzad<0 || rzad>N || kolumna<'A' || kolumna>'A'+N-1 || pl->get_plansza((rzad-1), (kolumna-'A'))=='X' || pl->get_plansza((rzad-1), (kolumna-'A'))=='O'){
		cout << "Bledne dane, podaj jeszcze raz: " << endl;
		cin.clear();
		cin.sync();
		cin >> rzad >> kolumna;
	}
	if(wylosowana==1){
		pl->set_plansza((rzad-1), (kolumna-'A'), wylosowana);
		pl->licznik++;
	}
	if(wylosowana==2){
		pl->set_plansza((rzad-1), (kolumna-'A'), wylosowana);
		pl->licznik++;
	}	
}

void Komputer::ruch(int wylosowana, Plansza* pl, int poziomTrudnosci){
	srand(time(NULL));
	bool czyMozliwyRuch[N][N];
	for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				czyMozliwyRuch[i][j]=false;
			}
	}

	if(poziomTrudnosci==1 && kolejka==2){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(pl->get_plansza(i, j)!='X' && pl->get_plansza(i, j)!='O'){
					czyMozliwyRuch[i][j]=true;
				}
			}
		}
		int x=rand()%15, y=rand()%15;
		bool stop=false;
		while(stop==false){
			if(czyMozliwyRuch[x][y]==true){
					pl->set_plansza(x, y, 2);
					pl->licznik++;
					stop=true;
			}
			else{
				x=rand()%15;
				y=rand()%15;
			}
		}
	}
	
	if(poziomTrudnosci==2){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(pl->get_plansza(i, j)!='X' && pl->get_plansza(i, j)!='O'){
					czyMozliwyRuch[i][j]=true;
				}
			}
		}
		
		int wyjdz=0;

		for(int w=0;w<N && wyjdz==0;w++){
			for(int k=0;k<N && wyjdz==0;k++){
				if((pl->get_plansza(w, k)=='O') && pl->get_plansza(w, k-1)==pl->get_plansza(w, k) || (pl->get_plansza(w, k)=='O') && pl->get_plansza(w, k-1)==pl->get_plansza(w, k+1) && pl->get_plansza(w, k-1)==pl->get_plansza(w, k) || (pl->get_plansza(w, k)=='O') && pl->get_plansza(w, k)==pl->get_plansza(w, k+1) || pl->get_plansza(w, k)=='O'){
					if(czyMozliwyRuch[w][k+1]==true){
						pl->set_plansza(w, k+1, 2);
						pl->licznik++;
						wyjdz=1;
					}
					else if(czyMozliwyRuch[w][k-1]==true){
							pl->set_plansza(w, k-1, 2);
							pl->licznik++;
							wyjdz=1;
					}
					else{
						bool stop=false;
						w=rand()%15;
						k=rand()%15;
						while(stop==false){
							if(czyMozliwyRuch[w][k]==true){
								pl->set_plansza(w, k, 2);
								pl->licznik++;
								wyjdz=1;
								stop=true;
							}
							else{
								w=rand()%15;
								k=rand()%15;
							}
						}
					}
					
				}
				if(pl->licznik==0 || pl->licznik==1){
					bool stop=false;
					w=rand()%15;
					k=rand()%15;
					while(stop==false){
						if(czyMozliwyRuch[w][k]==true){
							pl->set_plansza(w, k, 2);
							pl->licznik++;
							stop=true;
						}
						else{
							w=rand()%15;
							k=rand()%15;
						}
					}
				}
			}
		}
	}
}
