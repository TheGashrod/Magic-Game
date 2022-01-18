#ifndef __MTG_ACTION_INCLUDED__
#define __MTG_ACTION_INCLUDED__



#include "Duel.hpp"


class Action {


public:
    virtual void execute(Duel d) = 0;
};




#endif