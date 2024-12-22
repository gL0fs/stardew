#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Shop : public cocos2d::Layer {
public:
    static Shop* getInstance(); // 获取单例实例

    void displayShop(); // 显示商店
    void displayPlayerMoney();
    void updatePlayerMoneyDisplay(int money);
    void logSelectedItemCoord();
    void buySelectedItemCoord();
    void setVisible(bool visible);
private:
    Shop(); // 私有构造函数，防止外部创建实例
    virtual ~Shop(); // 私有析构函数

    static Shop* _instance; // 单例实例

    cocos2d::TMXTiledMap* _tileMap; // 商店的 TMX 地图
    cocos2d::TMXLayer* _itemsLayer; // 商店的物品层
    cocos2d::Vec2 _selectedItemCoord; // 当前选中的物品坐标

    bool init(); // 初始化函数
    void highlightSelectedItem(); // 高亮显示选中的物品
    bool isWithinShopArea(cocos2d::Vec2 itemCoord); // 检查坐标是否在商店区域内
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); // 键盘事件处理

    // 定义商店区域
    const int SHOP_AREA_START_X = 1;
    const int SHOP_AREA_START_Y = 1;
    const int SHOP_AREA_END_X = 4;
    const int SHOP_AREA_END_Y = 4;
    cocos2d::Label* _moneyLabel = nullptr; // 金钱标签
   
};