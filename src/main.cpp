// #include <iomanip>


#include "../headers/consoleInterface/ConsoleInterface.hpp"
#include "../headers/Duel.hpp"
#include "../headers/Player.hpp"
#include "../headers/CardsSet.hpp"
#include "../headers/enums/Color.hpp"
#include "../headers/assets/Lands.hpp"
#include "../headers/assets/Creatures.hpp"
#include "../headers/test/testConsoleInterface.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

	Lands landCards = Lands();
	Creatures creatureCards = Creatures();

	Player p1 = Player("J1", CardsSet(std::vector<Card*>()));
	Player p2 = Player("J2", CardsSet(std::vector<Card*>()));
	
   Duel duel = Duel(p1, p2);
   ConsoleInterface interface = ConsoleInterface(&duel);
   duel.addInterface(&interface);



	Color f = Blue;

	if (f == Blue){
		cout << landCards.landsList.at(0) << endl;
	}






	// mainTest();



	return 0;
}

