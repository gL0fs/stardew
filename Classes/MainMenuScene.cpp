//#include "MainMenuScene.h"
////#include "Test.h"
//
//USING_NS_CC;
//
//Scene* MainMenuScene::createScene() {
//    return MainMenuScene::create();
//}
//
//bool MainMenuScene::init() {
//    if (!Scene::init()) return false;
//
//    // ���ñ�����ɫ
//    /*auto background = LayerColor::create(Color4B(50, 150, 255, 255));
//    this->addChild(background);*/
//    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
//    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
//
//    // ����һ��Layer
//    auto layer = cocos2d::Layer::create();
//
//    // ��������Sprite
//    auto background = cocos2d::Sprite::create("Player.png");
//
//    // �����Ҫ���������ñ���Sprite��λ�úʹ�С
//    background->setPosition(origin + visibleSize / 2);
//    background->setScaleX(visibleSize.width / background->getContentSize().width);
//    background->setScaleY(visibleSize.height / background->getContentSize().height);
//
//    // ������Sprite��ӵ�Layer��
//    layer->addChild(background);
//
//    // ��Layer��ӵ�������
//    this->addChild(layer);
//    // ������ǩ
//
//
//    //auto sprite = Sprite::create("yellowLettersLogo.png");
//
//    //Vec2 spritePosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + visibleSize.height / 4);
//
//    //// ���þ���λ��
//    //sprite->setPosition(spritePosition);
//    //this->addChild(sprite);
//
//    //// ������ť
//    //auto playButton = MenuItemLabel::create(
//    //    Label::createWithTTF("Play", "fonts/Marker Felt.ttf", 32),
//    //    [](Ref* sender) {
//    //        // �л���ũ������
//    //        auto scene = Test::createScene();
//    //        Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
//    //    }
//    //);
//
//    //auto menu = Menu::create(playButton, nullptr);
//    //menu->setPosition(Director::getInstance()->getVisibleSize().width / 2, 100);
//    //this->addChild(menu);
//
//    return true;
//}