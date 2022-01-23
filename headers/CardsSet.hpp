#ifndef __MTG_CARDSSET_INCLUDED__
#define __MTG_CARDSSET_INCLUDED__



#include "../headers/Card.hpp"

#include <vector>

using std::vector;


class CardsSet {

	private:
		vector<Card *> c_cardsSet;

	public:

		// Constructors :
		CardsSet (vector<Card*> cardsSet);
		~CardsSet();

		// Getter & Setter :
		const vector<Card*> getCardsSet() const;
		void setCardsSet(vector<Card* > cardsSet);

		vector<Card*>* getCardsSet();
		

		// Methods :
		void transfer(Card *c, CardsSet  cardsSetDestination);







};



#endif