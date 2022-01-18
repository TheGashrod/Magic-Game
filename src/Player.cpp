

#include "Player.hpp"

//Constructors :
Player::Player (string name): p_name(name) { }

Player::~Player() { };

// Getters :
string Player::getName() const { return p_name; }

// setters :
void Player::setName(string name) { p_name = name; }
