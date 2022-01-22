#include "../headers/Duel.hpp"


#include <vector>


#include "../headers/Interface.hpp"
#include "../headers/Contender.hpp"
#include "../headers/Card.hpp"
#include "../headers/Creature.hpp"
#include "../headers/actions/FightHit.hpp"



using std::vector;


/* --------------------------------------------------------------------------------------------------/
                                        Constructeurs
/ --------------------------------------------------------------------------------------------------*/



Duel::Duel(Player player1, Player player2) {
	Contender c1 = Contender(player1, 20, player1.getDeck());
	Contender c2 = Contender(player2, 20, player2.getDeck());
	d_contenders.push_back(c1);
	d_contenders.push_back(c2);
}


/* --------------------------------------------------------------------------------------------------/
                                        Getters/setters
/ --------------------------------------------------------------------------------------------------*/


const vector<const Contender*> Duel::getContenders() const {
	vector<const Contender*> contenders = vector<const Contender*>();
	
	for(auto i=d_contenders.begin(); i != d_contenders.end(); i++) {
		const Contender* c = &(*i);
		contenders.push_back(c);
	}
	return contenders;
}


void Duel::addInterface(Interface_interface* i) {
	d_interfaces.push_back(i);
}





/* --------------------------------------------------------------------------------------------------/
                 Game phases and exchanges with interfaces
/ --------------------------------------------------------------------------------------------------*/
void Duel::start() {
	// TODO
}

void Duel::ph1Draw_start() {
	// TODO
}

void Duel::ph2Disgendage_start() {
	// TODO
}

void Duel::ph3PlayCard_start() { 
	// TODO
}

void Duel::chooseCard(const Card* c) { //! Beware of the fact c can be nullptr
	cout << "Received card in Duel : " << c << "\n";
	// TODO
}

void Duel::ph3_end() {
	// TODO
}

void Duel::ph4Fight_start() {
	// TODO
}

void Duel::ph4Fight(Creature att, Contender c, std::list<Creature> def) {
	// TODO
}

void Duel::ph4_end() {
	// TODO
}

void Duel::ph5PlayCard_start() {
	// TODO
}

// chooseCard is called again here

void Duel::ph5_end() {
	// TODO
}

void Duel::ph6Discard_start() {
	// TODO
}

void Duel::ph6_end(std::list<const Card*> discarded) {
	// TODO
}
