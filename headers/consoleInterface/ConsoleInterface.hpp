#ifndef __MTG_CONSOLEINTERFACE_INCLUDED__
#define __MTG_CONSOLEINTERFACE_INCLUDED__



#include "../Interface.hpp"






class ConsoleInterface : public Interface_interface {

    virtual void showText(std::string t);

	virtual void ph1DrawnCard(Card c);
	virtual void ph2Disgendage(std::list<Card> c);
	virtual void ph3PlayCards_wait(std::list<Card> c, std::list<Card> inGameLand);
	virtual void ph4Fight_wait(Contender att, Contender def);
	virtual void ph5PlayCards_wait(std::list<Card> c, std::list<Card> inGameLand);
	virtual void ph6Discard_wait(std::list<Card> c, size_t nbToDiscard);

};





#endif
