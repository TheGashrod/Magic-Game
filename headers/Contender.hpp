#ifndef __MTG_CONTENDER_INCLUDED__
#define __MTG_CONTENDER_INCLUDED__




#include "Card.hpp"
#include "CardsSet.hpp"
#include "Player.hpp"



typedef unsigned char stat;


class Contender {

	private :
		Player c_player;
		int c_vitality;
		CardsSet c_library;
		CardsSet c_cemetary;
		CardsSet c_hand;
		CardsSet c_inGameCards;


	
	public:

		// Constructors :
		Contender (Player p, int vita, CardsSet deck);
		~Contender();


		// Getters :
		Player getPlayer() const;
		int getVitality() const;
		CardsSet getLibrary() const;
		CardsSet getCemetary() const;
		CardsSet getHand() const;
		CardsSet getInGameCards() const;
		CardsSet* getOriginalLibrary();
		CardsSet* getOriginalCemetary();
		CardsSet* getOriginalHand();
		CardsSet* getOriginalInGameCards();
		

		// Setters :
		void setVitality(int vita);

		// Methods :
		const Card * drawCard();



		/**
		 * @brief Damages the player by a number of health points
		 * 
		 * @param hp damage
		 * @return int how much damage was actually dealt
		 */
		int damageBy(stat hp);


 };



 #endif