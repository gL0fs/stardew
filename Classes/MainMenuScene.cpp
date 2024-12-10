#include "MainMenuScene.h"
#include "Test.h"

USING_NS_CC;

Scene* MainMenuScene::createScene() {
    return MainMenuScene::create();
}

bool MainMenuScene::init() {
    if (!Scene::init()) return false;

    // 设置背景颜色
    auto background = LayerColor::create(Color4B(50, 150, 255, 255));
    this->addChild(background);

    // 创建标签
    auto label = Label::createWithTTF("Welcome to Stardew Valley!", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Director::getInstance()->getVisibleSize() / 2);
    this->addChild(label);

    // 创建按钮
    auto playButton = MenuItemLabel::create(
        Label::createWithTTF("Play", "fonts/Marker Felt.ttf", 32),
        [](Ref* sender) {
            // 切换到农场场景
            auto scene = Test::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
        }
    );

    auto menu = Menu::create(playButton, nullptr);
    menu->setPosition(Director::getInstance()->getVisibleSize().width / 2, 100);
    this->addChild(menu);

    return true;
}
