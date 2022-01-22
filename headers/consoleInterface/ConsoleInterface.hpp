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

		virtual void ph1DrawnCard(const Contender* con, const Card* card);
		virtual void ph2Disengage(const Contender* con, const std::list<const Card*> c);
		virtual void ph3PlayCards_wait(const Contender* con);
		virtual void ph4Fight_wait(const Contender* att, const Contender* def);
		virtual void ph5PlayCards_wait(const Contender* con);
		virtual void ph6Discard_wait(const Contender* con, size_t nbToDiscard);

	// Methods :
	private:
		const Card* pickACard_option(std::list<const Card*> cards) const;
		const Card* pickACard(std::list<const Card*> cards) const;




	// Friends :
	friend int testInterface();

};





#endif
