#include "Player.h"
#include "cocos2d.h"
USING_NS_CC;
Player* Player::_instance = nullptr;
int Player:: money = 500;
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
Vec2 Player::getxy() {
    Vec2 worldPos = _instance->getPosition();
   
    int x = static_cast<int>(worldPos.x / 17.83);
    int y = static_cast<int>(30 * 17.83 - worldPos.y) / (17.83);
    CCLOG("player%d %d", x, y);

    return cocos2d::Vec2(x, y);
}

int Player::getmoney() {
    return money;
}
void Player::changemoney(int cost) {
    money = money + cost;
}