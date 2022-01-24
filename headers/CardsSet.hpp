#ifndef __MTG_CARDSSET_INCLUDED__
#define __MTG_CARDSSET_INCLUDED__



#include "../headers/Card.hpp"
class Creature;
class Land;


#include <vector>

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
		std::vector<const Creature*> getCreatures() const;
		std::vector<const Land*> getLands() const;
		std::vector<Creature*> getOriginalCreatures();
		std::vector<Land*> getOriginalLands();

		vector<Card*> * getOriginalCardsSet();
		

		// Methods :
		void push(Card *c);
		void transfer(const Card *c, CardsSet *cardsSetDestination);








};



#endif