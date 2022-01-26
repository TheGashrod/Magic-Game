
#include "../headers/CardsSet.hpp"



#include "../headers/Creature.hpp"
#include "../headers/Land.hpp"


#include <stdexcept>
#include <vector>

using std::vector;


/* --------------------------------------------------------------------------------------------------/
                                         Constructors
/ --------------------------------------------------------------------------------------------------*/
CardsSet::CardsSet (vector<Card *> cardsSet) : c_cardsSet(cardsSet){};
CardsSet::~CardsSet(){};



/* --------------------------------------------------------------------------------------------------/
                                             Getters
/ --------------------------------------------------------------------------------------------------*/

vector<const Card*> CardsSet::getCardsSet() const { 
	vector<const Card*> cards = vector<const Card*>();
	for(auto c = c_cardsSet.begin(); c != c_cardsSet.end(); c++) {
		cards.push_back(*c);
	}
	return cards;
}

CardsSet CardsSet::getNotLands() const{
	vector<Card*> NotLands = vector<Card*>();
	for(auto c = c_cardsSet.begin(); c != c_cardsSet.end(); c++) {
		if( !(!(*c)->isLand())) {
			NotLands.push_back( (*c) );
		}
	}
	return NotLands;
}


CardsSet CardsSet::getDisengaged() const {
	vector<Card*> cards = vector<Card*>();
	for(auto c = c_cardsSet.begin(); c != c_cardsSet.end(); c++) {
		if( !(*c)->isEngaged() ) {
			cards.push_back( (*c) );
		}
	}
	return cards;
}


vector<Card*>* CardsSet::getOriginalCardsSet() { return & c_cardsSet; }


vector<const Creature*> CardsSet::getCreatures() const {
	vector<const Creature*> cards = vector<const Creature*>();
	for(Card* c : c_cardsSet) {
		if (Creature* card = dynamic_cast<Creature*>(c) ) {
        cards.push_back(card);
   	}
	}
	return cards;	
}


vector<const Land*> CardsSet::getLands() const {
	vector<const Land*> cards = vector<const Land*>();
	for(Card* c : c_cardsSet) {
		if (Land* card = dynamic_cast<Land*>(c) ) {
        cards.push_back(card);
   	}
	}
	return cards;	
}


std::vector<Creature*> CardsSet::getOriginalCreatures() {
	vector<Creature*> cards = vector<Creature*>();
	for(Card* c : c_cardsSet) {
		if ( Creature* card = dynamic_cast<Creature*>(c) ) {
        cards.push_back(card);
   	}
	}
	return cards;	
}


std::vector<Land*> CardsSet::getOriginalLands() {
	vector<Land*> cards = vector<Land*>();
	for(Card* c : c_cardsSet) {
		if ( Land* card = dynamic_cast<Land*>(c) ) {
        cards.push_back(card);
   	}
	}
	return cards;	
}



Card* CardsSet::getCardById(long id) {
	bool flag = false;
	for (int i = 0; i< int(c_cardsSet.size()); i++) {
		if ((c_cardsSet[i])->getId() == id)
			return c_cardsSet[i];
	}
	throw std::invalid_argument( "The given card doesn't exist on this cardsSet" );
}

/* --------------------------------------------------------------------------------------------------/
                                             Setters
/ --------------------------------------------------------------------------------------------------*/


void CardsSet::setCardsSet(vector<Card*> cardsSet) { c_cardsSet = cardsSet; }


/* --------------------------------------------------------------------------------------------------/
                                           Methods
/ --------------------------------------------------------------------------------------------------*/


void CardsSet::push(Card *c){
	c_cardsSet.push_back(c);
}


void CardsSet::transfer(const Card *c, CardsSet *cardsSetDestination){
	bool flag = false;
	for (int i = 0; i< int(c_cardsSet.size()); i++){
		if ((c_cardsSet[i])->hasSameId(c)){
			
			flag = true;
			cardsSetDestination->push(c_cardsSet[i]);
			c_cardsSet.erase (c_cardsSet.begin()+i);
			return;
		}
	}
	throw std::invalid_argument( "The given card doesn't exist on this cardsSet" );
}



ostream& CardsSet::print(ostream& os) const {
	os << "CARDSSET" << endl;
	
	cout << "CardsSet::print 1" << endl;
	for(auto c = c_cardsSet.begin(); c != c_cardsSet.end(); c++) {
		os << "| " << (*c) << endl;
	}
	cout << "CardsSet::print 3" << endl;
}



ostream& operator<<(ostream& os, const CardsSet cs) {
	return cs.print(os);
}