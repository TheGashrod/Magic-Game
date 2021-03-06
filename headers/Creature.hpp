#ifndef __MTG_CREATURE_INCLUDED__
#define __MTG_CREATURE_INCLUDED__


#include <list>
#include <tuple>
#include <vector>


#include "Card.hpp"



class Contender;
class Land;


typedef unsigned char stat;
class Creature : public Card {

	// Members :
	private :
		std::tuple<int, std::list<Color>> c_cost;
		stat c_power;
		stat c_powerDef;
		stat c_toughness;
		stat c_toughnessDef;

	//Constructors :
	public:
		Creature (string name, std::list<Color> colors, bool isEngaged,
			std::list<Color> colorCost, int anyCost,
			stat powerDefault, stat toughness);

		~Creature();

		virtual shared_ptr<Card> clone() const;


	// Getters/setters
	public:
		std::tuple<int, std::list<Color>> getCost() const;
		/**
		 * @brief Get the Color cost of a creature
		 *
		 * @return std::list<Color> one colour per defined necessary land to invoke
		 */
		std::list<Color> getColorCost() const;
		/**
		 * @brief Get the remaining cost of a creature, that can be any ground
		 *
		 * @return int the number of necessary grounds
		 */
		int getAnyCost() const;
		stat getPower() const;
		stat getPowerDefault() const;
		stat getToughness() const;
		stat getToughnessDefault() const;
		bool isAlive() const;

		void setPowerDefault(stat val);
		void setToughnessDefault(stat val);
		void setPower(stat val);
		void setToughness(stat val);
		void usePower(stat amount);
		void regainPower(stat amount);
		void damageBy(stat hp);
		void healBy(stat hp);
		void resetStats();

		virtual bool isLand() const;


	// Methods :
	public:
		virtual void newTurnDisengage();
		int dealDamageTo(Creature* c);
		int dealDamageTo(Contender* c) const;
		int receiveDamageFrom(Creature* c);
		bool isFittingCosts(const std::vector<const Land*> specificCost, const std::vector<const Land*> anyCost) const;

	
	// Print :
	public:
		virtual ostream& print(ostream& os) const;

};



#endif
