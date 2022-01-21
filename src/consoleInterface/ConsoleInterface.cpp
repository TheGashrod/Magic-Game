#include "../../headers/consoleInterface/ConsoleInterface.hpp"


#include <iostream>

#include "../../headers/Card.hpp"
#include "../../headers/Creature.hpp"
#include "../../headers/Contender.hpp"



using std::cout;
using std::endl;
using std::size_t;



ConsoleInterface::ConsoleInterface(Duel d) : i_duel(d) { }




void ConsoleInterface::showText(std::string t) {
    cout << t << endl;
}


void ConsoleInterface::ph1DrawnCard(const Card* c) {
    cout << "Vous piochez une carte : \n" << c << "\n";
}

void ConsoleInterface::ph2Disengage(const std::list<Card*> c) {
    cout << "Vos cartes ont été désengagées :" << endl;
    for(auto card = c.begin(); card != c.end(); card++) {
        cout << *card << endl;
    }
}

void ConsoleInterface::ph3PlayCards_wait(std::list<Card*> c, std::list<Card*> inGameLand) {
    cout << "You can put cards from your hand into the game." << endl;
    i_duel.chooseCard( pickACard_option(c) );
}

void ConsoleInterface::ph4Fight_wait(Contender att, Contender def) {
    // TODO
}

void ConsoleInterface::ph5PlayCards_wait(std::list<Card*> c, std::list<Card*> inGameLand) {
    // TODO
}

void ConsoleInterface::ph6Discard_wait(std::list<Card*> c, size_t nbToDiscard) {
    // TODO
}



/**
 * @brief Lets the player pick a card among a list if they want
 * 
 * @param cards The available cards to pick from
 * @return Card* The picked card OR nullptr if the player doesn't want to pick
 */
Card* ConsoleInterface::pickACard_option(std::list<Card*> cards) const {
    size_t choice;

    do {
        cout << "Pick a card among these (type the number) :\n";
        size_t k = 1;
        for(auto i = cards.begin(); i != cards.end(); i++) {
            cout << k << ". " << *i << endl;
            k++;
        }
        cout << "0. Don't pick any card" << endl << endl;
        cout << "Your choice : ";
        cin >> choice;
    } while(choice > cards.size());

    if(choice == 0) {
        return nullptr; // Return if the player doesn't make any choice
    } else {
        auto i = cards.begin();
        for(size_t k=1; k < choice; k++)
            i++;
        return *i;
    }
}



Card* ConsoleInterface::pickACard(std::list<Card*> cards) const {
    size_t choice;

    do {
        cout << "Pick a card among these (type the number) :\n";
        size_t k = 1;
        for(auto i = cards.begin(); i != cards.end(); i++) {
            cout << k << ". " << *i << endl;
            k++;
        }
        cout << "Your choice : ";
        cin >> choice;
    } while(choice == 0 || choice > cards.size());

    auto i = cards.begin();
    for(size_t k=1; k < choice; k++)
        i++;
    return *i;
}