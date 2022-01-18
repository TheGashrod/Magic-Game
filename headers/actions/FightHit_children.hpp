#include "FightHit.hpp"
#include "../Creature.hpp"


/**
 * @brief Action when a creature directly hits a player
 * Inherits FightHit
 */
class FightContenderHit : public FightHit {

public:
    const Creature* f_attacker;
    const Contender* f_victim;

public:
    virtual void damage();

};





/**
 * @brief Action when a creature attacks another one blocking (only damages the defender)
 * Inherits FightHit
 */
class FightCreatureHit : public FightHit {

public:
    const Creature* f_attacker;
    const Creature* f_victim;

public:
    virtual void damage();

};




/**
 * @brief Action when a creature blocks an attack (only damages the attacker)
 * Inherits FightHit
 */
class FightBlock : public FightHit {

public:
    const Creature* f_attacker;
    const Creature* f_defender;

    
public:
    virtual void damage();

};
