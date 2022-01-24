 #include "../headers/Land.hpp"

#include <memory>


using std::unique_ptr;


Land::Land (string name, Color color, bool isEngaged)
: Card(name, std::list<Color>(color), isEngaged) {
	 
}


shared_ptr<Card> Land::clone() const {
	Land l = Land(getName(), *getColor().begin(), isEngaged());
	return std::make_shared<Land>(l);
}




bool Land::isLand() const {
	return true;
}


ostream& Land::print(ostream& os) const {
	return os << "[Land] " << c_name;
}