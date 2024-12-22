// MyFarm.cpp
#include "MyFarm.h"
#include "CropSystem.h"
USING_NS_CC;
Scene* MyFarm::createScene() {
    auto scene = Scene::create();
    auto layer = MyFarm::create();
    if (layer != nullptr) {
        scene->addChild(layer);
    }
    return scene;
}

MyFarm* MyFarm::create() {
    MyFarm* myFarm = new (std::nothrow) MyFarm();
    if (myFarm && myFarm->initMap()) {
        myFarm->autorelease();
        return myFarm;
    }
    CC_SAFE_DELETE(myFarm);
    return nullptr;
}

bool MyFarm::init() {
    if (!BaseMapLayer::init()) {
        return false;
    }
    return true;
}

void MyFarm::initCropSystem() {
    _cropSystem = CropSystem::create();
    if (_cropSystem) {
        // ������ϵͳ��ӵ���ͼ�㼶��
        // ȷ��������ȷ��Z���ϣ������ڵ�ͼ�Ϸ�����ɫ�·�
        this->addChild(_cropSystem, 1);  // Z��Ϊ1�����Ը�����Ҫ����

        // ����������������ʼ������
        // ����������е��������ݵ�
    }
}

bool MyFarm::initMap() {
    if (!init()) {
        return false;
    }


    loadMap("Farm3.tmx");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    _timeUI = GameTimeUI::create();
    _timeUI->setPosition(Vec2(visibleSize.width - 120, visibleSize.height - 50));
    this->addChild(_timeUI, 10);
    _toolbar = Toolbar::getInstance();
    _toolbar->setPositionOnLeft();
    this->addChild(_toolbar, 10);
    initializePlayer();

    // ��ʼ������ϵͳ
    initCropSystem();
    // ������������
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MyFarm::onMouseDown1, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MyFarm::onKeyPressed1, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    CCLOG("��������������");
    CCLOG("�������������");
    return true;
}

void MyFarm::switchMap(const std::string& mapName, int path) {
    // ʵ�ֵ�ͼ�л��߼�
}
void MyFarm::onKeyPressed1(EventKeyboard::KeyCode keyCode, Event* event) {
    // ������ѡ��1-5����
    if (keyCode >= EventKeyboard::KeyCode::KEY_1 &&
        keyCode <= EventKeyboard::KeyCode::KEY_5) {
        int toolIndex = static_cast<int>(keyCode) - static_cast<int>(EventKeyboard::KeyCode::KEY_1) + 1;
        _toolbar->switchTool(toolIndex);
    }

    // ��������ѡ��Q,W,E,R����
    if (_cropSystem) {
        switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_Z:
            _cropSystem->selectCropType(Crop::CropType::CARROT);
            break;
        case EventKeyboard::KeyCode::KEY_X:
            _cropSystem->selectCropType(Crop::CropType::SMALL_TREE);
            break;
        case EventKeyboard::KeyCode::KEY_C:
            _cropSystem->selectCropType(Crop::CropType::RED_FLOWER);
            break;
        case EventKeyboard::KeyCode::KEY_V:
            _cropSystem->selectCropType(Crop::CropType::TREE_FLOWER);
            break;
        }
    }
}

void MyFarm::onMouseDown1(EventMouse* event) {
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
        Vec2 clickPos = Vec2(event->getCursorX(), event->getCursorY());
        Vec2 locationInNode = this->convertToNodeSpace(clickPos);

        int currentTool = _toolbar->getCurrentToolIndex();
      /*  _cropSystem->plantCrop(locationInNode);*/

        if (_cropSystem) {
            if (currentTool == 2) { // ��ͷ
                _cropSystem->plantCrop(locationInNode);
                CCLOG("������ֲ����");
            }
            else if (currentTool == 3) { // ����
                _cropSystem->removeCrop(locationInNode);
                CCLOG("�����Ƴ�����");
            }
        }
    }
}
