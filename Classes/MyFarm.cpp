// MyFarm.cpp
#include "MyFarm.h"
#include "CropSystem.h"
USING_NS_CC;
Scene* MyFarm::createScene(const std::string& spawnPointName) {
    auto scene = Scene::create();

 
    // ������ͼ��
    auto layer = MyFarm::create(spawnPointName);
    if (layer != nullptr) {
        scene->addChild(layer);

    // ����UI
    auto timeUI = GameTimeUI::create();
    if (timeUI) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        // �����Ѿ������˱��������ê��Ϊ���Ͻǣ�����ֱ�����õ����Ͻ�λ��
        timeUI->setPosition(Vec2(visibleSize.width, visibleSize.height));
        scene->addChild(timeUI, 10);
    }

    // ����������
    auto toolbarLayer = Toolbar::getInstance();
    if (toolbarLayer) {
        // ȷ��������ֻ��һ�����ڵ�
        if (toolbarLayer->getParent()) {
            toolbarLayer->removeFromParent();
        }

        toolbarLayer->setPositionOnLeft();
        scene->addChild(toolbarLayer, 10);  // ���Z��ȷ���ɼ�

        // ��Ҫ�����ó�ʼ����
        toolbarLayer->switchTool(1);  // Ĭ��ѡ���һ������

        // ���������Ա��������
        toolbarLayer->setName("toolbar");
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
        // ������ϵͳ��ӵ���ͼ�㼶��
        // ȷ��������ȷ��Z���ϣ������ڵ�ͼ�Ϸ�����ɫ�·�
        this->addChild(_cropSystem, 1);  // Z��Ϊ1�����Ը�����Ҫ����

        // ����������������ʼ������
        // ����������е��������ݵ�
    }
}

bool MyFarm::initMap(const std::string& spawnPointName) {
    if (!init()) {
        return false;
    }


    loadMap("Farm3.tmx");
  

    // ��ʼ������ϵͳ
    initCropSystem();
    initAnimalSystem();
    // ������������
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MyFarm::onMouseDown1, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MyFarm::onKeyPressed1, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}

void MyFarm::onKeyPressed1(EventKeyboard::KeyCode keyCode, Event* event) {
    // �ӳ����л�ȡ������
    auto scene = Director::getInstance()->getRunningScene();
    auto toolbar = dynamic_cast<Toolbar*>(scene->getChildByName("toolbar"));
    // ������ѡ��1-5����
    if (keyCode >= EventKeyboard::KeyCode::KEY_1 &&
        keyCode <= EventKeyboard::KeyCode::KEY_5) {
        int toolIndex = static_cast<int>(keyCode) - static_cast<int>(EventKeyboard::KeyCode::KEY_1) + 1;
        if (toolbar) {
            toolbar->switchTool(toolIndex);
        }
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
        // ��ȡ�����͹�����
        auto scene = Director::getInstance()->getRunningScene();
        auto toolbar = dynamic_cast<Toolbar*>(scene->getChildByName("toolbar"));

        if (toolbar) {
            Vec2 clickPos = Vec2(event->getCursorX(), event->getCursorY());
            Vec2 locationInNode = this->convertToNodeSpace(clickPos);
            int currentTool = toolbar->getCurrentToolIndex();


            if (_cropSystem) {
                switch (currentTool) {
                case 2: // ��ֲ����
                    _cropSystem->plantCrop(locationInNode);
                    break;
                case 3: // �ջ񹤾�
                {
                    std::string harvestedItem = _cropSystem->harvestCrop(locationInNode);
                    if (!harvestedItem.empty()) {
                        // ��ӵ���ұ���
                        _playerInstance->getInventory()->addItemToInventory(harvestedItem, 1);
                    }
                }
                break;
                case 4: // ��ˮ����
                    _cropSystem->waterCrop(locationInNode);
                    break;
                }
            }
        }
    }
}