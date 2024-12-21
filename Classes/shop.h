#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Shop : public cocos2d::Layer {
public:
    static Shop* getInstance(); // ��ȡ����ʵ��

    void displayShop(); // ��ʾ�̵�
    void displayPlayerMoney();
    void updatePlayerMoneyDisplay(int money);
    void logSelectedItemCoord();
private:
    Shop(); // ˽�й��캯������ֹ�ⲿ����ʵ��
    virtual ~Shop(); // ˽����������

    static Shop* _instance; // ����ʵ��

    cocos2d::TMXTiledMap* _tileMap; // �̵�� TMX ��ͼ
    cocos2d::TMXLayer* _itemsLayer; // �̵����Ʒ��
    cocos2d::Vec2 _selectedItemCoord; // ��ǰѡ�е���Ʒ����

    bool init(); // ��ʼ������
    void highlightSelectedItem(); // ������ʾѡ�е���Ʒ
    bool isWithinShopArea(cocos2d::Vec2 itemCoord); // ��������Ƿ����̵�������
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); // �����¼�����

    // �����̵�����
    const int SHOP_AREA_START_X = 1;
    const int SHOP_AREA_START_Y = 1;
    const int SHOP_AREA_END_X = 4;
    const int SHOP_AREA_END_Y = 4;
    cocos2d::Label* _moneyLabel = nullptr; // ��Ǯ��ǩ
   
};