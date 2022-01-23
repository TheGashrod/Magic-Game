#include "../headers/Duel.hpp"


#include <typeinfo>
#include <vector>
#include "../headers/tools/random.hpp"

#include "../headers/Interface.hpp"
#include "../headers/Contender.hpp"
#include "../headers/Card.hpp"
#include "../headers/Creature.hpp"
#include "../headers/Land.hpp"
#include "../headers/actions/FightHit.hpp"



using std::vector;
using std::size_t;


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



void Duel::showTextInInterfaces(string t) {
	for(auto inter=d_interfaces.begin(); inter != d_interfaces.end(); inter++) {
		Interface_interface* i = *inter;
		i->showText(t);
	}
}



/* --------------------------------------------------------------------------------------------------/
                 Game phases and exchanges with interfaces
/ --------------------------------------------------------------------------------------------------*/
void Duel::start() {

	
	// Picking the starting player
	size_t startId = randInt(d_contenders.size());
	d_currentContender = &(d_contenders.at(startId));
	
	showTextInInterfaces("The first player has been chosen randomly.");


	// Pick 7 cards randomly
	for(auto con = d_contenders.begin(); con != d_contenders.end(); con++) {
		Contender* c = &(*con);
		if(c->getLibrary().getCardsSet().size() < MAX_CARDS_AMOUNT) {
			gameOver(nullptr);
			return;
		}
		
		for(int i = 0; i < MAX_CARDS_AMOUNT; i++) {
			cout << "Drawing a card\n";
			c->drawCard(); // TODO To check
		}
	}

	// Starting first turn, skipping the 1st phase as mentioned in the rules
	ph2Disengage_start();
}




void Duel::ph1Draw_start() {
	d_currentPhase = 1;

	// TODO : Check whether the player has any card
	// TODO
}

void Duel::ph2Disengage_start() {
	d_currentPhase = 2;

	// Disengaging cards
	vector<Card*>* cards = d_currentContender->getInGameCards().getOriginalCardsSet();
	std::list<const Card*> disengaged = std::list<const Card*>();

	for(auto card=(*cards).begin(); card != (*cards).end(); card++) {
		Card* c = *card;
		if(c->isEngaged()) {
			c->disengage();
			const Card* cc = c;
			disengaged.push_back( cc );
		}
	}
	
	// Resetting right to set lands
	d_remainingLands = 1;

	// Notifying interfaces
	for(auto inter = d_interfaces.begin(); inter != d_interfaces.end(); inter++) {
		Interface_interface* i = *inter;
		i->ph2Disengage(d_currentContender , disengaged);
	}

	ph3PlayCard_start();
}




void Duel::ph3PlayCard_start() {
	d_currentPhase = 3;

	for(auto inter = d_interfaces.begin(); inter != d_interfaces.end(); inter++) {
		(*inter)->ph3PlayCards_wait(d_currentContender);
	}
	
	// TODO
}



/* Note : c cannot be nullptr, since ph3_end() is supposed to be called in these cases instead */
void Duel::chooseCard(const Card* c) {
	if( !(d_currentPhase == 3 || d_currentPhase == 5) ) {
		throw string("Duel::chooseCard has been called out of phase 3 or 5");
		return;
	}

	
	if(c->isLand()) {
		if(d_remainingLands > 0)
			throw string("[Error] Cannot add multiple lands to the game during the same turn");
		else
			d_remainingLands--;
	}

	// Effectively moving the card to the board
	d_currentContender->getOriginalHand()->transfer(c, d_currentContender->getOriginalInGameCards() );


	// Notifying interfaces again
	if(d_currentPhase == 3)
		for(auto inter = d_interfaces.begin(); inter != d_interfaces.end(); inter++)
			(*inter)->ph3PlayCards_wait(d_currentContender);
	else if(d_currentPhase == 5)
		for(auto inter = d_interfaces.begin(); inter != d_interfaces.end(); inter++)
			(*inter)->ph5PlayCards_wait(d_currentContender);
}




void Duel::ph3_end() {
	// TODO
}




void Duel::ph4Fight_start() {
	d_currentPhase = 4;
	// TODO
}




void Duel::ph4Fight(Creature att, Contender c, std::list<Creature> def) {
	// TODO
}




void Duel::ph4_end() {
	// TODO
}




void Duel::ph5PlayCard_start() {
	d_currentPhase = 5;
	// TODO
}




// chooseCard is called again here




void Duel::ph5_end() {
	// TODO
}




void Duel::ph6Discard_start() {
	d_currentPhase = 6;
	// TODO
}




void Duel::ph6_end(std::list<const Card*> discarded) {
	// TODO
}




void Duel::gameOver(Contender* winner) { //! winner can be nullptr if the game failed to begin
	if(winner == nullptr) {
		showTextInInterfaces("The game has been cancelled.");
		return;
	}
	// TODO
}
