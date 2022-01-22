#include "../../headers/test/testConsoleInterface.hpp"

#include <iostream>
#include <list>


#include "../../headers/consoleInterface/ConsoleInterface.hpp"
#include "../../headers/Contender.hpp"
#include "../../headers/Creature.hpp"
#include "../../headers/Duel.hpp"


int testInterface() {

	Player p1 = Player("J1", CardsSet(std::vector<Card*>()));
	Player p2 = Player("J2", CardsSet(std::vector<Card*>()));

	Duel d = Duel(p1, p2);
	ConsoleInterface inter = ConsoleInterface(d);


	Creature c1 = Creature("Démon de Pagaille", std::list<Color>({Blue, Red}), false, std::list<Color>({Red, Red}), 1, 3, 3);
	Creature c2 = Creature("The purple scare", std::list<Color>({Black}), false, std::list<Color>({Red, Blue}), 0, 2, 3);

	const Contender* ah = d.getContenders().at(0);

	const Contender* con1 = d.getContenders().at(0);
	const Contender* con2 = d.getContenders().at(1);


	const Card* c1Ptr = &c1;
	const Card* c2Ptr = &c2;
	const Contender* con1Ptr = con1;
	
	const std::list<const Card*> cList1 = std::list<const Card*>({c1Ptr, c2Ptr});


	inter.showText("showText works !!");
	
	
	cout << "\n\n";
	inter.ph1DrawnCard(con1Ptr, c1Ptr);
	cout << "\n";

	inter.ph2Disengage(con1Ptr, cList1);
	cout << "\n";
	
	const Card* picked1 =  inter.pickACard_option(cList1);
	if(picked1 != nullptr)
		cout << picked1<< endl;
	else
		cout << "No card picked\n";
	const Card* picked2 = inter.pickACard(cList1);


	inter.ph3PlayCards_wait(con1Ptr);

	
}
