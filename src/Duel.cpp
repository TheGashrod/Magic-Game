#include "../headers/Duel.hpp"


#include <typeinfo>
#include <vector>
#include <iostream>
#include "../headers/tools/random.hpp"

#include "../headers/Interface.hpp"
#include "../headers/Contender.hpp"
#include "../headers/Card.hpp"
#include "../headers/Creature.hpp"
#include "../headers/Land.hpp"
#include "../headers/AttackRound.hpp"
#include "../headers/AttackAction.hpp"


using std::cout;

using std::vector;
using std::size_t;


/* --------------------------------------------------------------------------------------------------/
                                          Constructors
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


unsigned char Duel::getRemainingTurns() const{ return d_remainingTurns;}

void Duel::setRemainingTurns(unsigned char nb){
	d_remainingTurns = nb;
}


Contender* Duel::getOtherContender() {
	for(auto con = d_contenders.begin(); con != d_contenders.end(); con++) {
		if(&(*con) != d_currentContender) {
			return &(*con);
		}
	}
	throw string("No other Contender found in Duel instance");
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

void Duel::contenderGameVision(Contender* currentContender){
	
	// for(int i=0; i<contenders.size(); i++) {
	// 	if(&contenders[i] == &currentContender){
	// 	}else{
	// 		cout << " My opposent in game's cards " << contenders[i]->getOriginalInGameCards()->getOriginalCardsSet()<< endl;
	// 	}
	// }

	cout << " My opposent in game's cards " << *getOtherContender()->getOriginalInGameCards() << endl;


	cout << " My in game's cards "<< *currentContender->getOriginalInGameCards() << endl;
	

	cout << " My hand's cards " << *currentContender->getOriginalHand() << endl;
}



/* --------------------------------------------------------------------------------------------------/
                 Game phases and exchanges with interfaces
/ --------------------------------------------------------------------------------------------------*/
void Duel::start() {
	if(d_currentPhase != 0) { 
		throw string("Duel::start has been called while the game was already started");
		return;
	}

	
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
			c->drawCard();
		}
	}

	contenderGameVision(d_currentContender);

	// Starting first turn, skipping the 1st phase as mentioned in the rules
	ph2Disengage_start();
}




void Duel::ph1Draw_start() {
	d_currentPhase = 1;

	// Test whether the player has remaining cards
	if ((d_currentContender->getOriginalLibrary()->getOriginalCardsSet())->size() == 0 ) {
		for(auto inter=d_interfaces.begin(); inter != d_interfaces.end(); inter++) {
			(*inter)->showText("\nThis player doesn't have any remaining card and cannot draw.");
		}
		gameOver( getOtherContender() );
	}

	// Picking a card
	else{
		const Card * c = d_currentContender->drawCard();

		// Notifying interfaces
		for(auto inter = d_interfaces.begin(); inter != d_interfaces.end(); inter++) {
			Interface_interface* i = *inter;
			i->ph1DrawnCard(d_currentContender, c);
		}

		ph2Disengage_start();
	}
}

void Duel::ph2Disengage_start() {
	d_currentPhase = 2;

	// Disengaging cards
	vector<Card*>* cards = d_currentContender->getOriginalInGameCards()->getOriginalCardsSet();
	std::list<const Card*> disengaged = std::list<const Card*>();

	for(auto card=(*cards).begin(); card != (*cards).end(); card++) {
		Card* c = *card;
		if(c->isEngaged()) {
			c->disengage();
			disengaged.push_back( *card );
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
}




/* Note : c cannot be nullptr, since ph3_end() is supposed to be called in these cases instead */
void Duel::chooseCard(const Card* c) {
	if( !(d_currentPhase == 3 || d_currentPhase == 5) ) {
		throw string("Duel::chooseCard has been called out of phase 3 or 5");
		return;
	}


	// TODO : Check cost in interface
	// TODO : Check number of lands in interface
	
	if(c->isLand()) {
		if(d_remainingLands > 0)
			throw string("[Error] Cannot add multiple lands to the game during the same turn");
		else
			d_remainingLands--;
	}

	// Effectively moving the card to the board
	d_currentContender->getOriginalHand()->transfer(c, d_currentContender->getOriginalInGameCards() );
	d_currentContender->getOriginalInGameCards()->getCardById(c->getId())->engage();


	// Notifying interfaces again
	if(d_currentPhase == 3)
		for(auto inter = d_interfaces.begin(); inter != d_interfaces.end(); inter++)
			(*inter)->ph3PlayCards_wait(d_currentContender);
	else if(d_currentPhase == 5)
		for(auto inter = d_interfaces.begin(); inter != d_interfaces.end(); inter++)
			(*inter)->ph5PlayCards_wait(d_currentContender);
}




void Duel::ph3_end() {
	if(d_currentPhase != 3) { 
		throw string("Duel::ph3_end has been called out of phase 3");
		return;
	}
	ph4Fight_start();
}




void Duel::ph4Fight_start() {
	d_currentPhase = 4;
	cout << "Beginning phase 4" << endl;

	for(Interface_interface* interface : d_interfaces) {
		interface->ph4Fight_wait(d_currentContender, getOtherContender());
	}
}




void Duel::ph4Fight(const Creature* att, std::vector<const Creature*> def) {
	if(d_currentPhase != 4) { 
		throw string("Duel::ph4Fight has been called out of phase 4");
		return;
	}

	cout << "Before building AttackRound" << endl;

	// Building AttackRound
	AttackRound ar = AttackRound();
	Creature* c;
	if (c = dynamic_cast<Creature*>( d_currentContender->getOriginalInGameCards()->getCardById(att->getId()) )) {
		AttackAction aa = AttackAction(d_currentContender, getOtherContender(), c );
		for(auto defen = def.begin(); defen != def.end(); defen++) {
			if (c = dynamic_cast<Creature*>( getOtherContender()->getOriginalInGameCards()->getCardById((*defen)->getId()) )) {
				aa.addFightCreature( FightCreature(c, false) );
			}
		}
		ar.addAttack(aa);
	}


	// TODO : Take abilities into account


	// Executing AttackRound
	cout << "Before executing attack " << endl;
	ar.execute();

	cout << "After executing attack" << endl;

	// Check if a player has died
	if( d_currentContender->getVitality() <= 0 ) {
		gameOver( getOtherContender() );
		return;
	}
	else if( getOtherContender()->getVitality() <= 0 ) {
		gameOver( d_currentContender );
		return;
	}


	// Notifying interfaces
	for(Interface_interface* interface : d_interfaces) {
		interface->ph4Fight_wait(d_currentContender, getOtherContender());
	}
}




void Duel::ph4_end() {
	if(d_currentPhase != 4) { 
		throw string("Duel::end has been called out of phase 4");
		return;
	}
	
	ph5PlayCard_start();
}




void Duel::ph5PlayCard_start() {
	d_currentPhase = 5;
	cout << "Beginning phase 5" << endl;
	
	for(auto inter = d_interfaces.begin(); inter != d_interfaces.end(); inter++) {
		(*inter)->ph5PlayCards_wait(d_currentContender);
	}
}




// chooseCard is called again here




void Duel::ph5_end() {
	if(d_currentPhase != 5) { 
		throw string("Duel::ph5_end has been called out of phase 5");
		return;
	}
	
	ph6Discard_start();
}


void Duel::ph6Discard_start() {
	d_currentPhase = 6;
	cout << "Beginning phase 6" << endl;

	// Verif que le jour à moins de 7 cartes sinon calculer cmb il a en plus, l'envoyer à l'interface...
	// puis passer à phase6end depuis l'interface
	int n = (d_currentContender->getOriginalHand()->getOriginalCardsSet())->size();
	if (n>MAX_CARDS_AMOUNT){
		for(auto inter = d_interfaces.begin(); inter != d_interfaces.end(); inter++) {
			(*inter)->ph6Discard_wait(d_currentContender, (n-MAX_CARDS_AMOUNT));
		}
	}else{ph6_end({});}
}




void Duel::ph6_end(std::vector<const Card*> discarded) {
	if(d_currentPhase != 6) { 
		throw string("Duel::ph6_end has been called out of phase 6");
		return;
	}


	// Check whether the interface has discarded enough cards
	if(discarded.size() > 0) {
		size_t newSize = d_currentContender->getHand().getCardsSet().size() - discarded.size();
		if(newSize < MAX_CARDS_AMOUNT) {
			throw string("An interface has given an excessive number of cards to discard");
		}
		else if(newSize > MAX_CARDS_AMOUNT) {
			for(auto inter = d_interfaces.begin(); inter != d_interfaces.end(); inter++) {
				(*inter)->ph6Discard_wait(d_currentContender, newSize-MAX_CARDS_AMOUNT);
			}
			return;
		}
	}
	

	// Transfer the discarded cards to the cemetery
	for(auto dis = discarded.begin(); dis != discarded.end(); dis++) {
		d_currentContender->getOriginalHand()->transfer( *dis, d_currentContender->getOriginalCemetary() );
	}


	// Check if the Current contender still have some remaining turns and give the Other contender the hand to play if not
	if((getRemainingTurns()-1) > 0){
		setRemainingTurns(getRemainingTurns()-1);
		ph1Draw_start();
	}
	else {
		d_currentContender = getOtherContender();
		ph1Draw_start();
	}

}



/* --------------------------------------------------------------------------------------------------/
                                         Other methods
/ --------------------------------------------------------------------------------------------------*/


void Duel::gameOver(Contender* winner) { //! winner can be nullptr if the game failed to begin
	if(winner == nullptr) {
		showTextInInterfaces("The game has been cancelled.");
		return;
	}

	showTextInInterfaces("\nEND OF THE GAME");
	showTextInInterfaces("Winner : ");
	showTextInInterfaces(winner->getPlayer().getName());
	// TODO
}
