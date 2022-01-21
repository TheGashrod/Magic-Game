#ifndef __MTG_DUEL_INCLUDED__
#define __MTG_DUEL_INCLUDED__


#include "Duel_interface.hpp"


#include <list>
#include <vector>


class Interface_interface;
class Contender;
class Card;
class Creature;
class FightHit;



class Duel : public Duel_interface {

// Members
private:
    char d_currentPhase;
    char d_remainingTurns;
    Contender* d_currentContender;
    std::vector<Interface_interface*>d_interfaces;
    std::vector<FightHit*> d_fightHitBuffer;



    // Game phases and exchanges with interfaces
    public: virtual void start();
    private: virtual void ph1Draw_start();
    private: virtual void ph2Disgendage_start();
    private: virtual void ph3PlayCard_start();
    public: virtual void chooseCard(Card* c);
    public: virtual void ph3_end();
    private: virtual void ph4Fight_start();
    public: virtual void ph4Fight(Creature att, Contender c, std::list<Creature> def);
    public: virtual void ph4_end();
    private: virtual void ph5PlayCard_start();
    // chooseCard is called again here
    public: virtual void ph5_end();
    private: virtual void ph6Discard_start();
    public: virtual void ph6_end();


    // Getters/setters (Turns related members)
    public:
        char getPhase() const;
        unsigned char getRemainingTurns() const;
        Contender* getCurrentContender() const;
        const std::vector<FightHit> getFightHitBuffer() const;

        void setRemainingTurns(unsigned char nb);
        void addInterface(Interface_interface* i);
        void addFightHitToBuffer(FightHit* fh);
        void clearFightHitBuffer();


};



#endif
