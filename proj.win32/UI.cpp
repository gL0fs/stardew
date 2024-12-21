#include "UI.h"

UI* UI::_instance = nullptr;

UI::UI() {
    // ��ʼ�� UI Ԫ��
    _healthLabel = cocos2d::Label::createWithSystemFont("Health: 100", "Arial", 24);
    _staminaLabel = cocos2d::Label::createWithSystemFont("Stamina: 100", "Arial", 24);
    _zhongdiLabel = cocos2d::Label::createWithSystemFont("Zhongdi: 0", "Arial", 24);
    _diaoyuLabel = cocos2d::Label::createWithSystemFont("Diaoyu: 0", "Arial", 24);
    _wakuangLabel = cocos2d::Label::createWithSystemFont("Wakuang: 0", "Arial", 24);

    // ����λ��
    _healthLabel->setPosition(cocos2d::Vec2(100, 600));
    _staminaLabel->setPosition(cocos2d::Vec2(100, 550));
    _zhongdiLabel->setPosition(cocos2d::Vec2(100, 500));
    _diaoyuLabel->setPosition(cocos2d::Vec2(100, 450));
    _wakuangLabel->setPosition(cocos2d::Vec2(100, 400));

    // ��ӵ���ǰ��
    this->addChild(_healthLabel);
    this->addChild(_staminaLabel);
    this->addChild(_zhongdiLabel);
    this->addChild(_diaoyuLabel);
    this->addChild(_wakuangLabel);
}

UI* UI::getInstance() {
    if (!_instance) {
        _instance = new (std::nothrow) UI();
        if (_instance && _instance->init()) {
            _instance->autorelease();
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
    this->setVisible(true);
    updateUI(); // ������ʾ
}