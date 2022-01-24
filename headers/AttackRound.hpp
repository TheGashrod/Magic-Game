#ifndef __MTG_ATTACKROUND_INCLUDED__
#define __MTG_ATTACKROUND_INCLUDED__


#include <vector>


#include "AttackAction.hpp"



class AttackRound {

	// Attributes :
	private:
		std::vector<AttackAction> r_attacks = std::vector<AttackAction>();


	// Getters & setters :
	public:
		std::vector<AttackAction> getAttacks() const;

		void addAttack(AttackAction aa);
	

	// Methods :
	public:
		void execute();
		//void applyAbility(FightAbility a); // TODO Decomment when Ability is available
		void reset();


};








#endif