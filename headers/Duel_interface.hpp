#ifndef __MTG_DUEL_INTERFACE_INCLUDED__
#define __MTG_DUEL_INTERFACE_INCLUDED__


#include <list>


class Card;
class Creature;
class Contender;


class Duel_interface {
	// Game phases and exchanges with interfaces
   public: virtual void start() = 0;
   protected: virtual void ph1Draw_start() = 0;
   protected: virtual void ph2Disengage_start() = 0;
   protected: virtual void ph3PlayCard_start() = 0;
   public: virtual void chooseCard(const Card* c) = 0;
   public: virtual void ph3_end() = 0;
   protected: virtual void ph4Fight_start() = 0;
   public: virtual void  ph4Fight(Creature att, Contender c, std::list<Creature> def) = 0;
   public: virtual void ph4_end() = 0;
   protected: virtual void ph5PlayCard_start() = 0;
   // chooseCard is called again here
   public: virtual void ph5_end() = 0;
   protected: virtual void ph6Discard_start() = 0;
   public: virtual void ph6_end(std::list<const Card*> discarded) = 0;

	void niceMethod();
};





#endif