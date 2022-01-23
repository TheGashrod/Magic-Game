#include "../../headers/tools/random.hpp"

#include <random>



int randInt(int max) {

	std::random_device r;

	std::default_random_engine e1(r());
   std::uniform_int_distribution<int> uniform_dist(0, max-1);

   return uniform_dist(e1);
}
	