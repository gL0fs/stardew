#ifndef PLAYER_H
#define PLAYER_H

#include "cocos2d.h"
#include "Backpack.h"
#include <vector>
#include <string>

#include "shop.h"
#include "UI.h"
USING_NS_CC;

class Player : public Sprite {
public:
    static Player* getInstance();

    // 玩家初始化
    bool initPlayer(const std::string& spriteFile);

    void setHealth(int health);
    void changeHealth();
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

    void displayShop(); // 显示商店
    int Player::getmoney();
    void Player::setMoney(int newMoney);
    void addzhong();
    void addyu();
    void addkuang();

    void showUI(); // 添加显示 UI 的方法
    int diaoyu;
    int wakuang;
    int zhongdi;
private:
    Player();
    static int money;

    
    static Player* _instance;

    

    int _health;
    int _stamina;
    Inventory* _inventory;
    Shop* _shopLayer; // 商店层
    
    CC_DISALLOW_COPY_AND_ASSIGN(Player);
    
};

#endif // PLAYER_H
