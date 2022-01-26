#include "../../headers/consoleInterface/ConsoleInterface.hpp"


#include <iostream>

#include "../../headers/Duel.hpp"
#include "../../headers/Card.hpp"
#include "../../headers/Creature.hpp"
#include "../../headers/Land.hpp"
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
    cout << endl << con << " You draw a card : \n" << card << "\n";
}




void ConsoleInterface::ph2Disengage(const Contender* con, const std::list<const Card*> c) {
    cout << endl << con << " Your in-game cards have been disengaged :" << endl;
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
    cout << "ConsoleInterface::ph3PlayCards_wait 0" << endl;
    cout << endl << con << " You can put cards from your hand into the game." << endl;
    auto cardsTemp = con->getHand().getCardsSet();
    cout << "ConsoleInterface::ph3PlayCards_wait 0.1" << endl;
    const Card* picked = pickACard_option( cardsTemp );
    cout << "ConsoleInterface::ph3PlayCards_wait 0.2" << endl;
    
    if(picked == nullptr) {
        i_duel->ph3_end();
    }
    else {
        
        cout << "ConsoleInterface::ph3PlayCards_wait 0.3" << endl;
        vector<const Land*> specificCost = vector<const Land*>();
        vector<const Land*> anyCost = vector<const Land*>();
        
        cout << "ConsoleInterface::ph3PlayCards_wait 0.4" << endl;

        shared_ptr<Card> ptr = picked->clone();
        //CardsSet(vector<Card*>({&(*ptr)}));
        Card* card = &(*ptr);
        cout << "c obtained from ID : " << card << endl;

        if(!card->isLand())
        if( Creature* c = dynamic_cast<Creature*>(card) ) {
            
            cout << "ConsoleInterface::ph3PlayCards_wait 1" << endl;
            cout << c << endl;
            cout << "ConsoleInterface::ph3PlayCards_wait 1.0" << endl;

            // Picking the specific lands
            std::list<Color> costs = c->getColorCost();
            cout << "ConsoleInterface::ph3PlayCards_wait 1.1" << endl;
            size_t remainingColors = costs.size();
            for(auto cost = costs.begin(); cost != costs.end(); cost++) {
                cout << "ConsoleInterface::ph3PlayCards_wait 1.2" << endl;
                cout << endl << con << " You must pick a " <<  *cost << " land, " << remainingColors << " other specific land(s) and " << c->getAnyCost() << " land(s) of any type to invoke " << c->getName() << "." << endl
                << con << " You will now pick the first asked land." << endl;
                cout << "ConsoleInterface::ph3PlayCards_wait 1.3" << endl;
                const Land* land = pickALand_option( con->getInGameCards().getLands() );
                cout << "ConsoleInterface::ph3PlayCards_wait 1.4" << endl;
                if(land == nullptr) {
                    cout << con << " Aborting creature invokation." << endl;
                    ph3PlayCards_wait(con);
                    return;
                }
                cout << "ConsoleInterface::ph3PlayCards_wait 1.5" << endl;
                specificCost.push_back(land);
                cout << "ConsoleInterface::ph3PlayCards_wait 1.6" << endl;
                remainingColors--;
            }
            
            
            cout << "ConsoleInterface::ph3PlayCards_wait 2" << endl;

            // Picking the "any" lands
            for(remainingColors = c->getAnyCost(); remainingColors > 0; remainingColors--) {
                cout << endl << con << " You must now pick " << remainingColors << " land(s) of any color." << endl;
                const Land* land = pickALand_option( con->getInGameCards().getLands() );
                if(land == nullptr) {
                    cout << con << " Aborting creature invokation." << endl;
                    ph3PlayCards_wait(con);
                    return;
                }
                anyCost.push_back(land);
            }

            
            cout << "ConsoleInterface::ph3PlayCards_wait 3";
        }


        i_duel->chooseCard( picked, specificCost, anyCost );
    }
}




void ConsoleInterface::ph4Fight_wait(const Contender* att, const Contender* def) {
    
    if( att->getInGameCards().getDisengaged().getCreatures().size() > 0 ) {
    
        cout << endl << att << " Do you want to attack " << def->getPlayer().getName() << " ?";
        bool isAttacking = pickYesOrNo();
        
        if(isAttacking) {

            cout << endl << att << " Pick your attacking creature." << endl;
            const Creature* attCreature = pickACreature( att->getInGameCards().getDisengaged().getCreatures() );
            
            cout << endl << def << " Action from " << def->getPlayer().getName() << endl;
            vector<const Creature*> defCreatures = vector<const Creature*>();
            bool mustContinue = true;
            vector<const Creature*> defCandidates = def->getInGameCards().getDisengaged().getCreatures();
            do {
                cout << endl << def << " Pick a defending creature. (you can pick multiple ones till you type 0)" << endl;
                const Creature* c = pickACreature_option( defCandidates );
                if(c == nullptr) {
                    mustContinue = false;
                }
                else {
                    defCreatures.push_back(c);

                    // Removing from the pickable creatures
                    auto altC = defCandidates.begin();
                    bool hasDeleted = false;
                    cout << "ph4 interface remove from pickable 1" << endl;
                    while(!hasDeleted && altC != defCandidates.end()) {
                        cout << "ph4 interface remove from pickable 2" << endl;
                        if((*altC)->hasSameId(c)) {
                             cout << "ph4 interface remove from pickable 3" << endl;
                            defCandidates.erase( altC );
                            hasDeleted = true;
                        }
                        cout << "ph4 interface remove from pickable 4" << endl;
                        altC++;
                        cout << "ph4 interface remove from pickable 5" << endl;
                    }
                    cout << "ph4 interface remove from pickable 6" << endl;
                }
            } while(mustContinue);

            // Notifying Duel
            i_duel->ph4Fight(attCreature, defCreatures);
            
        }
        else
            i_duel->ph4_end();
    }
    else {
        cout << endl << att << " You do not have any creature able to attack. Skipping fight phase." << endl;
        i_duel->ph4_end();
    }
}




void ConsoleInterface::ph5PlayCards_wait(const Contender* con) {
    cout << endl << con << " You can put cards from your hand into the game again." << endl;
    const Card* picked = pickACard_option( con->getHand().getCardsSet() );
    
    if(picked == nullptr) {
        i_duel->ph5_end();
    }
    else {
        //i_duel->chooseCard( picked );
    }
}




void ConsoleInterface::ph6Discard_wait(const Contender* con, size_t nbToDiscard) {
    // boucler sur nb to discard en demandant quelle carte envoyer au cimetière sur la hand du joueur
    std::vector<const Card*> discarded = {};

    for (int i=nbToDiscard; i>0; i--){
        cout << endl << con << " You have an excessive number of cards. You must send " << i << " card(s) from your hand to the cemetary." << endl;
        discarded.push_back(pickACard(con->getHand().getCardsSet()));
    }

    i_duel->ph6_end(discarded);
}





/* --------------------------------------------------------------------------------------------------/
                                          User actions
/ --------------------------------------------------------------------------------------------------*/



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




const Land* ConsoleInterface::pickALand(std::vector<const Land*> cards) const {
    size_t choice;

    do {
        cout << "Pick a land among these (type the number) :\n";
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



const Land* ConsoleInterface::pickALand_option(std::vector<const Land*> cards) const {
    size_t choice;

    do {
        cout << "Pick a land among these (type the number) :\n";
        size_t k = 1;
        for(auto i = cards.begin(); i != cards.end(); i++) {
            cout << k << ". " << *i << endl;
            k++;
        }
        cout << "0. Don't pick any land" << endl << endl;
        cout << "Your choice : ";
        cin >> choice;
    } while(choice > cards.size());

    if(choice == 0) {
        return nullptr; // Return if the player doesn't make any choice
    } else {
        return cards.at(choice-1);
    }
}



bool ConsoleInterface::pickYesOrNo() const {
    bool answer;
    
    cout << "\nYour answer (1 for yes, 0 for no) : ";
    cin >> answer;;

    return answer;
}