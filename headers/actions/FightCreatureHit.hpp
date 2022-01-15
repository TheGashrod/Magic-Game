#include "FightHit.hpp"
#include "../Creature.hpp"

class FightCreatureHit : public FightHit {

public:
    Creature getAttacker();
    Creature getVictim();

};
