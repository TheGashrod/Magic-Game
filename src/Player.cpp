

#include "../headers/Player.hpp"



//Constructors :
Player::Player (string name, CardsSet deck): p_username(name), p_deck(deck) { }
Player::~Player() { };

// Getters :
string Player::getName() const { return p_username; }
CardsSet Player::getDeck() const { return p_deck; }

// setters :
void Player::setName(string name) { p_username = name; }
