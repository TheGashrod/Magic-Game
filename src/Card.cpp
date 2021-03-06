#include "../headers/Card.hpp"

#include <algorithm>
#include <iostream>


#include "../headers/enums/Color.hpp"


using namespace std;


// Members :
unsigned long Card::c_nextId = 0;


// Constructors :
Card::Card(unsigned long id, string name, std::list<Color> colors, bool isEngaged)
: c_id(id), c_name(name), c_colors(std::list(colors)), c_isEngaged(isEngaged) { }

Card::Card (string name, std::list<Color> colors, bool isEngaged)
: Card(c_nextId++, name, std::list<Color>(colors), isEngaged) { }

Card::~Card() {};


// Getters/setters :
long Card::getId() const { return c_id; }
string Card::getName() const { return c_name; }
std::list<Color> Card::getColor() const { return c_colors; }
bool Card::isEngaged() const { return c_isEngaged; }

void Card::engage() { c_isEngaged = true; }
void Card::disengage() { c_isEngaged = false; }


// Methods :
bool Card::hasSameId(const Card *c) const {
    return c->c_id == this->c_id;
}
void Card::newTurnDisengage() { 
    disengage();
}


// Print :
ostream& Card::print(ostream& os) const {
    return os << "[Card] " << getName() << " | Abstract";
}



// Operators :
ostream& operator<<(ostream& os, const Card* c) {
    ostream& os2 = (*c).print(os);
    return os2;
}
