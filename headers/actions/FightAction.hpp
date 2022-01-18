#ifndef __MTG_FIGHTACTION_INCLUDED__
#define __MTG_FIGHTACTION_INCLUDED__


#include "../Action.hpp"


Action a = Action();

class FightAction : public Action {
    virtual void nothing() = 0;
};




#endif