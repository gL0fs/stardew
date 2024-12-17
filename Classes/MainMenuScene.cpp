

#include "MainMenuScene.h"
#include "Test.h"
#include "Mine.h"
USING_NS_CC;

Scene* MainMenuScene::createScene() {
    return MainMenuScene::create();
}

bool MainMenuScene::init() {
    if (!Scene::init()) return false;

    // 设置背景颜色
    /*auto background = LayerColor::create(Color4B(50, 150, 255, 255));
    this->addChild(background);*/
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // 创建一个Layer
    auto layer = cocos2d::Layer::create();

    // 创建背景Sprite
    auto background = cocos2d::Sprite::create("stardewPanorama.png");

    // 如果需要，可以设置背景Sprite的位置和大小
    background->setPosition(origin + visibleSize / 2);
    background->setScaleX(visibleSize.width / background->getContentSize().width);
    background->setScaleY(visibleSize.height / background->getContentSize().height);

    // 将背景Sprite添加到Layer中
    layer->addChild(background);

    // 将Layer添加到场景中
    this->addChild(layer);
    // 创建标签
   
  
    auto sprite = Sprite::create("yellowLettersLogo.png");

    Vec2 spritePosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + visibleSize.height / 4);

    // 设置精灵位置
    sprite->setPosition(spritePosition);
    this->addChild(sprite);

    // 创建按钮
    auto playButton = MenuItemLabel::create(
        Label::createWithTTF("Play", "fonts/Marker Felt.ttf", 32),
        [](Ref* sender) {
            // 切换到农场场景
            auto scene = Mine::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
        }
    );

    auto menu = Menu::create(playButton, nullptr);
    menu->setPosition(Director::getInstance()->getVisibleSize().width / 2, 100);
    this->addChild(menu);

    return true;
}
