#include "../../headers/test/testConsoleInterface.hpp"

#include <iostream>
#include <list>


#include "../../headers/consoleInterface/ConsoleInterface.hpp"
#include "../../headers/Creature.hpp"


int testInterface() {
	ConsoleInterface inter = ConsoleInterface();


	Creature c1 = Creature("Démon de Pagaille", std::list<Color>({Blue, Red}), false, std::list<Color>({Red, Red}), 1, 3, 3);
	Creature c2 = Creature("The purple scare", std::list<Color>({Black}), false, std::list<Color>({Red, Blue}), 0, 2, 3);
	// TODO : Display cost

	const std::list<Card*> cList1 = std::list<Card*>({&c1, &c2});
	
	
	inter.showText("showText works !!");
	
	
	cout << "\n\n";
	const Card* c1Ptr = &c1;
	inter.ph1DrawnCard(c1Ptr);
	cout << "\n";

	inter.ph2Disengage(cList1);
	cout << "\n";

}