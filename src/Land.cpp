 #include "../headers/Land.hpp"

#include <memory>


using std::unique_ptr;


 Land::Land (string name, Color color, bool isEngaged)
 : Card(name, std::list<Color>(color), isEngaged) {
	 
 }


unique_ptr<Card> Land::clone() const {
	const Land l = *this;
	Land copy = Land(l);
	std::unique_ptr<Land> ptr = std::unique_ptr<Land>(&copy);
	return ptr;
}


ostream& Card::print(ostream& os) const {
	return os << "[Land] " << c_name;
}