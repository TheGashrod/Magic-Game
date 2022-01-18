#include "FightAction.hpp"

class FightHit : public FightAction {


public:
    virtual void execute(Duel d);
    /**
     * @brief Deals damage accordingly to stored creatures and contenders
     * Deals the actual damage while "execute" only adds the FightHit to a buffer to be executed later
     */
    virtual void damage() = 0;
};
