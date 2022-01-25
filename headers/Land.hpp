#ifndef __MTG_LAND_INCLUDED__
#define __MTG_LAND_INCLUDED__


#include <memory>


#include "Card.hpp"



class Land : public Card {

	// Members :
	// None

	// Constructors :
	protected:
		Land(unsigned long id, string name, Color color, bool isEngaged);
	public:
		Land(string name, Color color, bool isEngaged);
		virtual shared_ptr<Card> clone() const;
		Land duplicateLand() const;
		Land cloneLand() const;


	// Getters/setters
	public:
		virtual bool isLand() const;



	// Print :
	public:
		virtual ostream& print(ostream& os) const;

};


ostream& operator<<(ostream& os, const Land l);
ostream& operator<<(ostream& os, const Land* l);



#endif
