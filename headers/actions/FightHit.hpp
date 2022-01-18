#ifndef __MTG_FIGHTHIT_INCLUDED__
#define __MTG_FIGHTHIT_INCLUDED__


#include "FightAction.hpp"
#include "../Duel.hpp"


class FightHit : public FightAction {


public:
    virtual void execute(Duel d);
    /**
     * @brief Deals damage accordingly to stored creatures and contenders
     * Deals the actual damage while "execute" only adds the FightHit to a buffer to be executed later
     */
    virtual void damage() = 0;
};








#endif