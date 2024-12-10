#include "MainMenuScene.h"
#include "Test.h"

USING_NS_CC;

Scene* MainMenuScene::createScene() {
    return MainMenuScene::create();
}

bool MainMenuScene::init() {
    if (!Scene::init()) return false;

    // ���ñ�����ɫ
    auto background = LayerColor::create(Color4B(50, 150, 255, 255));
    this->addChild(background);

    // ������ǩ
    auto label = Label::createWithTTF("Welcome to Stardew Valley!", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Director::getInstance()->getVisibleSize() / 2);
    this->addChild(label);

    // ������ť
    auto playButton = MenuItemLabel::create(
        Label::createWithTTF("Play", "fonts/Marker Felt.ttf", 32),
        [](Ref* sender) {
            // �л���ũ������
            auto scene = Test::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
        }
    );

    auto menu = Menu::create(playButton, nullptr);
    menu->setPosition(Director::getInstance()->getVisibleSize().width / 2, 100);
    this->addChild(menu);

    return true;
}
