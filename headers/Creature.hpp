
#include "tools/Color.hpp"

class Creature : Card {

	private :

	public :
		std::tuple<int, List<Color>> cost;

		//Constructors :
		Creature (int, List<Color>);
    	// Card();
        ~Card();
} 
