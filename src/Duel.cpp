#include "../headers/Duel.hpp"


#include <typeinfo>
#include <vector>
#include "../headers/tools/random.hpp"

#include "../headers/Interface.hpp"
#include "../headers/Contender.hpp"
#include "../headers/Card.hpp"
#include "../headers/Creature.hpp"
#include "../headers/Land.hpp"



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


const Contender* Duel::getOtherContender() const {
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

	// Starting first turn, skipping the 1st phase as mentioned in the rules
	ph2Disengage_start();
}




void Duel::ph1Draw_start() {
	d_currentPhase = 1;

	if ((d_currentContender->getOriginalLibrary()->getOriginalCardsSet())->size() == 0 ){gameOver(nullptr);}
	else{ const Card * c = d_currentContender->drawCard();

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
		cout << "Boucle ph2Disengage 1" << endl;
		Card* c = *card;
		cout << "Boucle ph2Disengage 2" << endl;
		if(c->isEngaged()) {
			cout << "Boucle ph2Disengage 2.1" << endl;
			c->disengage();
			cout << "Boucle ph2Disengage 2.2" << endl;
			//cout << "Value of c : " << *card << endl;
			//cout << "Value of c : " << c << endl;
			const Card* cc = *card;
			cout << "Boucle ph2Disengage 2.3" << endl;
			disengaged.push_back( *card );
			cout << "Boucle ph2Disengage 2.4" << endl;
			*disengaged.begin();
			cout << "Boucle ph2Disengage 2.5" << endl;
			(*disengaged.begin())->isEngaged();
			cout << "Boucle ph2Disengage 2.6" << endl;
			//(*disengaged.begin())->print(cout);
			cout << "Boucle ph2Disengage 2.7" << ", Size of disengaged : " << disengaged.size() << endl;
			cout << *disengaged.begin() << endl;
			cout << "Boucle ph2Disengage 2.8" << endl;
		}
	}
	cout << "Boucle ph2Disengage 3" << endl;
	
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

	for(Interface_interface* interface : d_interfaces) {
		interface->ph4Fight_wait(d_currentContender, getOtherContender());
	}
}




void Duel::ph4Fight(const Creature* att, std::vector<const Creature*> def) {
	if(d_currentPhase != 4) { 
		throw string("Duel::ph4Fight has been called out of phase 4");
		return;
	}
	// TODO
}




void Duel::ph4_end() {
	if(d_currentPhase != 4) { 
		throw string("Duel::end has been called out of phase 4");
		return;
	}
	// TODO
}




void Duel::ph5PlayCard_start() {
	d_currentPhase = 5;
	// TODO
}




// chooseCard is called again here




void Duel::ph5_end() {
	if(d_currentPhase != 5) { 
		throw string("Duel::ph5_end has been called out of phase 5");
		return;
	}
	// TODO
}


void Duel::ph6Discard_start() {
	d_currentPhase = 6;
	// TODO verif que le jour à moins de 7 cartes sinon calculer cmb il a en plus, l'envoyer à l'interface...
	// puis passer à phase6end depuis l'interface
	int n = (d_currentContender->getOriginalHand()->getOriginalCardsSet())->size();
	if (n>7){
		for(auto inter = d_interfaces.begin(); inter != d_interfaces.end(); inter++) {
			(*inter)->ph6Discard_wait(d_currentContender, (n-7));
		}
	}else{ph6_end({});}
}




void Duel::ph6_end(std::vector<const Card*> discarded) {
	if(d_currentPhase != 6) { 
		throw string("Duel::ph6_end has been called out of phase 6");
		return;
	}

	// Transfer the discarded cards to the cimetery
	for (int i=0; i<discarded.size(); i++){
		d_currentContender->getOriginalHand()->transfer(discarded[0], d_currentContender->getOriginalCemetary());
	}
	


	// Check if the Current contender still have some remaining turns and give the Other contender the hand to play if not
	if((getRemainingTurns()-1) > 0){
		setRemainingTurns(getRemainingTurns()-1);
		ph1Draw_start();
	}else{ 
		for(auto con = d_contenders.begin(); con != d_contenders.end(); con++) {
			if(&(*con) != d_currentContender) {
				d_currentContender = &(*con);
			}
		}
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
	// TODO
}
