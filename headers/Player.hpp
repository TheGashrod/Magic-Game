#ifndef __MTG_PLAYER_INCLUDED__
#define __MTG_PLAYER_INCLUDED__


#include <string>
#include <vector>


#include "CardsSet.hpp"
#include <vector>

using std::vector;
using std::string;


class Card;



class Player {

	// Attributes :
	private:
		string p_username;
		CardsSet p_deck;

	
	// Constructor :
	public:
		Player(string username, CardsSet deck);
		~Player();
	

	// --------------- Getters/setters ---------------
	public:
		CardsSet getDeck() const;
		string getName() const;

		void setName(string name);

		
		
		/**
		 * @brief Adds a copy of c to the player's deck
		 * Also checks whether a card with the same ID is already in the game
		 * @param c the new card
		 */
		void addCardToDeck(Card* c);
		/**
		 * @brief Removes one card from the player's deck based on its ID
		 * 
		 * @param c The card to remove
		 * @return true if the card was found and removed
		 * @return false if the card was not found
		 */
		bool removeFromDeck(Card* c);

};






#endif