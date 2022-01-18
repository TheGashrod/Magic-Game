#include "../headers/Card.hpp"

#include <algorithm>

using namespace std;


// Members :
unsigned long Card::c_nextId = 0;


// Constructors :
Card::Card(unsigned long id, string name, std::list<Color> colors, bool isEngaged)
: c_id(id), c_name(name), c_colors(std::list(colors)), c_isEngaged(isEngaged) { }

Card::Card (string name, std::list<Color> colors, bool isEngaged)
: Card(c_nextId++, name, colors, isEngaged) { }

Card::~Card() {};


// Getters/setters :
bool Card::isEngaged() const { return c_isEngaged; }

void Card::engage() { c_isEngaged = true; }
void Card::disengage() { c_isEngaged = false; }


// Methods :
bool Card::hasSameId(Card *c) const {
    return c->c_id == this->c_id;
}
