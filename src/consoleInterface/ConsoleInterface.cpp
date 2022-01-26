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
    cout << endl;
    cout << "\033[1;32m(======================================== DRAWING A CARD ========================================)" << endl;
    cout << con << " You draw a card : \n" << card << "\n";
}




void ConsoleInterface::ph2Disengage(const Contender* con, const std::list<const Card*> c) {
    cout << endl;
    cout << "\033[1;32m(======================================= DISENGAGING CARDS =======================================)" << endl;
    cout << con << " Your in-game cards have been disengaged :" << endl;
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

    // print contender Game vision :
    contenderGameVision();

    cout << "\033[38;5;153m= INVOCATION PHASE ===/" << endl;

    cout << endl << "\033[38;5;202m" << con << "\033[38;5;202m You can put cards from your hand into the game." << endl;
    
    std::vector<const Card*> pickableCards;
    if(i_duel->getRemainingLands() > 0) {
        pickableCards = con->getHand().getCardsSet();
    }
    else {
        pickableCards = con->getHand().getNotLands().getCardsSet();
    }
    
    
    const Card* picked = pickACard_option( pickableCards );
    // cout << "ConsoleInterface::ph3PlayCards_wait 0.2" << endl;
    
    if(picked == nullptr) {
        i_duel->ph3_end();
    }
    else {

        
        // cout << "ConsoleInterface::ph3PlayCards_wait 0.3" << endl;
        vector<const Land*> specificCost = vector<const Land*>();
        vector<const Land*> anyCost = vector<const Land*>();
        
        // cout << "ConsoleInterface::ph3PlayCards_wait 0.4" << endl;


        shared_ptr<Card> ptr = picked->clone();
        //CardsSet(vector<Card*>({&(*ptr)}));
        Card* card = &(*ptr);

        if(!card->isLand())
        if( Creature* c = dynamic_cast<Creature*>(card) ) {

            
            // cout << "ConsoleInterface::ph3PlayCards_wait 1" << endl;
            cout << c << endl;
            // cout << "ConsoleInterface::ph3PlayCards_wait 1.0" << endl;


            // Picking the specific lands
            std::list<Color> costs = c->getColorCost();
            vector<const Land*> availableCol = con->getInGameCards().getDisengaged().getLands();
            size_t remainingColors = costs.size();
            for(auto cost = costs.begin(); cost != costs.end(); cost++) {
                cout << endl << "\033[38;5;202m" << con << "\033[38;5;202m You must pick a " <<  *cost << " land, " << remainingColors-1 << " other specific land(s) and " << c->getAnyCost() << " land(s) of any type to invoke " << c->getName() << "." << endl
                << con << "\033[38;5;202m You will now pick the first asked land.";

                const Land* land; // Force the player to give the right color of land
                do {
                    cout << endl;
                    land = pickALand_option( availableCol );
                } while( !(land == nullptr || *land->getColor().begin() == *cost) );
                for(auto land2 = availableCol.begin(); land2 != availableCol.end(); land2++) { // Removing from the pickable list
                    if(land == (*land2)) {
                        availableCol.erase(land2);
                        break;
                    }
                }

                // cout << "ConsoleInterface::ph3PlayCards_wait 1.4" << endl;

                if(land == nullptr) {
                    cout << "\033[1;32m" << con << "\033[1;32m Aborting creature invokation." << endl;
                    ph3PlayCards_wait(con);
                    return;
                }

                // cout << "ConsoleInterface::ph3PlayCards_wait 1.5" << endl;
                specificCost.push_back(land);
                // cout << "ConsoleInterface::ph3PlayCards_wait 1.6" << endl;
                remainingColors--;
            }
            
 

            // Picking the "any" lands
            for(remainingColors = c->getAnyCost(); remainingColors > 0; remainingColors--) {
                cout << endl << "\033[38;5;202m" << con << "\033[38;5;202m You must now pick " << remainingColors << " land(s) of any color." << endl;
                const Land* land = pickALand_option( availableCol );
                if(land == nullptr) {
                    cout << "\033[1;32m" << con << "\033[1;32m Aborting creature invokation." << endl;
                    ph3PlayCards_wait(con);
                    return;
                }
                anyCost.push_back(land);
            }


            
            // cout << "ConsoleInterface::ph3PlayCards_wait 3";

        }else{
            if(i_duel->getRemainingLands() > 0){
                ph3PlayCards_wait(con);
                return;
            }
        }


        i_duel->chooseCard( picked, specificCost, anyCost );
    }
}




void ConsoleInterface::ph4Fight_wait(const Contender* att, const Contender* def) {
    

    // print  contender Game vision :
    contenderGameVision();
    cout << "\033[38;5;153m= FIGHT PHASE ===/" << endl;


    if( att->getInGameCards().getDisengaged().getCreatures().size() > 0 ) {
    
        cout << endl << "\033[38;5;202m" << att << "\033[38;5;202m Do you want to attack " << def->getPlayer().getName() << " ?";
        bool isAttacking = pickYesOrNo();
        
        if(isAttacking) {

            cout << endl << "\033[38;5;202m" << att << "\033[38;5;202m Pick your attacking creature." << endl;
            const Creature* attCreature = pickACreature( att->getInGameCards().getDisengaged().getCreatures() );
            
            cout << endl << "\033[1;32m" << def << "\033[1;32m Action from " << def->getPlayer().getName() << endl;
            vector<const Creature*> defCreatures = vector<const Creature*>();
            bool mustContinue = true;
            vector<const Creature*> defCandidates = def->getInGameCards().getDisengaged().getCreatures();
            do {
                contenderOposentGameVision();
                cout << endl << "\033[38;5;202m" << def << "\033[38;5;202m Pick a defending creature. (you can pick multiple ones till you type 0)" << endl;
                const Creature* c = pickACreature_option( defCandidates );
                if(c == nullptr) {
                    mustContinue = false;
                }
                else {
                    defCreatures.push_back(c);

                    // Removing from the pickable creatures
                    auto altC = defCandidates.begin();
                    bool hasDeleted = false;
                    while(!hasDeleted && altC != defCandidates.end()) {
                        if((*altC)->hasSameId(c)) {
                            defCandidates.erase( altC );
                            hasDeleted = true;
                        }
                        altC++;
                    }
                }
            } while(mustContinue);

            // Notifying Duel
            i_duel->ph4Fight(attCreature, defCreatures);
            
        }
        else
            i_duel->ph4_end();
    }
    else {
        cout << endl << "\033[38;5;202m" << att << "\033[38;5;202m You do not have any creature able to attack. Skipping fight phase." << endl;
        i_duel->ph4_end();
    }
}




void ConsoleInterface::ph5PlayCards_wait(const Contender* con) {

    // print  contender Game vision :
    contenderGameVision();
    cout << "\033[38;5;153m= INVOCATION PHASE 2 ===/" << endl;
    cout << endl << "\033[38;5;202m" << con << "\033[38;5;202m You can put cards from your hand into the game again." << endl;


    std::vector<const Card*> pickableCards;
    if(i_duel->getRemainingLands() > 0) {
        pickableCards = con->getHand().getCardsSet();
    }
    else {
        pickableCards = con->getHand().getNotLands().getCardsSet();
    }
    
    const Card* picked = pickACard_option( pickableCards );
    
    if(picked == nullptr) {
        i_duel->ph5_end();
    }
    else {
        vector<const Land*> specificCost = vector<const Land*>();
        vector<const Land*> anyCost = vector<const Land*>();

        shared_ptr<Card> ptr = picked->clone();
        //CardsSet(vector<Card*>({&(*ptr)}));
        Card* card = &(*ptr);

        if(!card->isLand())
        if( Creature* c = dynamic_cast<Creature*>(card) ) {

            // Picking the specific lands
            std::list<Color> costs = c->getColorCost();
            vector<const Land*> availableCol = con->getInGameCards().getDisengaged().getLands();
            size_t remainingColors = costs.size();
            for(auto cost = costs.begin(); cost != costs.end(); cost++) {
                cout << endl << "\033[38;5;202m" << con << "\033[38;5;202m You must pick a " <<  *cost << " land, " << remainingColors-1 << " other specific land(s) and " << c->getAnyCost() << " land(s) of any type to invoke " << c->getName() << "." << endl
                << "\033[38;5;202m" << con << " You will now pick the first asked land.";
                
                const Land* land; // Force the player to give the right color of land
                do {
                    cout << endl;
                    land = pickALand_option( availableCol );
                } while( !(land == nullptr || *land->getColor().begin() == *cost) );

                for(auto land2 = availableCol.begin(); land2 != availableCol.end(); land2++) { // Removing from the pickable list
                    if(land == (*land2)) {
                        availableCol.erase(land2);
                        break;
                    }
                }
                if(land == nullptr) {
                    cout << "\033[1;32m" << con << "\033[1;32m Aborting creature invokation." << endl;
                    ph5PlayCards_wait(con);
                    return;
                }
                specificCost.push_back(land);
                remainingColors--;
            }
            

            // Picking the "any" lands
            for(remainingColors = c->getAnyCost(); remainingColors > 0; remainingColors--) {
                cout << endl << "\033[38;5;202m" << con << "\033[38;5;202m You must now pick " << remainingColors << " land(s) of any color." << endl;
                const Land* land = pickALand_option( availableCol );
                if(land == nullptr) {
                    cout << "\033[1;32m" << con << "\033[1;32m Aborting creature invokation." << endl;
                    ph5PlayCards_wait(con);
                    return;
                }
                anyCost.push_back(land);
            }

        }


        i_duel->chooseCard( picked, specificCost, anyCost );
    }
}




void ConsoleInterface::ph6Discard_wait(const Contender* con, size_t nbToDiscard) {

    cout << endl;
    cout << "\033[1;32m(======================================= DISCARD PHASE =======================================)" << endl;


    // boucler sur nb to discard en demandant quelle carte envoyer au cimetière sur la hand du joueur
    std::vector<const Card*> discarded = {};

    for (int i=nbToDiscard; i>0; i--){
        cout << endl << "\033[38;5;202m" << con << "\033[38;5;202m You have an excessive number of cards. You must send " << i << " card(s) from your hand to the cemetary." << endl;
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
        cout << "\033[38;5;202mPick a card among these (type the number) :\n\033[38;5;181m";
        size_t k = 1;
        for(auto i = cards.begin(); i != cards.end(); i++) {
            cout << k << ". " << *i << endl;
            k++;
        }
        cout << "\033[38;5;202mYour choice : ";
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
        cout << "\033[38;5;202mPick a card among these (type the number) :\n\033[38;5;181m";
        size_t k = 1;
        for(auto i = cards.begin(); i != cards.end(); i++) {
            cout << k << ". " << *i << endl;
            k++;
        }
        cout << "0. Don't pick any card" << endl << endl;
        cout << "\033[38;5;202mYour choice : ";
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
        cout << "\033[38;5;202mPick a creature among these (type the number) :\n\033[38;5;181m";
        size_t k = 1;
        for(auto i = cards.begin(); i != cards.end(); i++) {
            cout << k << ". " << *i << endl;
            k++;
        }
        cout << "\033[38;5;202mYour choice : ";
        cin >> choice;
    } while(choice == 0 || choice > cards.size());

    return cards.at(choice-1);
}



const Creature* ConsoleInterface::pickACreature_option(std::vector<const Creature*> cards) const {
    size_t choice;

    do {
        cout << "\033[38;5;202mPick a creature among these (type the number) :\n\033[38;5;181m";
        size_t k = 1;
        for(auto i = cards.begin(); i != cards.end(); i++) {
            cout << k << ". " << *i << endl;
            k++;
        }
        cout << "0. Don't pick any creature" << endl << endl;
        cout << "\033[38;5;202mYour choice : ";
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
        cout << "\033[38;5;202mPick a land among these (type the number) :\n\033[38;5;181m";
        size_t k = 1;
        for(auto i = cards.begin(); i != cards.end(); i++) {
            cout << k << ". " << *i << endl;
            k++;
        }
        cout << "\033[38;5;202mYour choice : ";
        cin >> choice;
    } while(choice == 0 || choice > cards.size());

    return cards.at(choice-1);
}



const Land* ConsoleInterface::pickALand_option(std::vector<const Land*> cards) const {
    size_t choice;

    do {
        cout << "\033[38;5;202mPick a land among these (type the number) :\n\033[38;5;181m";
        size_t k = 1;
        for(auto i = cards.begin(); i != cards.end(); i++) {
            cout << k << ". " << *i << endl;
            k++;
        }
        cout << "0. Don't pick any land" << endl << endl;
        cout << "\033[38;5;202mYour choice : ";
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
    
    cout << "\n\033[38;5;202mYour answer (1 for yes, 0 for no) : ";
    cin >> answer;;

    return answer;
}



/* --------------------------------------------------------------------------------------------------/
                                         Print the board
/ --------------------------------------------------------------------------------------------------*/



void ConsoleInterface::contenderGameVision(){

    cout << endl;
    cout << "\033[38;5;39m(==============================// BOARD (Perspective from " << i_duel->getCurrentContender() << ") \\\\==============================)" << endl;
    cout << "\033[38;5;63m---- In game cards from " << *i_duel->getOtherContender() << " : " << *i_duel->getOtherContender()->getOriginalInGameCards();
    cout << "\033[38;5;63m---- In game cards from " << *i_duel->getCurrentContender() << " : " << *i_duel->getCurrentContender()->getOriginalInGameCards();
    cout << "\033[38;5;39m(============================================================================================)" << endl;
    cout << "---- Your hand : " << *i_duel->getCurrentContender()->getOriginalHand();
    cout << "\033[38;5;39m(============================================================================================)" << endl;
}


void ConsoleInterface::contenderOposentGameVision(){

    cout << "\033[38;5;39m(==============================// BOARD (Perspective from " << i_duel->getOtherContender() << ") \\\\==============================)" << endl;
    cout << "\033[38;5;63m---- In game cards from " << *i_duel->getCurrentContender() << " : " << *i_duel->getCurrentContender()->getOriginalInGameCards();
    cout << "\033[38;5;63m---- In game cards from " << *i_duel->getOtherContender() << " : " << *i_duel->getOtherContender()->getOriginalInGameCards();
    cout << "\033[38;5;39m(============================================================================================)" << endl;
    cout << "---- Your hand : " << *i_duel->getOtherContender()->getOriginalHand();
    cout << "\033[38;5;39m(============================================================================================)" << endl;
}