#ifndef __MTG_FIGHTDEATH_INCLUDED__
#define __MTG_FIGHTDEATH_INCLUDED__




#include "FightAction.hpp"
#include "../Creature.hpp"

class FightDeath : public FightAction {


public:
    Creature getCreature();
};




#endif