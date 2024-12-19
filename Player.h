#ifndef PLAYER_H
#define PLAYER_H

#include "cocos2d.h"
#include <vector>
#include <string>

USING_NS_CC;

class Player : public Sprite {
public:
    static Player* getInstance();

    // ��ҳ�ʼ��
    bool initPlayer(const std::string& spriteFile);

    void setHealth(int health);
    int getHealth() const;

    void setStamina(int stamina);
    int getStamina() const;

    void addItemToInventory(const std::string& item);
    const std::vector<std::string>& getInventory() const;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    Vec2 Player::getxy();//�õ���ҵ�ǰ����Ƭ����
private:
    Player();

    static Player* _instance;

    int _health;
    int _stamina;
    std::vector<std::string> _inventory;

    CC_DISALLOW_COPY_AND_ASSIGN(Player);
};

#endif // PLAYER_H
