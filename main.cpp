#include <cstdlib>
#include "Plansza.h"
#include "Gra.h"
#include "Gracz.h"
#include "Ranking.h"

using namespace std;

int main(){
	
	Gra* g=new Gra;
	g->start();
	delete g;
	system("pause");
	return 0;
}
