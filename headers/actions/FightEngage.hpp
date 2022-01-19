#ifndef __MTG_FIGHTENGAGE_INCLUDED__
#define __MTG_FIGHTENGAGE_INCLUDED__


#include "FightAction.hpp"
class Creature;




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




#endif
