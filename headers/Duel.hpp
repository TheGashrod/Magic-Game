#ifndef __MTG_DUEL_INCLUDED__
#define __MTG_DUEL_INCLUDED__



#include <list>
#include <vector>

#include "Creature.hpp"
#include "actions/FightHit.hpp"


class Duel {

// Members
private:
    char d_currentPhase;
    char d_remainingTurns;
    Contender* d_currentContender;
    // TODO : Interfaces
    vector<FightHit> fightHitBuffer;



    // Game phases and exchanges with interfaces
    public: void start();
    private: void ph1Draw_start();
    private: void ph2Disgendage_start();
    private: void ph3PlayCard_start();
    public: void chooseCard(Card c);
    public: void ph3_end();
    private: void ph4Fight_start();
    public: void ph4Fight(Creature att, Contender c, std::list<Creature> def);
    public: void ph4_end();
    private: void ph5PlayCard_start();
    // chooseCard is called again here
    public: void ph5_end();
    private: void ph6Discard_start();
    public: void ph6_end();

    unsigned char getRemainingTurns();
    void setRemainingTurns(unsigned char nb);

};



#endif 