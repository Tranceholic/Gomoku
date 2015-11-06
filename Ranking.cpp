#include "Ranking.h"

string Element::get_nazwaGracza(){
	return nazwaGracza;
}
int Element::get_nrTury(){
	return nrTury;
}
ostream& operator<<(ostream &wypisz, const Element &elem){
	return wypisz << "Nazwa gracza: " << elem.nazwaGracza << " Liczba tur: " << elem.nrTury << endl;
}
Element::Element():nazwaGracza("brak"), nrTury(0), next(NULL){}
Element::Element(string gracz, int tura):nazwaGracza(gracz), nrTury(tura), next(NULL){}
Element::Element(Element& el):nazwaGracza(el.nazwaGracza), nrTury(el.nrTury){}
Element::~Element(){
	delete next;
}

Ranking::Ranking():head(NULL), wsk(NULL){}

Ranking::~Ranking(){
	delete head;
}

void Ranking::wczytajRanking(fstream& Plik){
	string pomNazwa;
	int pomNr;
	
	while(!Plik.eof()){
		Plik >> pomNazwa >> pomNr;
		if(!Plik.eof()){
			if(head==NULL){
				head=new Element(pomNazwa, pomNr);
				wsk=head;
			} 
			else{
				wsk->next=new Element(pomNazwa, pomNr);
				wsk=wsk->next;
			}
		}
	}
}

void Ranking::wypiszRanking(){
	int nr=0;
	wsk=head;
	while(wsk!=NULL){
		cout << nr+1 << " " << *wsk << endl;
		wsk=wsk->next;
		nr++;
	} 
}

void Ranking::sortujRanking(){
	Element* tmp=NULL;
	bool zamiana=false;

	while(!zamiana){
		zamiana=true;
		if(head->get_nrTury()>head->next->get_nrTury()){
			tmp=head->next;
			head->next=head->next->next;
			tmp->next=head;
			head=tmp;
			zamiana=false;
		}
		for(wsk=head;wsk!=NULL && wsk->next!=NULL && wsk->next->next!=NULL;wsk=wsk->next) {
			if(wsk->next->get_nrTury()>wsk->next->next->get_nrTury()){
				tmp=wsk->next;
				wsk->next=wsk->next->next;
				tmp->next=wsk->next->next;
				wsk->next->next=tmp;
				zamiana=false;
			}
		}
	}
}
