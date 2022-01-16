#include "FightAction.hpp"

class FightHit : public FightAction {


public:
    virtual void damage() = 0;
};
