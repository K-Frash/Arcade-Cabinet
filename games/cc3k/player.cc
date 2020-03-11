#include "player.h"
#include "hero.h"
#include <string> 
#include <iostream>
Player::Player(Hero* hero): hero(hero) {
	
}

Player::~Player() {
	delete hero;
}

// tells hero to move in a direction (player input captured at an earlier step)
void Player::move(std::string direction) {
	hero->Move(direction);
}

// reads player input and tells hero to attack in that direction
void Player::attack() {
	std::string direction;
	std::cin >> direction;
	hero->Attack(direction);
}

// reads player input and tells hero to consume in that direction
void Player::consume() {
	std::string direction;
	std::cin >> direction;
	hero->Consume(direction);
}

Hero* Player::getHero() {
	return hero;
}

bool Player::isDead() {
	return hero->getHp() > 0 ? false : true;
}

int Player::getScore() {
	return hero->getScore();
}