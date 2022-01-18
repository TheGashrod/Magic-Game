#include "../headers/Card.hpp"

#include <algorithm>

using namespace std;


// Members :
unsigned long Card::c_nextId = 0;


// Constructors :
Card::Card (string name, std::list<Color> colors) : c_id(c_nextId++), c_name(name), c_colors(std::list(colors)) { }

Card::~Card() {};


// Methods :
bool Card::hasSameId(Card *c) const {
    return c->c_id == this->c_id;
}
