#include "Plansza.h"

void Plansza::setColor(int c){
	HANDLE kolorek;
	kolorek=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(kolorek, c);
}

ostream& operator<<(ostream &wypisz, Plansza& pl) {
	system("cls");
	wypisz << endl << "  ";
	for(int k=0;k<N;k++){
		wypisz << " ___";
	}
	wypisz << endl;
	for(int l=0;l<N;l++){
		wypisz << "  ";
		for(int k=0;k<N;k++){
			wypisz << "|   ";
		}
		wypisz << "|" << endl;
		wypisz.width(2);
		wypisz << l+1;
		for(int k=0;k<N;k++){
			wypisz << "| " << pl.plansza[l][k] << " ";
		}
		wypisz << "|" << endl;
		wypisz << "  ";
		for(int k=0;k<N;k++){
			wypisz << "|___";
		}
		wypisz << "|" << endl;
	}
	wypisz << " ";
	for(int k=0;k<N;k++){
		wypisz << "   " << (char)('A'+k);
	}
	wypisz << endl;
	return wypisz;
}

Plansza::Plansza(){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			plansza[i][j]=NULL;
		}
	}
}
Plansza::Plansza(fstream& Plik){
	char pomPlansza[N][N];

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			Plik >> pomPlansza[i][j];
			plansza[i][j]=pomPlansza[i][j];
		}
	}
}
Plansza::~Plansza(){
	
}

char Plansza::get_plansza(int m, int n){
	return plansza[m][n];
}
void Plansza::set_plansza(int m, int n, int wylosowana){
	if(wylosowana==1)
		this->plansza[m][n]='X';
	if(wylosowana==2)
		this->plansza[m][n]='O';
}
void Plansza::rysujPlansze(char plansza[N][N]){

	system("cls");
	cout << endl << "  ";
	for(int k=0;k<N;k++){
		cout << " ___";
	}
	cout << endl;
	for(int l=0;l<N;l++){
		cout << "  ";
		for(int k=0;k<N;k++){
			cout << "|   ";
		}
		cout << "|" << endl;
		cout.width(2);
		cout << l+1;
		for(int k=0;k<N;k++){
			if(plansza[l][k]=='*'){
				cout << "| ";
				setColor(3);
				cout << plansza[l][k];
				setColor(7);
				cout << " ";
			}
			else
			cout << "| " << plansza[l][k] << " ";
		}
		cout << "|" << endl;
		cout << "  ";
		for(int k=0;k<N;k++){
			cout << "|___";
		}
		cout << "|" << endl;
	}
	cout << " ";
	for(int k=0;k<N;k++){
		cout << "   " << (char)('A'+k);
	}
	cout << endl;

}

bool Plansza::koniecGry(char tab[N][N]){
	int w, k, c, i;
	
	// szukamy zwycieskiego ustawienia w poziomie
	for(w=0;w<15;w++){
		c=1;
		for(k=1;k<15;k++){
			if(tab[w][k-1]==tab[w][k]) c++;
			else c=1;
			if((c==5) && tab[w][k]){
				if((k<14) && (tab[w][k]==tab[w][k+1])) continue;
				for(i=0;i<5;i++)
					tab[w][k-i] = '*'; // zaznaczamy zwycieskie ustawienie
				return true;
			}
		}
	}
	// szukamy zwycieskiego ustawienia w pionie
	for(k=0;k<15;k++){
		c=1;
		for(w=1;w<15;w++){
			if(tab[w-1][k]==tab[w][k]) c++;
			else c=1;
			if((c==5) && tab[w][k]){
				if((w<14) && (tab[w][k]==tab[w+1][k])) continue;
				for(i=0;i<5;i++) tab[w-i][k] = '*'; // zaznaczamy zwycieskie ustawienie
				return true;
			}
		}
	}
	// szukamy zwycieskiego ustawienia po przekatnej z lewa na prawo w dol
	for(k=0;k<11;k++){
		for(w=0;w<11;w++){
			c=1;
			for(i=1;i<5;i++){
				if(tab[w+i-1][k+i-1]==tab[w+i][k+i]) c++;
				else c=1;
				if((c==5) && tab[w][k]){
					if((w<10) && (k<10) && (tab[w][k]==tab[w+5][k+5]))
						continue;
					if((w) && (k) && (tab[w][k]==tab[w-1][k-1]))
						continue;
					for(i=0;i<5;i++) tab[w+i][k+i] = '*'; // zaznaczamy zwycieskie ustawienie
					return true;
				}
			}
		}
	}
	// szukamy zwycieskiego ustawienia po przekatnej z prawa na lewo w dol
	for(k=4;k<15;k++){
		for(w=0;w<11;w++){
			c=1;
			for(i=1;i<5;i++){
				if(tab[w+i-1][k-i+1]==tab[w+i][k-i]) c++;
				else c=1;
				if((c==5) && tab[w][k]){
					if((w<10) && (k>4) && (tab[w][k]==tab[w+5][k-5]))
						continue;
					if((w) && (k<15) && (tab[w][k]==tab[w-1][k+1]))
						continue;
					for(i=0;i<5;i++) tab[w+i][k-i] = '*'; // zaznaczamy zwycieskie ustawienie
					return true;
				}
			}
		}
	}
	// sprawdzamy czy nie zostal wyczerpany limit ruchow
	if(licznik==226)
		return true;

	return false;
}

int Plansza::licznik=0;
