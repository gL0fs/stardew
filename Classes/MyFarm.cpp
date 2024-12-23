// MyFarm.cpp
#include "MyFarm.h"
#include "CropSystem.h"
USING_NS_CC;
Scene* MyFarm::createScene(const std::string& spawnPointName) {
    auto scene = Scene::create();


    // 创建地图层
    auto layer = MyFarm::create(spawnPointName);
    if (layer != nullptr) {
        scene->addChild(layer);

        // 创建UI
        auto timeUI = GameTimeUI::create();
        if (timeUI) {
            auto visibleSize = Director::getInstance()->getVisibleSize();
            // 由于已经设置了背景精灵的锚点为右上角，这里直接设置到右上角位置
            timeUI->setPosition(Vec2(visibleSize.width, visibleSize.height));
            scene->addChild(timeUI, 10);
        }

        // 创建工具栏
        auto toolbarLayer = Toolbar::getInstance();
        if (toolbarLayer) {
            // 确保工具栏只有一个父节点
            if (toolbarLayer->getParent()) {
                toolbarLayer->removeFromParent();
            }

            toolbarLayer->setPositionOnLeft();
            scene->addChild(toolbarLayer, 10);  // 提高Z序确保可见

            // 重要：设置初始工具
            toolbarLayer->switchTool(1);  // 默认选择第一个工具

            // 设置名称以便后续查找
            toolbarLayer->setName("toolbar");
        }

        return scene;
    }
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
  

    // 初始化作物系统
    initCropSystem();
    initAnimalSystem();
    // 设置鼠标监听器
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MyFarm::onMouseDown1, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MyFarm::onKeyPressed1, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}

void MyFarm::onKeyPressed1(EventKeyboard::KeyCode keyCode, Event* event) {
    // 从场景中获取工具栏
    auto scene = Director::getInstance()->getRunningScene();
    auto toolbar = dynamic_cast<Toolbar*>(scene->getChildByName("toolbar"));
    // 处理工具选择（1-5键）
    if (keyCode >= EventKeyboard::KeyCode::KEY_1 &&
        keyCode <= EventKeyboard::KeyCode::KEY_5) {
        int toolIndex = static_cast<int>(keyCode) - static_cast<int>(EventKeyboard::KeyCode::KEY_1) + 1;
        if (toolbar) {
            toolbar->switchTool(toolIndex);
        }
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
        // 获取场景和工具栏
        auto scene = Director::getInstance()->getRunningScene();
        auto toolbar = dynamic_cast<Toolbar*>(scene->getChildByName("toolbar"));

        if (toolbar) {
            Vec2 clickPos = Vec2(event->getCursorX(), event->getCursorY());
            Vec2 locationInNode = this->convertToNodeSpace(clickPos);
            int currentTool = toolbar->getCurrentToolIndex();


            if (_cropSystem) {
                switch (currentTool) {
                case 2: // 种植工具
                    _cropSystem->plantCrop(locationInNode);
                    break;
                case 3: // 收获工具
                {
                    std::string harvestedItem = _cropSystem->harvestCrop(locationInNode);
                    if (!harvestedItem.empty()) {
                        // 添加到玩家背包
                        _playerInstance->getInventory()->addItemToInventory(harvestedItem, 1);
                    }
                }
                break;
                case 4: // 浇水工具
                    _cropSystem->waterCrop(locationInNode);
                    break;
                }
            }
        }
    }
}