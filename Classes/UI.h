#pragma once
#ifndef UI_H
#define UI_H

#include "cocos2d.h"
#include "Player.h"

class UI : public cocos2d::Layer {
public:
    static UI* getInstance(); // ����ģʽ
    void updateUI();          // ���� UI ��ʾ
    void showUI();            // ��ʾ UI
   
private:
    UI(); // ���캯��˽�л�
    static UI* _instance;     // ����ʵ��

    // UI Ԫ��
    cocos2d::Label* _healthLabel;
    cocos2d::Label* _staminaLabel;
    cocos2d::Label* _zhongdiLabel;
    cocos2d::Label* _diaoyuLabel;
    cocos2d::Label* _wakuangLabel;
};

#endif   // UI_H