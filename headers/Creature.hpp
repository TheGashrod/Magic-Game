#include <list>
#include <tuple>


#include "Card.hpp"
#include "Contender.hpp"


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

		void setPowerDefault(stat val);
		void setToughnessDefault(stat val);
		void setPower(stat val);
		void setToughness(stat val);
		void usePower(stat amount);
		void regainPower(stat amount);
		void damageBy(stat hp);
		void healBy(stat hp);
		void resetStats();


	// Methods :
	public:
		int dealDamageTo(Creature* c);
		int dealDamageTo(Contender* c) const;
		int receiveDamageFrom(Creature* c);

};
