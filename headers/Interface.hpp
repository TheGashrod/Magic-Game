#ifndef __MTG_INTERFACE_INTERFACE_INCLUDED__
#define __MTG_INTERFACE_INTERFACE_INCLUDED__




#include <string>
#include <list>


class Duel;
class Card;
class Contender;



class Interface_interface {

	public:

		/**
		 * @brief Makes the interface print any text to the user
		 * 
		 * @param t text to print
		 */
		virtual void showText(std::string t) = 0;

		
		/**
		 * @brief Notifies the interface about a new drawn card
		 * 
		 * @param c 
		 */
		virtual void ph1DrawnCard(const Contender* con, const Card* card) = 0;

		/**
		 * @brief Notifies the interface about the player's cards getting disengaged
		 * 
		 * @param con the player
		 * @param c list of the just disengaged cards on the player's ground
		 */
		virtual void ph2Disengage(const Contender* con, const std::list<const Card*> c) = 0;

		/**
		 * @brief Tells the interface that Duel is waiting for a phase 3 card or nothing to be played
		 * Expects Duel::chooseCard or Duel::ph3_end to be called
		 * @param con the player able to play a card
		 */
		virtual void ph3PlayCards_wait(const Contender* con) = 0;

		/**
		 * @brief Tells the interface that Duel is waiting for a phase 4 pick of attack
		 * Expects Duel::ph4Fight or Duel::ph4_end to be called
		 * @param att the player able to attack
		 * @param def the victim player
		 */
		virtual void ph4Fight_wait(const Contender* att, const Contender* def) = 0;

		/**
		 * @brief Tells the interface that Duel is waiting for a phase 5 card or nothing to be played
		 * Expects Duel::chooseCard or Duel::ph3_end to be called
		 * @param con the player able to play a card
		 */
		virtual void ph5PlayCards_wait(const Contender* con) = 0;

		/**
		 * @brief Tells the interface that Duel is waiting for the player to pick cards to discard
		 * It happens when the player reaches the number of cards limit
		 * Expects Duel::ph6_end to be called
		 * @param con player supposed to discard cards
		 * @param nbToDiscard number of cards needing to be discarded
		 */
		virtual void ph6Discard_wait(const Contender* con, size_t nbToDiscard) = 0;

};





#endif
