#include "../../headers/consoleInterface/ConsoleInterface.hpp"


#include <iostream>

//#include "../../headers/Interface.hpp"
#include "../../headers/Card.hpp"
#include "../../headers/Creature.hpp"
#include "../../headers/Contender.hpp"



using std::cout;
using std::endl;


void ConsoleInterface::showText(std::string t) {
    cout << t << endl;
}


void ConsoleInterface::ph1DrawnCard(Card* c) {
    cout << "Vous piochez une carte : " << c << endl;
}

void ConsoleInterface::ph2Disgendage(std::list<Card*> c) {
    // TODO
}

void ConsoleInterface::ph3PlayCards_wait(std::list<Card*> c, std::list<Card*> inGameLand) {
    // TODO
};

void ConsoleInterface::ph4Fight_wait(Contender att, Contender def) {
    // TODO
}

void ConsoleInterface::ph5PlayCards_wait(std::list<Card*> c, std::list<Card*> inGameLand) {
    // TODO
}

void ConsoleInterface::ph6Discard_wait(std::list<Card*> c, size_t nbToDiscard) {
    // TODO
}
