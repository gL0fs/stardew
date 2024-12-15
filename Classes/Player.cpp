#include "Player.h"

Player* Player::_instance = nullptr;

Player::Player() : _health(100), _stamina(100) {}

Player* Player::getInstance() {
    if (!_instance) {
        _instance = new (std::nothrow) Player();
    }
    return _instance;
}

bool Player::initPlayer(const std::string& spriteFile) {
    if (!this->initWithFile(spriteFile)) {
        return false;
    }
    this->setAnchorPoint(Vec2(0.5,0));
    return true;
}

void Player::setHealth(int health) {
    _health = health;
}

int Player::getHealth() const {
    return _health;
}

void Player::setStamina(int stamina) {
    _stamina = stamina;
}

int Player::getStamina() const {
    return _stamina;
}

void Player::addItemToInventory(const std::string& item) {
    _inventory.push_back(item);
}

const std::vector<std::string>& Player::getInventory() const {
    return _inventory;
}

void Player::moveUp() {
    this->setPositionY(this->getPositionY() + 10);
}

void Player::moveDown() {
    this->setPositionY(this->getPositionY() - 10);
}

void Player::moveLeft() {
    this->setPositionX(this->getPositionX() - 10);
}

void Player::moveRight() {
    this->setPositionX(this->getPositionX() + 10);
}