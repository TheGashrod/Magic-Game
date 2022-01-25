#include "../../headers/test/testConsoleInterface.hpp"

#include <iostream>
#include <list>
#include <memory>


#include "../../headers/consoleInterface/ConsoleInterface.hpp"
#include "../../headers/Contender.hpp"
#include "../../headers/Creature.hpp"
#include "../../headers/Land.hpp"
#include "../../headers/Duel.hpp"



using std::cout;


Card* ca(Creature c) {
	return &c;
}
Card* ca(Land a) {
	return &a;
}



int mainTest() {

	
	

	Creature c1 = Creature("Démon de Pagaille", std::list<Color>({Blue, Red}), false, std::list<Color>({Red, Red}), 1, 3, 3);
	Creature c2 = Creature("The purple scare", std::list<Color>({White}), false, std::list<Color>({Black, Red, Black}), 0, 2, 3);

	

	Land la1 = Land("Terres désolées", Red, false);
	Land la12 = Land(la1);
	Land la2 = Land("Une boîte noire", Black, false);

	auto a =  la1.clone();

	if(c1.isFittingCosts( vector<Land>({la1, la1.duplicateLand()}), vector<Land>({la1.cloneLand()}) ) != false)
		cout << "ERROR_MTG : isFittingCosts with c1;<[la1, la1'], la1> test should be false because the same element is input twice" << endl;

	if(c1.isFittingCosts( vector<Land>({la1, la1.cloneLand()}), vector<Land>({la1.cloneLand()}) ) != true)
		cout << "ERROR_MTG : isFittingCosts with c1;<[la1, la1'], la1''> test should be true" << endl;
	
	if(c2.isFittingCosts( vector<Land>({la1, la1.cloneLand(), la1.cloneLand()}), vector<Land>({}) ) != false)
		cout << "ERROR_MTG : isFittingCosts with c2;<[la1, la1', la1''], []> test should be false because unmatching colors" << endl;
	
	if(c2.isFittingCosts( vector<Land>({la1, la2.cloneLand(), la2}), vector<Land>({}) ) != true)
		cout << "ERROR_MTG : isFittingCosts with c2;<[la1, la2', la2], []> test should be true" << endl;
	
	

	cout << "Color creature : " << *c1.getColorCost().begin() << endl;
	cout << "Color land : " << *la1.getColor().begin() << endl;


	cout << la1 << endl;
	

	shared_ptr<Card> c1clone = c1.clone();
	cout << "ID of c1 :  " << c1.getId() << " ; ID of c1Clone : " << (*c1clone).getId() << endl;

	

	shared_ptr<Card> la1clone = la1.clone();
	cout << "ID of la1 : "  << la1.getId() << " ; ID of laClone : " << (*la1clone).getId() << endl;

	

	Card* c1Ptr2 = &c1;
	const Card* c1Ptr = &c1;
	Card* c2Ptr2 = &c2;
	const Card* c2Ptr = &c2;
	
	const std::list<const Card*> cList1 = std::list<const Card*>({c1Ptr, c2Ptr, c1Ptr, c1Ptr, c1Ptr, c1Ptr, c1Ptr, c1Ptr, c1Ptr, c1Ptr, c1Ptr});

	cout << c1Ptr << endl;



	Player p1 = Player("J1", CardsSet(std::vector<Card*>({c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2, c1Ptr2})));
	Player p2 = Player("J2", CardsSet(std::vector<Card*>({c2Ptr2, c2Ptr2, c2Ptr2, c2Ptr2, c2Ptr2, c2Ptr2, c2Ptr2, c2Ptr2, c2Ptr2})));
	Player p3 = Player("J3", CardsSet(std::vector<Card*>({ca(la1), ca(la1), ca(la1), &la2, &la2, &la2, &la2, &la2, &la2, &c1, &c1, c1Ptr2, c1Ptr2, c2Ptr2, c2Ptr2, c2Ptr2, c2Ptr2})));

	Duel d = Duel(p1, p2);
	ConsoleInterface inter = ConsoleInterface(&d);


	inter.pickALand_option( p3.getDeck().getLands() );
	//inter.pickACreature( p3.getDeck().getCreatures() );


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

	//d.start();
	//d.ph1Draw_start();
	//d.ph6Discard_start();

	
}
