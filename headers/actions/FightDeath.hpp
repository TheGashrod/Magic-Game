#ifndef __MTG_FIGHTDEATH_INCLUDED__
#define __MTG_FIGHTDEATH_INCLUDED__



#include "FightAction.hpp"
class Creature;


class FightDeath : public FightAction {


public:
    Creature getCreature();
};




#endif
