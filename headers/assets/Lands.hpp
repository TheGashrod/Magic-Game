#ifndef __MTG_LAND_ASSETS_INCLUDED__
#define __MTG_LAND_ASSETS_INCLUDED__


#include <vector>



#include "../../headers/Land.hpp"




vector<Land> landsList = vector<Land>({
	Land("Plains", Red, false),
	Land("Island", Black, false),
	Land("Swamp", White, false),
	Land("Mountain", Green, false),
	Land("Forest", Blue, false),
	Land("Dragonskull Summit", Black, false),
	Land("Drowned Catacomb", Red, false),
	Land("Glacial Fortress", White, false),
	Land("Gargoyle Castle", Blue, false),
	Land("Rootbound Crag", Green, false)

});


#endif