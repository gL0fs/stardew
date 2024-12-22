#include "UI.h"

UI* UI::_instance = nullptr;

 UI::UI() {
     // ��ȡ��Ļ�ߴ�
     auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
     cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

     // ��ʼ�� UI Ԫ��
     _healthLabel = cocos2d::Label::createWithSystemFont("Health: 100", "Arial", 24);
     _staminaLabel = cocos2d::Label::createWithSystemFont("Stamina: 100", "Arial", 24);
     _zhongdiLabel = cocos2d::Label::createWithSystemFont("Zhongdi: 0", "Arial", 24);
     _diaoyuLabel = cocos2d::Label::createWithSystemFont("Diaoyu: 0", "Arial", 24);
     _wakuangLabel = cocos2d::Label::createWithSystemFont("Wakuang: 0", "Arial", 24);

     // ����λ�ã�������ʾ����΢���ƣ�
     _healthLabel->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height - 30)); // ���Ƶ���Ļ����
     _staminaLabel->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height - 70)); // ���Ƶ���Ļ����
     _zhongdiLabel->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height - 110)); // ���Ƶ���Ļ����
     _diaoyuLabel->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height - 150)); // ���Ƶ���Ļ����
     _wakuangLabel->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height - 190)); // ���Ƶ���Ļ����

     // ��ӵ���ǰ��
     this->addChild(_healthLabel);
     this->addChild(_staminaLabel);
     this->addChild(_zhongdiLabel);
     this->addChild(_diaoyuLabel);
     this->addChild(_wakuangLabel);

     CCLOG("UI initialized");

}

UI* UI::getInstance() {
    if (!_instance) {
        _instance = new (std::nothrow) UI();
        if (_instance && _instance->init()) {
           
            CCLOG("intial");
        }
        else {
            CC_SAFE_DELETE(_instance);
        }
    }
    return _instance;
}

void UI::updateUI() {
    // ��ȡ Player �ĵ�ǰ״̬
    Player* player = Player::getInstance();
    _healthLabel->setString("Health: " + std::to_string(player->getHealth()));
    _staminaLabel->setString("Stamina: " + std::to_string(player->getStamina()));
    _zhongdiLabel->setString("Zhongdi: " + std::to_string(player->zhongdi));
    _diaoyuLabel->setString("Diaoyu: " + std::to_string(player->diaoyu));
    _wakuangLabel->setString("Wakuang: " + std::to_string(player->wakuang));
}

void UI::showUI() {
    // ��ʾ UI
    static int visible = 1;
    auto _UI = UI::getInstance();
    
    updateUI(); // ������ʾ
    if (!_UI->getParent()) {
        Director::getInstance()->getRunningScene()->addChild(_UI);
        CCLOG("kejian");
    }
    else {
        visible = 1 - visible;
       _UI->setVisible(visible);
        CCLOG("qiehuan");
    }
}