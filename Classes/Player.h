#ifndef PLAYER_H
#define PLAYER_H

#include "cocos2d.h"
#include "Backpack.h"
#include <vector>
#include <string>

USING_NS_CC;

class Player : public Sprite {
public:
    static Player* getInstance();

    // 玩家初始化
    bool initPlayer(const std::string& spriteFile);

    void setHealth(int health);
    int getHealth() const;

    void setStamina(int stamina);
    int getStamina() const;

    Inventory* Player::getInventory();
    void addInventory(const std::string& name, int quantity);
    void removeInventory(const std::string& name, int quantity);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    Vec2 Player::getxy();//得到玩家当前的瓦片坐标
private:
    Player();

    static Player* _instance;

    int _health;
    int _stamina;
    Inventory* _inventory;

    CC_DISALLOW_COPY_AND_ASSIGN(Player);
};

#endif // PLAYER_H
