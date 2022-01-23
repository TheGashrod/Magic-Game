
#include "../headers/CardsSet.hpp"


#include <stdexcept>
#include <vector>

using std::vector;


// Constructors :
CardsSet::CardsSet (vector<Card *> cardsSet) : c_cardsSet(cardsSet){};
CardsSet::~CardsSet(){};

// Getter & Setter :
vector<Card*> CardsSet::getCardsSet() const { return c_cardsSet;}
void CardsSet::setCardsSet(vector<Card*> cardsSet){c_cardsSet = cardsSet;}

// Methods :
void CardsSet::transfer(Card *c, CardsSet cardsSetDestination){
	bool flag = false;
	for (int i = 0; i< c_cardsSet.size(); i++){
		if ((c_cardsSet[i])->hasSameId(c)){
			flag = true;
			c_cardsSet.erase (c_cardsSet.begin()+i);
			cardsSetDestination.getCardsSet().push_back(c);
			break;
		}
		else{ continue;}
	}
	if (flag == false){ throw std::invalid_argument( "The given card doesn't exist on this cardsSet" ); }
}