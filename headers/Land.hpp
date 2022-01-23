#ifndef __MTG_LAND_INCLUDED__
#define __MTG_LAND_INCLUDED__


#include <memory>


#include "Card.hpp"



class Land : public Card {

	// Members :
	// None

	// Constructors :
	Land(string name, Color color, bool isEngaged);

	// Getters/setters
	virtual bool isLand() const;

	virtual ostream& print(ostream& os) const;

};




#endif
