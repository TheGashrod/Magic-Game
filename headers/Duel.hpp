class Duel {

public:
    void start();
    void drawPhase1();
    void disengagePhase2();
    void cardsPhase35();
    void fightPhase4();
    void discardPhase6();

    unsigned char getRemainingTurns();
    void setRemainingTurns(unsigned char nb);

};
