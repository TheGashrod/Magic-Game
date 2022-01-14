#include "FightHit.hpp"
#include "../Creature.hpp"

class FightBlock : public FightHit {

public:
    Creature getAttacker();
    Creature getVictim();

};
