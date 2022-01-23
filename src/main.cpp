// #include <iomanip>


#include "../headers/consoleInterface/ConsoleInterface.hpp"
#include "../headers/Duel.hpp"
#include "../headers/Player.hpp"
#include "../headers/CardsSet.hpp"
#include "../headers/enums/Color.hpp"
#include "../headers/test/testConsoleInterface.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

	Player p1 = Player("J1", CardsSet(std::vector<Card*>()));
	Player p2 = Player("J2", CardsSet(std::vector<Card*>()));
	
   Duel duel = Duel(p1, p2);
   ConsoleInterface interface = ConsoleInterface(&duel);
   duel.addInterface(&interface);



	Color f = Blue;

	if (f == Blue){
		cout << "hello Gael et Simo" << endl;
	}



	mainTest();



	return 0;
}

