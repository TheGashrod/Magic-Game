#include "../headers/AttackAction.hpp"



#include "../headers/Creature.hpp"



using std::vector;



/* --------------------------------------------------------------------------------------------------/
                                        FightCreature
/ --------------------------------------------------------------------------------------------------*/


// Constructors :
FightCreature::FightCreature(Creature* c, bool isAttacker) :
c_creature(c), c_isAttacker(isAttacker), c_isEngaged(true), c_overstrength(0), c_overtoughness(0) { }


// Getters :
const Creature* FightCreature::getCreature() const { return c_creature; }
bool FightCreature::isAttacker() const { return c_isAttacker; }
bool FightCreature::isEngaged() const { return c_isEngaged; }
int FightCreature::getOverstrength() const { return c_overstrength; }
int FightCreature::getOvertoughness() const { return c_overtoughness; }

// Setters :
void FightCreature::setAttacker(bool isAttack) { c_isAttacker = isAttack; }
void FightCreature::engage() { c_isEngaged = true; }
void FightCreature::disengage() { c_isEngaged = false; }
void FightCreature::setOverstrength(int val) { c_overstrength = val; }
void FightCreature::addOversrength(int val) { c_overstrength += val; }
void FightCreature::setOvertoughness(int val) { c_overtoughness = val; }
void FightCreature::addOvertoughness(int val) { c_overtoughness += val; }


// Methods :
void FightCreature::execute() {
	// TODO
}




/* --------------------------------------------------------------------------------------------------/
                                          AttackAction
/ --------------------------------------------------------------------------------------------------*/



// Constructors :
AttackAction::AttackAction(Contender* orderer, Contender* victim, Creature* attacker) :
a_attacker(orderer), a_victim(victim),
a_creatures(vector<FightCreature>( {FightCreature(attacker, true)} ))
{}


// Getters :
const Contender* AttackAction::getAttacker() const { return a_attacker; }
const Contender* AttackAction::getVictim() const { return a_victim; }
vector<FightCreature>* AttackAction::getOriginalCreatures() { return &a_creatures; }
//vector<tuple<Ability*, long>>* AttackAction::getOriginalAbilities(); // TODO : Decomment when Ability is released
//vector<const Ability*> AttackAction::getAbilities() const; // TODO : Decomment when Ability is released

// Setters :
void AttackAction::addFightCreature(FightCreature fc) { a_creatures.push_back(fc); }
void AttackAction::clearFightCreatures() { a_creatures.clear(); }


// Methods :
void AttackAction::execute() {
	for(auto c = a_creatures.begin(); c != a_creatures.end(); c++) {
		(*c).execute();
	}
}