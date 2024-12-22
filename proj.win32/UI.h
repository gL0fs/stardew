#pragma once
#ifndef UI_H
#define UI_H

#include "cocos2d.h"
#include "Player.h"

class UI : public cocos2d::Layer {
public:
    static UI* getInstance(); // 单例模式
    void updateUI();          // 更新 UI 显示
    void showUI();            // 显示 UI

private:
    UI(); // 构造函数私有化
    static UI* _instance;     // 单例实例

    // UI 元素
    cocos2d::Label* _healthLabel;
    cocos2d::Label* _staminaLabel;
    cocos2d::Label* _zhongdiLabel;
    cocos2d::Label* _diaoyuLabel;
    cocos2d::Label* _wakuangLabel;
};

#endif // UI_H