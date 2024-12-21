#include "Player.h"
#include "cocos2d.h"
#include "UI.h"
USING_NS_CC;
Player* Player::_instance = nullptr;
int Player::money = 500;
Player::Player()
    : _health(100),
    _stamina(100),
    zhongdi(0), diaoyu(0), wakuang(0),
    _inventory(nullptr){
    _inventory = new Inventory(36); 
    _shopLayer = Shop::getInstance(); // 获取单例商店实例
    
    CCLOG("shop instance");
    
}
void Player::addzhong()
{
    zhongdi++;
    if (zhongdi >= 100)
        zhongdi = 100;
    UI::getInstance()->updateUI(); // 更新 UI
}
void Player::addyu()
{
    diaoyu++;
    if (diaoyu >= 100)
        diaoyu = 100;
    UI::getInstance()->updateUI(); // 更新 UI
}
void Player::addkuang()
{
    wakuang++;
    if (wakuang >= 100)
        wakuang = 100;
    UI::getInstance()->updateUI(); // 更新 UI
}
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



int Player::getHealth() const {
    return _health;
}

void Player::setStamina(int stamina) {
    _stamina = stamina;
}

int Player::getStamina() const {
    return _stamina;
}

void Player::addInventory(const std::string& name, int quantity) {
    _inventory->addItemToInventory(name, quantity);
}

void Player::removeInventory(const std::string& name, int quantity) {
    _inventory->removeItem(name, quantity);
}

Inventory* Player::getInventory() {
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
void Player::displayShop() {
    _shopLayer = Shop::getInstance();
    if (_shopLayer) {
        CCLOG("diaoyong");
        _shopLayer->displayShop(); // 调用 Shop 类的显示函数
    }
}
int Player::getmoney()
{
    return money;
}
// 假设 player 是一个全局或成员变量
void Player::setMoney(int newMoney) {
    money = newMoney;

    // 更新商店中的金钱显示
    Shop::getInstance()->updatePlayerMoneyDisplay(newMoney);
}

void Player::showUI() {
    static auto _UI = UI::getInstance();
    CCLOG("uixianshi");
   _UI->showUI(); // 调用 UI 类的显示函数
}
void Player::setHealth(int health) {
    static auto _UI = UI::getInstance();
    _health=health;
    _UI->updateUI(); // 更新 UI
}
void Player::changeHealth() {
    static auto _UI = UI::getInstance();
    _health--;
    _UI->updateUI(); // 更新 UI
}
