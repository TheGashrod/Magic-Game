

#include "../headers/Contender.hpp"
#include "../headers/CardsSet.hpp"
#include "../headers/Card.hpp"

#include <vector>
#include "../headers/tools/random.hpp"

using std::vector;


// Constructors

Contender::Contender (Player p, int vita, CardsSet deck):
	c_player(p), c_vitality(vita), c_library({}), c_cemetary({}), c_inGameCards({}), c_hand({})
{
	cout << "Contender constructor 1" << endl;
	vector<Card*> newCards = vector<Card*>();
	cout << "Contender constructor 1.2" << endl;
	cout << deck << endl;
	for(auto card = deck.getOriginalCardsSet()->begin() ; card != deck.getOriginalCardsSet()->end(); card++) {
		cout << "Contender constructor 1.3" << endl;
		shared_ptr<Card> cPtr = (*card)->clone();
		cout << "Contender constructor 1.4" << endl;
		c_cards.push_back( cPtr );
		newCards.push_back( c_cards.at(c_cards.size()-1).get() );
		//newCards.push_back( cPtr.get() );
	}
	cout << "Contender constructor 2" << endl;
	//c_library = CardsSet(std::vector<Card*>()); //TODO
	CardsSet cs = CardsSet(newCards);
	cout << cs << endl;
	c_library = cs;
	cout << "Contender constructor 3" << endl;
}


Contender::~Contender() { };



// Getters :
Player Contender::getPlayer() const { return c_player; }
int Contender::getVitality() const { return c_vitality; }
CardsSet Contender::getLibrary() const { return c_library; }
CardsSet Contender::getCemetary() const { return c_cemetary; }
CardsSet Contender::getHand() const { return c_hand; }
CardsSet Contender::getInGameCards() const { return c_inGameCards; }
CardsSet* Contender::getOriginalLibrary() { return &c_library; }
CardsSet* Contender::getOriginalCemetary() { return &c_cemetary; }
CardsSet* Contender::getOriginalHand() { return &c_hand; }
CardsSet* Contender::getOriginalInGameCards() { return &c_inGameCards; }

// Setter :
void Contender::setVitality(int vita) { c_vitality = vita; }
int Contender::damageBy(stat hp) { c_vitality = std::max(0, c_vitality - hp); }


// Methods :
const Card * Contender::drawCard() {
	const Card * c = c_library.getOriginalCardsSet()->at( randInt(c_library.getOriginalCardsSet()->size()) );
	c_library.transfer( c, & c_hand);
	return c;
};

