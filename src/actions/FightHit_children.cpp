#include "../../headers/actions/FightHit_children.hpp"



#include "../../headers/Creature.hpp"
#include "../../headers/Contender.hpp"



void FightContenderHit::damage() {
	f_attacker->dealDamageTo(f_victim);
}

void FightCreatureHit::damage() {
	f_attacker->dealDamageTo(f_victim);
}

void FightBlock::damage() {
	f_defender->dealDamageTo(f_attacker);
};
