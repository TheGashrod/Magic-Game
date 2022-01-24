#ifndef __MTG_CARDSSET_INCLUDED__
#define __MTG_CARDSSET_INCLUDED__



#include <vector>
#include <iostream>


#include "../headers/Card.hpp"
class Creature;
class Land;


using std::vector;


class CardsSet {

	private:
		vector<Card* > c_cardsSet;

	public:

		// Constructors :
		CardsSet (vector<Card*> cardsSet);
		~CardsSet();

		// Getter & Setter :
		vector<const Card*> getCardsSet() const;
		void setCardsSet(vector<Card* > cardsSet);
		CardsSet getDisengaged() const;
		std::vector<const Creature*> getCreatures() const;
		std::vector<const Land*> getLands() const;
		std::vector<Creature*> getOriginalCreatures();
		std::vector<Land*> getOriginalLands();
		vector<Card*>* getOriginalCardsSet();
		Card* getCardById(long id);
		

		// Methods :
		void push(Card *c);
		void transfer(const Card *c, CardsSet *cardsSetDestination);
		ostream& print(ostream& os) const;

};


ostream& operator<<(ostream& os, const CardsSet cs);



#endif