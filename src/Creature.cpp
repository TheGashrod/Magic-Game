#include "../headers/Creature.hpp"

#include <algorithm>
#include <iostream>
#include <tuple>

#include "../headers/Contender.hpp"



using std::endl;
using std::tuple;
using std::unique_ptr;


//Constructors :
Creature::Creature (string name, std::list<Color> colors, bool isEngaged,
std::list<Color> colorCost, int anyCost,
stat powerDefault, stat toughnessDefault)
: Card(name, std::list<Color>(colors), isEngaged),
	c_cost( {anyCost, std::list<Color>(colorCost)} ),
	c_power(powerDefault), c_powerDef(powerDefault), c_toughness(toughnessDefault), c_toughnessDef(toughnessDefault) { }

Creature::~Creature() { };

shared_ptr<Card> Creature::clone() const {
	cout << "Creature copy constructor 1" << endl;
	Creature c = Creature(c_name, getColor(), isEngaged(), getColorCost(), getAnyCost(), c_powerDef, c_toughnessDef);
	cout << "Creature copy constructor 2" << endl;
	shared_ptr<Card> ptr = std::make_shared<Creature>(c);
	cout << "Creature copy constructor 3" << endl;
	return ptr;
}


// Getters/setters :
tuple<int, std::list<Color>> Creature::getCost() const { return tuple<int, std::list<Color>>(c_cost); }
std::list<Color> Creature::getColorCost() const { return std::list<Color>(  std::get<1>(c_cost) ); }
int Creature::getAnyCost() const { return std::get<0>(c_cost); }
stat Creature::getPower() const { return c_power; }
stat Creature::getPowerDefault() const { return c_powerDef; }
stat Creature::getToughness() const { return c_toughness; }
stat Creature::getToughnessDefault() const { return c_toughnessDef; }
bool Creature::isAlive() const { return c_toughness > 0; }

void Creature::setPowerDefault(stat val) { c_powerDef = val; }
void Creature::setToughnessDefault(stat val) { c_toughnessDef = val; }
void Creature::setPower(stat val) { c_power = val; }
void Creature::setToughness(stat val) { c_toughness = val; }
void Creature::usePower(stat amount) { c_power = std::max( (stat)0 , amount );}
void Creature::regainPower(stat amount) { c_power += amount; }
void Creature::healBy(stat hp) { c_toughness += hp; }
void Creature::damageBy(stat hp) { c_toughness = std::max( (stat)0 , hp ); }
void Creature::resetStats() {
	c_power = c_powerDef;
	c_toughness = c_toughnessDef;
}

bool Creature::isLand() const { return false; }


// Methods :
int Creature::dealDamageTo(Creature* c) {
	return c->receiveDamageFrom(this);
}

int Creature::dealDamageTo(Contender* c) const {
	return c->damageBy( getPower() );
	printf("Creature::dealDamageTo needs comment to be removed");
	return 0;
}


int Creature::receiveDamageFrom(Creature* c) {
	stat damage = std::min( c->getPower() , this->getToughness() );
	this->damageBy( damage );
	c->usePower( damage );
	return damage;
}




// Print :
ostream& Creature::print(ostream& os) const {
	os << "[Creature] " << c_colors << " " << c_name << "#" << getId()
			<< " | Power : " << (int)c_power<<"/"<<(int)c_powerDef
			<< " | Toughness : "<<(int)c_toughness<<"/"<<(int)c_toughnessDef
			<< " | Cost : "<<getColorCost();
	return os;
}