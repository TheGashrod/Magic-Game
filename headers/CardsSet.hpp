
#include "Card.hpp"

#include <vector>

using std::vector;

CardsSet
class CardsSet {

	private:
		vector<Card> c_cardsSet;

	public:

		// Constructors :
		CardsSet (vector<Card> cardsSet);
		~CardsSet();

		// Getter & Setter :
		vector<Card> getCardsSet();
		void setCardsSet(vector<Card> cardsSet);


		// Methods :
		void transfer(Card c, CardsSet cardsSetDestination);







};
