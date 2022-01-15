#include <list>
#include <tuple>
#include "Card.hpp"



class Creature : public Card {

	private :

	public :
		// TODO : Pourquoi un int si on a aussi une couleur Any ? Il faut choisir
		std::tuple<int, std::list<Color>> cost;

		//Constructors :
		Creature (int, std::list<Color>);
      ~Creature();

};
