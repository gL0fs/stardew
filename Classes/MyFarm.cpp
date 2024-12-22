// MyFarm.cpp
#include "MyFarm.h"
#include "CropSystem.h"
USING_NS_CC;
Scene* MyFarm::createScene(const std::string& spawnPointName) {
    auto scene = Scene::create();
    auto layer = MyFarm::create(spawnPointName);
    if (layer != nullptr) {
        scene->addChild(layer);
    }
    return scene;
}

MyFarm* MyFarm::create(const std::string& spawnPointName) {
    MyFarm* myFarm = new (std::nothrow) MyFarm();
    if (myFarm && myFarm->initMap(spawnPointName)) {
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
        // 将作物系统添加到地图层级上
        // 确保它在正确的Z序上，比如在地图上方，角色下方
        this->addChild(_cropSystem, 1);  // Z序为1，可以根据需要调整

        // 这里可以添加其他初始化代码
        // 比如加载已有的作物数据等
    }
}

bool MyFarm::initMap(const std::string& spawnPointName) {
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
    initializePlayer(spawnPointName);

    // 初始化作物系统
    initCropSystem();
    // 设置鼠标监听器
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MyFarm::onMouseDown1, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MyFarm::onKeyPressed1, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    CCLOG("输入监听器已添加");
    CCLOG("鼠标监听器已添加");
    return true;
}

void MyFarm::onKeyPressed1(EventKeyboard::KeyCode keyCode, Event* event) {
    // 处理工具选择（1-5键）
    if (keyCode >= EventKeyboard::KeyCode::KEY_1 &&
        keyCode <= EventKeyboard::KeyCode::KEY_5) {
        int toolIndex = static_cast<int>(keyCode) - static_cast<int>(EventKeyboard::KeyCode::KEY_1) + 1;
        _toolbar->switchTool(toolIndex);
    }

    // 处理作物选择（Q,W,E,R键）
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
            if (currentTool == 2) { // 锄头
                _cropSystem->plantCrop(locationInNode);
                CCLOG("尝试种植作物");
            }
            else if (currentTool == 3) { // 镐子
                _cropSystem->removeCrop(locationInNode);
                CCLOG("尝试移除作物");
            }
        }
    }
}
