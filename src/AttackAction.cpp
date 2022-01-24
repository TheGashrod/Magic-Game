#include "../headers/AttackAction.hpp"


#include <algorithm>


#include "../headers/Creature.hpp"



using std::vector;



/* --------------------------------------------------------------------------------------------------/
                                        FightCreature
/ --------------------------------------------------------------------------------------------------*/


//
// Constructors :
//
FightCreature::FightCreature(Creature* c, bool isAttacker) :
c_creature(c), c_isAttacker(isAttacker), c_isEngaged(true), c_overstrength(0), c_overtoughness(0) { }


//
// Getters :
//
const Creature* FightCreature::getCreature() const { return c_creature; }
Creature* FightCreature::getOriginalCreature() { return c_creature; }
bool FightCreature::isAttacker() const { return c_isAttacker; }
bool FightCreature::isEngaged() const { return c_isEngaged; }
int FightCreature::getOverstrength() const { return c_overstrength; }
int FightCreature::getOvertoughness() const { return c_overtoughness; }

//
// Setters :
//
void FightCreature::setAttacker(bool isAttack) { c_isAttacker = isAttack; }
void FightCreature::engage() { c_isEngaged = true; }
void FightCreature::disengage() { c_isEngaged = false; }
void FightCreature::setOverstrength(int val) { c_overstrength = val; }
void FightCreature::addOversrength(int val) { c_overstrength += val; }
void FightCreature::setOvertoughness(int val) { c_overtoughness = val; }
void FightCreature::addOvertoughness(int val) { c_overtoughness += val; }

//
// Methods :
//
void FightCreature::execute() {
	// TODO
}




/* --------------------------------------------------------------------------------------------------/
                                          AttackAction
/ --------------------------------------------------------------------------------------------------*/


//
// Constructors :
//
AttackAction::AttackAction(Contender* orderer, Contender* victim, Creature* attacker) :
a_attacker(orderer), a_victim(victim),
a_creatures(vector<FightCreature>( {FightCreature(attacker, true)} ))
{}

//
// Getters :
//
const Contender* AttackAction::getAttacker() const { return a_attacker; }
const Contender* AttackAction::getVictim() const { return a_victim; }
vector<FightCreature>* AttackAction::getOriginalCreatures() { return &a_creatures; }

bool AttackAction::isAnyAttackCreatureAlive() const {
	return any_of(a_creatures.begin(), a_creatures.end(), 
		[](FightCreature fc) { return fc.isAttacker() && fc.getCreature()->isAlive(); }
	);
}

FightCreature* AttackAction::getOriginalAttackCreature() {  }
//vector<tuple<Ability*, long>>* AttackAction::getOriginalAbilities(); // TODO : Decomment when Ability is released
//vector<const Ability*> AttackAction::getAbilities() const; // TODO : Decomment when Ability is released

//
// Setters :
//
void AttackAction::addFightCreature(FightCreature fc) { a_creatures.push_back(fc); }




//
// Methods :
//

void AttackAction::execute() {
	
	// Sort attackers and defenders
	vector<Creature*> attackers = vector<Creature*>();
	vector<Creature*> defenders = vector<Creature*>();
	for(auto c = a_creatures.begin(); c != a_creatures.end(); c++) {
		if( (*c).isAttacker() ) {
			attackers.push_back( (*c).getOriginalCreature() );
		}
		else {
			defenders.push_back( (*c).getOriginalCreature() );
		}
	}

	// Actual fight
	if(defenders.size() > 0) {
		for(auto att = attackers.begin(); att != attackers.end(); att++) {
			for(auto def = defenders.begin(); def != defenders.end(); def++) {
				if((*att)->isAlive() && (*def)->isAlive()) {
					
					(*att)->dealDamageTo( (*def) );
					(*def)->dealDamageTo( (*att) );
					
					// Send deads to cemetary
					if( !(*def)->isAlive() ) {
						a_victim->getInGameCards().transfer( (*def), a_victim->getOriginalCemetary() );
					}
					if( !(*att)->isAlive() ) {
						a_attacker->getInGameCards().transfer( (*att), a_attacker->getOriginalCemetary() );
						break;
					}
				}		
				
			}
		}
	}
}