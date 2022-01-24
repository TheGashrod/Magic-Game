#ifndef __MTG_ATTACKACTION_INCLUDED__
#define __MTG_ATTACKACTION_INCLUDED__



#include <vector>
#include <tuple>


#include "Contender.hpp"
#include "Creature.hpp"





class FightCreature {

	// Attributes :
	private:
		Creature* c_creature;
		bool c_isAttacker;
		bool c_isEngaged;
		int c_overstrength;
		int c_overtoughness;
	

	// Constructors :
	public:
		FightCreature(Creature* c, bool isAttacker);



	// Getters & setters
	public:
		const Creature* getCreature() const;
		bool isAttacker() const;
		bool isEngaged() const;
		int getOverstrength() const;
		int getOvertoughness() const;

		void setAttacker(bool isAttack);
		void engage();
		void disengage();
		void setOverstrength(int val);
		void addOversrength(int val);
		void setOvertoughness(int val);
		void addOvertoughness(int val);
	

	// Methods :
	public:
		void execute();


};




class AttackAction {

	// Attributes :
	private:
		Contender* a_attacker;
		Contender* a_victim;
		std::vector<FightCreature> a_creatures;
		//std::vector<tuple<Ability*, long>> a_appliedAbilities; // TODO : Decomment when Ability is released
	


	// Constructors :
	public:
		AttackAction(Contender* orderer, Contender* victim, Creature* attacker);



	// Getters & setters
	public:
		const Contender* getAttacker() const;
		const Contender* getVictim() const;
		std::vector<FightCreature>* getOriginalCreatures();
		//std::vector<tuple<Ability*, long>>* getOriginalAbilities(); // TODO : Decomment when Ability is released
		//std::vector<const Ability*> getAbilities() const; // TODO : Decomment when Ability is released

		void addFightCreature(FightCreature fc);
	private:
		void clearFightCreatures();




	// Methods :
	public:
		void execute();

};








#endif