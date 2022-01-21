 #include "../headers/Duel.hpp"



#include "../headers/Interface.hpp"
#include "../headers/Contender.hpp"
#include "../headers/Card.hpp"
#include "../headers/Creature.hpp"
#include "../headers/actions/FightHit.hpp"




// Getters/setters (Turns related members)
void Duel::addInterface(Interface_interface* i) {
	d_interfaces.push_back(i);
}

// Game phases and exchanges with interfaces
void Duel::start() {
	// TODO
}

void Duel::ph1Draw_start() {
	// TODO
}

void Duel::ph2Disgendage_start() {
	// TODO
}

void Duel::ph3PlayCard_start() {
	// TODO
}

void Duel::chooseCard(Card* c) {
	cout << "Received card in Duel : " << c << "\n"; //! Beware of the fact c can be nullptr
	// TODO
}

void Duel::ph3_end() {
	// TODO
}

void Duel::ph4Fight_start() {
	// TODO
}

void Duel::ph4Fight(Creature att, Contender c, std::list<Creature> def) {
	// TODO
}

void Duel::ph4_end() {
	// TODO
}

void Duel::ph5PlayCard_start() {
	// TODO
}

// chooseCard is called again here
void Duel::ph5_end() {
	// TODO
}

void Duel::ph6Discard_start() {
	// TODO
}

void Duel::ph6_end() {
	// TODO
}
