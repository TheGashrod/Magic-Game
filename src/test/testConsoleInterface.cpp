#include "../../headers/test/testConsoleInterface.hpp"

#include <iostream>


#include "../../headers/consoleInterface/ConsoleInterface.hpp"
#include "../../headers/Creature.hpp"


int testInterface() {
	ConsoleInterface inter = ConsoleInterface();


	Creature c1 = Creature("Démon de Pagaille", std::list<Color>({Blue, Red}), false, std::list<Color>(Red, Red), 1, 3, 3);
	
	
	inter.showText("showText works !!");
	
	
	cout << "\n\n";
	const Card* c1Ptr = &c1;
	inter.ph1DrawnCard(c1Ptr);
	cout << "\n";
}
