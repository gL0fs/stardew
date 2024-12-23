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
    _shopLayer = Shop::getInstance(); // ��ȡ�����̵�ʵ��
    
    CCLOG("shop instance");
    
}
void Player::addzhong()
{
    zhongdi++;
    if (zhongdi >= 100)
        zhongdi = 100;
    UI::getInstance()->updateUI(); // ���� UI
}
void Player::addyu()
{
    diaoyu++;
    if (diaoyu >= 100)
        diaoyu = 100;
    UI::getInstance()->updateUI(); // ���� UI
}
void Player::addkuang()
{
    wakuang++;
    if (wakuang >= 100)
        wakuang = 100;
    UI::getInstance()->updateUI(); // ���� UI
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
        _shopLayer->displayShop(); // ���� Shop �����ʾ����
    }
}
int Player::getmoney()
{
    return money;
}
// ���� player ��һ��ȫ�ֻ��Ա����
void Player::setMoney(int newMoney) {
    money = newMoney;

    // �����̵��еĽ�Ǯ��ʾ
    Shop::getInstance()->updatePlayerMoneyDisplay(newMoney);
}

void Player::showUI() {
    static auto _UI = UI::getInstance();
    CCLOG("uixianshi");
   _UI->showUI(); // ���� UI �����ʾ����
}
void Player::setHealth(int health) {
    static auto _UI = UI::getInstance();
    _health=health;
    _UI->updateUI(); // ���� UI
}
void Player::changeHealth() {
    static auto _UI = UI::getInstance();
    _health--;
    _UI->updateUI(); // ���� UI
}
void Player::loadAnimationFrames() {
    // ���ض���֡
    Vector<SpriteFrame*> downFrames, rightFrames, upFrames, leftFrames;

    for (int i = 1; i <= 16; i++) {
        std::string frameName = std::to_string(i) + ".png"; // ֡�ļ���

        // ��������
        auto texture = Director::getInstance()->getTextureCache()->addImage(frameName);
        if (!texture) {
            CCLOG("Failed to load texture: %s", frameName.c_str());
            continue;
        }

        // ���� SpriteFrame
        auto frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
        if (!frame) {
            CCLOG("Failed to create frame: %s", frameName.c_str());
            continue;
        }

        // ��ȡԭʼ�� rect
        auto rect = frame->getRect();

        // �Ŵ� rect 2.5 ��
        auto newRect = Rect(rect.origin.x, rect.origin.y, rect.size.width * 2.5f, rect.size.height * 2.5f);

        // �����µ� SpriteFrame
        auto newFrame = SpriteFrame::createWithTexture(texture, newRect, frame->isRotated(), frame->getOffset(), frame->getOriginalSize());

        // ����֡��ŷ��䵽��ͬ�ķ���
        if (i >= 1 && i <= 4) {
            downFrames.pushBack(newFrame); // �·���
        }
        else if (i >= 5 && i <= 8) {
            rightFrames.pushBack(newFrame); // �ҷ���
        }
        else if (i >= 9 && i <= 12) {
            upFrames.pushBack(newFrame); // �Ϸ���
        }
        else if (i >= 13 && i <= 16) {
            leftFrames.pushBack(newFrame); // ����
        }
    }

    // ��������
    if (downFrames.empty() || rightFrames.empty() || upFrames.empty() || leftFrames.empty()) {
        CCLOG("Error: Some animation frames are missing!");
        return;
    }

    _playerAnimation[0] = Animation::createWithSpriteFrames(downFrames, 0.1f); // ��
    _playerAnimation[1] = Animation::createWithSpriteFrames(rightFrames, 0.1f); // ��
    _playerAnimation[2] = Animation::createWithSpriteFrames(upFrames, 0.1f); // ��
    _playerAnimation[3] = Animation::createWithSpriteFrames(leftFrames, 0.1f); // ��

    // ���涯��
    for (int i = 0; i < 4; i++) {
        _playerAnimation[i]->retain();
    }
}