#include "FightHit.hpp"
#include "../Creature.hpp"
#include "../Contender.hpp"

class FightContenderHit : public FightHit {

public:
    Creature getAttacker();
    Contender getVictim();

};
