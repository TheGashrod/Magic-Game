

#include "../headers/Contender.hpp"
#include "../headers/CardsSet.hpp"
#include "../headers/Card.hpp"

#include <vector>

using std::vector;


Contender::Contender (Player p, int vita, CardsSet deck):
	c_player(p), c_vitality(vita), c_library(deck), c_cemetary({}), c_inGameCards({}), c_hand({}) { }
Contender::~Contender() { };



// Getters :
int Contender::getVitality() const { return c_vitality; }
CardsSet Contender::getLibrary() const { return c_library; }
CardsSet Contender::getCemetary() const { return c_cemetary; }
CardsSet Contender::getHand() const { return c_hand; }
CardsSet Contender::getInGameCards() const { return c_inGameCards; }

// Setter :
void Contender::setVitality(int vita) { c_vitality = vita; }

// Methods :
	// methode transfer à faire dans CardsSet
void Contender::drawCard(){
	c_library.CardsSet::transfer(c_library.getCardsSet()[0], c_hand);
};

