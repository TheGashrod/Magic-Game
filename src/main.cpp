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

#define UNUSED(x) (void)x;


int main(int argc, char *argv[]) {

	Lands landCards = Lands();
	Creatures creatureCards = Creatures();

	vector<Card*> deck = vector<Card*>();

	for (int i=0; i<21; i++){ deck.push_back(&creatureCards.creaturesList.at(i)); };
	for (int i=0; i<20; i++){ deck.push_back(&landCards.landsList.at(i)); };


	Player p1 = Player("MOHAMMED", CardsSet(deck));
	Player p2 = Player("GAEL", CardsSet(deck));
	
   Duel duel = Duel(p1, p2);
   ConsoleInterface interface = ConsoleInterface(&duel);

	UNUSED(argc); UNUSED(argv); UNUSED(interface);
   


   duel.start();






	// mainTest();



	return 0;
}

