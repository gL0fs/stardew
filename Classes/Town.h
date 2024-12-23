#pragma once
#ifndef __TOWN_H__
#define __TOWN_H__

#include "BaseMapLayer.h"
#include "Player.h"
#include "Mine.h"
#include "MainMenuScene.h"
#include "Toolbar.h"
#include "ui/CocosGUI.h"
#include "Forest.h"


class NPC : public cocos2d::Sprite {
public:
    NPC();  // ���캯��
    void setAffection(int value);  // ���úøж�
    int getAffection();  // ��ȡ��ǰ�øж�
    std::string getName();  // ��ȡ NPC ����
    void setName(std::string new_name);  // ���� NPC ����

    cocos2d::Rect npcrec;  // NPC �ľ�������

private:
    int affection;  // NPC �øж�
    std::string name;  // NPC ����
};

class Town : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene(const std::string& spawnPointName);
    static Town* create(const std::string& spawnPointName);
    void loadNPCsFromTMX(cocos2d::TMXTiledMap* _map);
    bool init() override;
    void showGiftSuccessDialog(NPC* npc, const std::string giftType, int affectionChange);
    void giveGift(NPC* npc, const std::string giftType);
    void showGiftDialog(NPC* npc);
    void checkPlayerInteractionWithNPC(NPC* npc, const cocos2d::Vec2& nextPosition);
    void update(float delta);
       

protected:
    Town();
    virtual ~Town();

private:
    bool initMap(const std::string& spawnPointName) override;
    std::vector<NPC*> npcs;
    std::vector<std::string> npcs_name;
};



#endif // __MAP1_H__