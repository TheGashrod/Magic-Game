#include "FightAction.hpp"
#include "../Creature.hpp"




/**
 * @brief Engages an attacking creature
 * 
 */
class FightEngageAttack : public FightAction {


public:
    Creature* f_creature;
};




/**
 * @brief Engages a blocking creature
 * 
 */
class FightEngageBlock : public FightAction {


public:
    Creature* f_creature;
};
