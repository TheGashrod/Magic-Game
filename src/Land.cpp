 #include "../headers/Land.hpp"

#include <memory>
#include <vector>
#include <list>


using std::vector;
using std::unique_ptr;


Land::Land(unsigned long id, string name, Color color, bool isEngaged)
: Card(id, name, std::list<Color>(color), isEngaged) { }

Land::Land (string name, Color color, bool isEngaged)
: Card(name, std::list<Color>({color}), isEngaged) {
	 
}


shared_ptr<Card> Land::clone() const {
	Land l = Land(getName(), *getColor().begin(), isEngaged());
	return std::make_shared<Land>(l);
}


Land Land::cloneLand() const {
	return Land(getName(), *getColor().begin(), isEngaged());
}
Land Land::duplicateLand() const {
	return Land(c_id, getName(), *getColor().begin(), isEngaged());
}







bool Land::isLand() const {
	return true;
}


ostream& Land::print(ostream& os) const {
	os << "[Land] ";

	std::list<Color> colors = getColor();
	for(auto color = colors.begin(); color != colors.end(); color++) {
		os << *color;
	}
	
	os << " " << c_name << "#" << getId() << " ";
	return os; 
}



ostream& operator<<(ostream& os, const Land l) {
	return l.print(os);
}

ostream& operator<<(ostream& os, const Land* l) {
	return l->print(os);
}