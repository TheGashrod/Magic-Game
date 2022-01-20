#ifndef __MTG_INTERFACE_INTERFACE_INCLUDED__
#define __MTG_INTERFACE_INTERFACE_INCLUDED__




#include <string>
#include <list>


class Card;
class Contender;



class Interface_interface {

public:

	virtual void showText(std::string t) = 0;

	virtual void ph1DrawnCard(Card* c) = 0;
	virtual void ph2Disgendage(std::list<Card*> c) = 0;
	virtual void ph3PlayCards_wait(std::list<Card*> c, std::list<Card*> inGameLand) = 0;
	virtual void ph4Fight_wait(Contender att, Contender def) = 0;
	virtual void ph5PlayCards_wait(std::list<Card*> c, std::list<Card*> inGameLand) = 0;
	virtual void ph6Discard_wait(std::list<Card*> c, size_t nbToDiscard) = 0;

};





#endif
