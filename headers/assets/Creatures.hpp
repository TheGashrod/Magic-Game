#ifndef __MTG_CREATURE_ASSETS_INCLUDED__
#define __MTG_CREATURE_ASSETS_INCLUDED__


#include <vector>


#include "../../headers/Creature.hpp"


vector<Creature> creaturesList = vector<Creature>({
Creature("Demon of Pagaille", std::list<Color>({Blue, Red}), false, std::list<Color>({Red, Black}), 1, 3, 3),
Creature("The purple scare", std::list<Color>({Black}), false, std::list<Color>({Red, Blue}), 0, 2, 3),
Creature("Ajani Goldmane", std::list<Color>({White, Red}), false, std::list<Color>({Green, Green}), 2, 3, 4),
Creature("Griffin Sentinel", std::list<Color>({Black, Green}), false, std::list<Color>({Black, Blue}), 1, 1, 2),
Creature("Armored Ascension", std::list<Color>({Blue, White}), false, std::list<Color>({Blue, White}), 0, 2, 3),
Creature("Baneslayer Angel", std::list<Color>({White, Red, Green}), false, std::list<Color>({Green, White}), 0, 2, 2),
Creature("Blinding Mage", std::list<Color>({Blue}), false, std::list<Color>({Blue, White}), 1, 2, 1),
Creature("Captain of the Watch", std::list<Color>({White}), false, std::list<Color>({Red, Red}), 3, 1, 1),
Creature("Elite Vanguard", std::list<Color>({Red}), false, std::list<Color>({Black, White}), 2, 2, 2),
Creature("Siege Mastodon", std::list<Color>({Red, Black}), false, std::list<Color>({Red, Blue}), 1, 3, 3),
Creature("Serra Angel", std::list<Color>({Green, Blue}), false, std::list<Color>({Black, Green}), 0, 2, 3),
Creature("Coral Merfolk", std::list<Color>({Black}), false, std::list<Color>({Red, Blue}), 0, 2, 3),
Creature("Djinn of Wishes", std::list<Color>({White, Red}), false, std::list<Color>({Green, Green}), 2, 3, 4),
Creature("Horned Turtle", std::list<Color>({Black, Green}), false, std::list<Color>({Black, Blue}), 1, 1, 2),
Creature("Illusionary Servant", std::list<Color>({Blue, White}), false, std::list<Color>({Blue, White}), 0, 2, 3),
Creature("Merfolk Looter", std::list<Color>({White, Red, Green}), false, std::list<Color>({Green, White}), 0, 2, 2),
Creature("Merfolk Sovereign", std::list<Color>({Blue}), false, std::list<Color>({Blue, White}), 1, 2, 1),
Creature("Phantom Warrior", std::list<Color>({White}), false, std::list<Color>({Red, Red}), 3, 1, 1),
Creature("Sage Owl", std::list<Color>({Red}), false, std::list<Color>({Black, White}), 2, 2, 2),
Creature("Black Knight", std::list<Color>({Red, Black}), false, std::list<Color>({Red, Blue}), 1, 3, 3),
Creature("Acolyte of Xathrid", std::list<Color>({Green, Blue}), false, std::list<Color>({Black, Green}), 0, 2, 3)

});


#endif