#include "../../headers/enums/Color.hpp"


#include <iostream>

using std::ostream;


ostream& operator<<(ostream& os, const Color c) {
	switch (c)
	{
	case Blue: return os << "/Blue/";
	case White: return os << "/White/";
	case Red: return os << "/Red/";
	case Black: return os << "/Black/";
	case Green: return os << "/Green/";
	}
	return os << "/Unknown color/";
}


ostream& operator<<(ostream& os, std::list<Color> colors) {
	//std::cout << "Before Colors loop | colors vector size : " << colors.size() << "\n";
	for(auto i = colors.begin(); i != colors.end(); i++) {
		os << *i;
	}
	return os;
}