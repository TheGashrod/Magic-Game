#include "../../headers/test/testConsoleInterface.hpp"

#include <iostream>
#include <list>
#include <memory>


#include "../../headers/consoleInterface/ConsoleInterface.hpp"
#include "../../headers/Contender.hpp"
#include "../../headers/Creature.hpp"
#include "../../headers/Duel.hpp"


int mainTest() {

	


	Creature c1 = Creature("Démon de Pagaille", std::list<Color>({Blue, Red}), false, std::list<Color>({Red, Red}), 1, 3, 3);
	Creature c2 = Creature("The purple scare", std::list<Color>({Black}), false, std::list<Color>({Red, Blue}), 0, 2, 3);

	shared_ptr<Card> c1clone = c1.clone();
	cout << "ID of c1 :  " << c1.getId() << " ; ID of c1Clone : " << (*c1clone).getId() << endl;


	Card* c1Ptr2 = &c1;
	const Card* c1Ptr = &c1;
	Card* c2Ptr2 = &c2;
	const Card* c2Ptr = &c2;
	
	const std::list<const Card*> cList1 = std::list<const Card*>({c1Ptr, c2Ptr, c1Ptr, c1Ptr, c1Ptr, c1Ptr, c1Ptr, c1Ptr, c1Ptr, c1Ptr, c1Ptr});



	Player p1 = Player("J1", CardsSet(std::vector<Card*>({c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2})));
	Player p2 = Player("J2", CardsSet(std::vector<Card*>({c2Ptr2, c2Ptr2, c2Ptr2, c2Ptr2, c2Ptr2, c2Ptr2, c2Ptr2, c2Ptr2, c2Ptr2})));

	Duel d = Duel(p1, p2);
	ConsoleInterface inter = ConsoleInterface(&d);


	const Contender* con1 = d.getContenders().at(0);
	const Contender* con2 = d.getContenders().at(1);

	
	const Contender* con1Ptr = con1;

	CardsSet l1 = CardsSet(std::vector<Card*>({c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2}));
	CardsSet l2 = CardsSet(std::vector<Card*>({}));

	std::cout << l1.getOriginalCardsSet()->size();

	std::cout << l2.getOriginalCardsSet()->size();

	//l1.transfer(c1Ptr2, & l2);

	std::cout << l1.getOriginalCardsSet()->size();

	std::cout << l2.getOriginalCardsSet()->size();


	inter.showText("showText works !!");
	
	
	/*
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
	*/

	d.showTextInInterfaces("showTextInInterfaces works too !\n");

	cout << "Other player : " << d.getOtherContender()->getPlayer().getName() << endl;

	d.start();

	
}
