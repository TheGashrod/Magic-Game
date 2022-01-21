#ifndef __MTG_CONSOLEINTERFACE_INCLUDED__
#define __MTG_CONSOLEINTERFACE_INCLUDED__



#include "../Interface.hpp"


#include "../Duel.hpp"



class ConsoleInterface : public Interface_interface {
	
	
	// Attributes :
	private:
		Duel i_duel;

	// Constructors :
	public:
		ConsoleInterface(Duel d);

	// Interface_interface :
	public:
		virtual void showText(std::string t);

		virtual void ph1DrawnCard(const Card* c);
		virtual void ph2Disengage(const std::list<Card*> c);
		virtual void ph3PlayCards_wait(std::list<Card*> c, std::list<Card*> inGameLand);
		virtual void ph4Fight_wait(Contender att, Contender def);
		virtual void ph5PlayCards_wait(std::list<Card*> c, std::list<Card*> inGameLand);
		virtual void ph6Discard_wait(std::list<Card*> c, size_t nbToDiscard);

	// Methods :
	private:
		Card* pickACard_option(std::list<Card*> cards) const;
		Card* pickACard(std::list<Card*> cards) const;




	// Friends :
	friend int testInterface();

};





#endif
