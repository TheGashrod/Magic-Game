#include "../../headers/consoleInterface/ConsoleInterface.hpp"


#include <iostream>

#include "../../headers/Duel.hpp"
#include "../../headers/Card.hpp"
#include "../../headers/Creature.hpp"
#include "../../headers/Contender.hpp"



using std::cout;
using std::endl;
using std::size_t;
using std::string;
using std::vector;


/* --------------------------------------------------------------------------------------------------/
                                          Constructors
/ --------------------------------------------------------------------------------------------------*/


ConsoleInterface::ConsoleInterface(Duel* d) : i_duel(d) {
    i_duel->addInterface(this);
}



/* --------------------------------------------------------------------------------------------------/
                                       Duel listeners
/ --------------------------------------------------------------------------------------------------*/

void ConsoleInterface::showText(std::string t) {
    cout << t << endl;
}


void ConsoleInterface::ph1DrawnCard(const Contender* con, const Card* card) {
    cout << endl << "Vous piochez une carte : \n" << card << "\n";
}

void ConsoleInterface::ph2Disengage(const Contender* con, const std::list<const Card*> c) {
    cout << endl << "Vos cartes ont été désengagées :" << endl;
    if(c.size() == 0) {
        cout << "Aucune" << endl;
    }
    else {
        for(auto card = c.begin(); card != c.end(); card++) {
        cout << *card << endl;
        }
    }
}

void ConsoleInterface::ph3PlayCards_wait(const Contender* con) {
    cout << endl << "You can put cards from your hand into the game." << endl;
    cout << "Nombre de cartes : " << con->getHand().getCardsSet().size() << endl;
    const Card* picked = pickACard_option( con->getHand().getCardsSet() );
    
    if(picked == nullptr) {
        i_duel->ph3_end();
    }
    else {
        i_duel->chooseCard( picked );
    }
}

void ConsoleInterface::ph4Fight_wait(const Contender* att, const Contender* def) {
    
    if( att->getInGameCards().getDisengaged().getCreatures().size() > 0 ) {
    
        cout << endl << "Do you want to attack " << def->getPlayer().getName() << " ?";
        bool isAttacking = pickYesOrNo();
        
        if(isAttacking) {

            cout << endl << "Pick your attacking creature." << endl;
            const Creature* attCreature = pickACreature( att->getInGameCards().getDisengaged().getCreatures() );
            
            cout << endl << "Action from " << def->getPlayer().getName() << endl;
            vector<const Creature*> defCreatures = vector<const Creature*>();
            bool mustContinue = true;
            cout << def->getInGameCards() << endl;
            do {
                cout << endl << "Pick a defending creature. (you can pick multiple ones till you type 0)" << endl;
                const Creature* c = pickACreature_option( def->getInGameCards().getDisengaged().getCreatures() );
                if(c == nullptr) {
                    mustContinue = false;
                }
                else {
                    defCreatures.push_back(c);
                }
            } while(mustContinue);

            // Notifying Duel
            i_duel->ph4Fight(attCreature, defCreatures);
            
        }
        else
            i_duel->ph4_end();
    }
    else {
        cout << endl << "You do not have any creature able to attack. Skipping fight phase." << endl;
        i_duel->ph4_end();
    }
}

void ConsoleInterface::ph5PlayCards_wait(const Contender* con) {
    cout << endl << "You can put cards from your hand into the game again." << endl;
    const Card* picked = pickACard_option( con->getHand().getCardsSet() );
    
    if(picked == nullptr) {
        i_duel->ph3_end();
    }
    else {
        i_duel->chooseCard( picked );
    }
}

void ConsoleInterface::ph6Discard_wait(const Contender* con, size_t nbToDiscard) {
    // TODO
}





/* --------------------------------------------------------------------------------------------------/
                                          User actions
/ --------------------------------------------------------------------------------------------------*/


/**
 * @brief Lets the player pick a card among a list if they want
 * 
 * @param cards The available cards to pick from
 * @return Card* The picked card OR nullptr if the player doesn't want to pick
 */
const Card* ConsoleInterface::pickACard_option(std::vector<const Card*> cards) const {
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
        return cards.at(choice-1);
    }
}



const Card* ConsoleInterface::pickACard(std::vector<const Card*> cards) const {
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

    return cards.at(choice-1);
}



const Creature* ConsoleInterface::pickACreature_option(std::vector<const Creature*> cards) const {
    size_t choice;

    do {
        cout << "Pick a creature among these (type the number) :\n";
        size_t k = 1;
        for(auto i = cards.begin(); i != cards.end(); i++) {
            cout << k << ". " << *i << endl;
            k++;
        }
        cout << "0. Don't pick any creature" << endl << endl;
        cout << "Your choice : ";
        cin >> choice;
    } while(choice > cards.size());

    if(choice == 0) {
        return nullptr; // Return if the player doesn't make any choice
    } else {
        return cards.at(choice-1);
    }
}



const Creature* ConsoleInterface::pickACreature(vector<const Creature*> cards) const {
    size_t choice;

    do {
        cout << "Pick a creature among these (type the number) :\n";
        size_t k = 1;
        for(auto i = cards.begin(); i != cards.end(); i++) {
            cout << k << ". " << *i << endl;
            k++;
        }
        cout << "Your choice : ";
        cin >> choice;
    } while(choice == 0 || choice > cards.size());

    return cards.at(choice-1);
}


bool ConsoleInterface::pickYesOrNo() const {
    bool answer;
    
    cout << "\nYour answer (1 for yes, 0 for no) : ";
    cin >> answer;;

    return answer;
}