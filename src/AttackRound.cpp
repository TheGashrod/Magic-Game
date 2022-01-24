#include "../headers/AttackRound.hpp"



// Getters & setters :
std::vector<AttackAction> AttackRound::getAttacks() const { return r_attacks; }

void AttackRound::addAttack(AttackAction aa) { r_attacks.push_back(aa); }



// Methods :
void AttackRound::execute() {
	
	// Execute the attack if possible
	for(auto aa = r_attacks.begin(); aa != r_attacks.end(); aa++) {
		if( (*aa).isAnyAttackCreatureAlive() ) {
			(*aa).execute();
		}
	}
}

/*
void AttackRound::applyAbility(FightAbility fa) { // TODO : Decomment when Ability is available
	
}*/

void AttackRound::reset() { r_attacks.clear(); }