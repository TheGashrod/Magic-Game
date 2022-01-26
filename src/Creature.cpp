#include "../headers/Creature.hpp"

#include <algorithm>
#include <iostream>
#include <tuple>

#include "../headers/Contender.hpp"
#include "../headers/Land.hpp"
#include "../headers/tools/str.hpp"



using std::endl;
using std::size_t;
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
	Creature c = Creature(c_name, getColor(), isEngaged(), getColorCost(), getAnyCost(), c_powerDef, c_toughnessDef);
	shared_ptr<Card> ptr = std::make_shared<Creature>(c);
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
void Creature::usePower(stat amount) { c_power = std::max( 0 , (int)c_power - amount );}
void Creature::regainPower(stat amount) { c_power += amount; }
void Creature::healBy(stat hp) { c_toughness += hp; }
void Creature::damageBy(stat hp) { c_toughness = std::max( 0 , (int)c_toughness - hp ); }
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


bool Creature::isFittingCosts(const vector<const Land*> specificCost, const vector<const Land*> anyCost) const {
	

	// Checking whether each Land is unique :
	vector<const Land*> allLands = vector<const Land*>();
	for(auto land = specificCost.begin(); land != specificCost.end(); land++) {
		allLands.push_back( *land );
	}
	for(auto land = anyCost.begin(); land != anyCost.end(); land++) {
		allLands.push_back( *land );
	}
	for(size_t i = allLands.size()-1; i > 0; i--) {
		for(size_t i2 = 0; i2 < i; i2++) {
			if(allLands.at(i)->hasSameId( allLands.at(i2) ))
				return false;
		}
	}

	// Checking whether each land is engaged
	for(auto land = allLands.begin(); land != allLands.end(); land++) {
		if((*land)->isEngaged()) {
			return false;
		}
	}
	

	// Checking whether there are enough "any" lands for this creature
	if(anyCost.size() != getAnyCost()) {
		return false;
	}

	// Matching each specific cost with a land
	std::list<Color> cost = std::list<Color>(getColorCost());
	for(auto land = specificCost.begin(); land != specificCost.end(); land++) {
		
		auto color = cost.begin();
		int k = 0;
		bool hasFound = false;
		while(color != cost.end() && !hasFound) {
			if( *(*land)->getColor().begin() == *color) {
				cost.erase( color );
				hasFound = true;
			}
			color++;
			k++;
		}
		// If found nowhere
		if(!hasFound) {
			return false;
		}
	}


	// Returning true if everything's fine
	return true;
}



void Creature::newTurnDisengage() {
	c_power = c_powerDef;
	c_toughness = c_toughnessDef;
	disengage();
}




// Print :
ostream& Creature::print(ostream& os) const {
	os << "[Creature" << str_if(!isEngaged(),"*") << "] " << c_colors << " " << c_name << "#" << getId()
			<< " | Power : " << (int)c_power<<"/"<<(int)c_powerDef
			<< " | Toughness : "<<(int)c_toughness<<"/"<<(int)c_toughnessDef
			<< " | FirstCost : "<<getColorCost() << " SecondCost : " << getAnyCost();
	return os;
}