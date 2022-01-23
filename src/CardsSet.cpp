
#include "../headers/CardsSet.hpp"


#include <stdexcept>
#include <vector>

using std::vector;


// Constructors :
CardsSet::CardsSet (vector<Card *> cardsSet) : c_cardsSet(cardsSet){};
CardsSet::~CardsSet(){};


// Getter & Setter :
vector<const Card*> CardsSet::getCardsSet() const { 
	vector<const Card*> cards = vector<const Card*>();
	for(auto c = c_cardsSet.begin(); c != c_cardsSet.end(); c++) {
		cards.push_back(*c);
	}
	return cards;
}
void CardsSet::setCardsSet(vector<Card*> cardsSet){c_cardsSet = cardsSet;}

vector<Card*>* CardsSet::getOriginalCardsSet() { return & c_cardsSet; }


// Methods :


void CardsSet::push(Card *c){
	c_cardsSet.push_back(c);
}


void CardsSet::transfer(const Card *c, CardsSet *cardsSetDestination){
	bool flag = false;
	for (int i = 0; i< int(c_cardsSet.size()); i++){
		if ((c_cardsSet[i])->hasSameId(c)){
			
    	cout << "Même ID" << "\n";
			flag = true;
			cardsSetDestination->push(c_cardsSet[i]);
			c_cardsSet.erase (c_cardsSet.begin()+i);
			break;
		}
		else{ continue;}
	}
	if (flag == false){ throw std::invalid_argument( "The given card doesn't exist on this cardsSet" ); }
}

