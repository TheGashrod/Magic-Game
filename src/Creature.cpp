#include "../headers/Creature.hpp"

#include <algorithm>

using std::tuple;


//Constructors :
Creature::Creature (string name, std::list<Color> colors, bool isEngaged,
std::list<Color> colorCost, int anyCost,
stat powerDefault, stat toughnessDefault)
: Card(name, colors, isEngaged),
	c_cost( {anyCost, std::list<Color>(colorCost)} ),
	c_power(powerDefault), c_powerDef(powerDefault), c_toughness(toughnessDefault), c_toughnessDef(toughnessDefault) { }

Creature::~Creature() { };


// Getters/setters :
tuple<int, std::list<Color>> Creature::getCost() const { return tuple<int, std::list<Color>>(c_cost); }
std::list<Color> Creature::getColorCost() const { return std::list<Color>(  std::get<1>(c_cost) ); }
int Creature::getAnyCost() const { return std::get<0>(c_cost); }
stat Creature::getPower() const { return c_power; }
stat Creature::getPowerDefault() const { return c_powerDef; }
stat Creature::getToughness() const { return c_toughness; }
stat Creature::getToughnessDefault() const { return c_toughnessDef; }

void Creature::setPowerDefault(stat val) { c_powerDef = val; }
void Creature::setToughnessDefault(stat val) { c_toughnessDef = val; }
void Creature::setPower(stat val) { c_power = val; }
void Creature::setToughness(stat val) { c_toughness = val; }
void Creature::usePower(stat amount) { c_power += amount; }
void Creature::regainPower(stat amount) { c_power = std::max( (stat)0 , amount ); }
void Creature::healBy(stat hp) { c_toughness += hp; }
void Creature::damageBy(stat hp) { c_toughness = std::max( (stat)0 , hp ); }
void Creature::resetStats() {
	c_power = c_powerDef;
	c_toughness = c_toughnessDef;
}


// Methods :
int Creature::dealDamageTo(Creature* c) {
	return c->receiveDamageFrom(this);
}

int Creature::dealDamageTo(Contender* c) const {
	return c->damageBy( getPower() );
}


int Creature::receiveDamageFrom(Creature* c) {
	stat damage = std::min( c->getPower() , this->getToughness() );
	this->damageBy( damage );
	c->usePower( damage );
}