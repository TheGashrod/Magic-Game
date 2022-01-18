

#include <vector>
#include "CardsSet.hpp"
#include "Player.hpp"


using std::vector;

class Contender {

	private :
		Player c_player;
		int c_vitality;
		CardsSet c_library;
		CardsSet c_cemetary;
		CardsSetc_hand;
		CardsSet c_inGameCards;


	
	public:

		// Constructors :
		Contender (Player p, int vita, vector<CardsSet> deck);
		~Contender();


		// Getters :
		int getVitality();
		CardsSet getLibrary();
		CardsSet getCemetary();
		CardsSet getHand();
		CardsSet getInGameCards();

		// Setters :
		void setVitality(int vita);

		// Methods :
		void drawCard();



		/**
		 * @brief Damages the player by a number of health points
		 * 
		 * @param hp damage
		 * @return int how much damage was actually dealt
		 */
		// int damageBy(stat hp);


 };