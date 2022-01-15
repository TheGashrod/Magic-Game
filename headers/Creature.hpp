#include <list>
#include "enums/Color.cpp"
#include "Card.hpp"



class Creature : public Card {

	private :

	public :
		std::tuple<int, std::list<Color>> cost;

		//Constructors :
		Creature (int, std::list<Color>);
      ~Creature();

};
