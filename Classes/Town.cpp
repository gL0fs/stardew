#include "Town.h"
#include "Toolbar.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

NPC::NPC() : affection(3) {  // 构造函数，初始化好感度为 3
    // 其他初始化工作可以在这里进行
}

void NPC::setAffection(int value) {
    affection += value;  // 增加或减少好感度
}

int NPC::getAffection() {
    return affection;  // 返回当前好感度
}

std::string NPC::getName() {
    return name;  // 返回 NPC 的名字
}

void NPC::setName(std::string new_name) {
    name = new_name;  // 设置 NPC 的名字
}


Town::Town() :npcs_name({ "Abigail","Emily","Alex" })
{

}

Town::~Town()
{
}
Scene* Town::createScene(const std::string& spawnPointName)
{
    auto scene = Scene::create();

    auto layer = Town::create(spawnPointName);
    if (layer != nullptr)
    {
        TimeManager* timeManager = TimeManager::getInstance();
        // 确保TimeManager只被初始化一次
        static bool timeManagerInitialized = false;
        if (!timeManagerInitialized) {
            timeManager->init();
            timeManagerInitialized = true;
        }

        // 确保TimeManager只有一个父节点
        if (timeManager->getParent()) {
            timeManager->removeFromParent();
        }
        scene->addChild(timeManager);
        scene->addChild(layer);
    }
    auto toolbarLayer = Toolbar::getInstance();
    toolbarLayer->setPositionOnLeft(); // 设置工具栏层位置

    if (toolbarLayer->getParent() == nullptr)
        scene->addChild(toolbarLayer, 1); // 将工具栏层添加到场景中
    else {
        toolbarLayer->getParent()->removeChild(toolbarLayer, false);
        scene->addChild(toolbarLayer);
    }

   
    return scene;
}
Town* Town::create(const std::string& spawnPointName)
{
    Town* town = new (std::nothrow) Town();
    if (town && town->initMap(spawnPointName))
    {
        town->autorelease();
        return town;
    }
    CC_SAFE_DELETE(town);
    return nullptr;
}

bool Town::init()
{
    if (!BaseMapLayer::init())
    {
        return false;
    }

    return true;
}

void Town::loadNPCsFromTMX(cocos2d::TMXTiledMap*  _map) {
    auto npcGroup = _map->getObjectGroup("Objects");

    if (npcGroup) {
        // 获取每个对象的信息（假设 npc 对象在该组中定义）
        for (std::string name : npcs_name) {
            auto& npcData = npcGroup->getObject(name);

            if (!npcData.empty()) {
                // 获取位置和尺寸数据，并根据需要缩放
                float obx = npcData["x"].asFloat() * 2.5;
                float oby = npcData["y"].asFloat() * 2.5;
                float obw = npcData["width"].asFloat() * 2;
                float obh = npcData["height"].asFloat() * 2;

                // 获取地图尺寸
                cocos2d::Size mapSize = _map->getMapSize();

                // 创建 NPC 的矩形
                cocos2d::Rect npcrec(obx, oby, obw, obh);
                CCLOG("NPC position: %f %f", obx, oby);

                // 创建 NPC 对象
                NPC* npc = new NPC();
                npcs.push_back(npc);  // 将 NPC 添加到 npcs 容器中
                npc->npcrec = npcrec;  // 设置 NPC 的矩形范围

                // 设置 NPC 的名字
                npc->setName(npcData["name"].asString());
          }
            else {
                CCLOG("NPC '13' not found in 'Objects' group.");
            }
        }
    }
}





bool Town::initMap(const std::string& spawnPointName)
{
    if (!init())
    {
        return false;
    }


    loadMap("Town/town.tmx");//加入地图层 
    initializePlayer(spawnPointName);//加入玩家层
    loadNPCsFromTMX(_map);

    auto toolbar = Toolbar::getInstance();//工具栏实例
    auto uiLayer = Layer::create();
    this->addChild(uiLayer);

    // 在UI层中添加toolbar
    int toolbarHeight = 16; // 假设工具栏的高度是16像素
    auto winSize = Director::getInstance()->getWinSize();
    auto toolbarLayout = ui::Layout::create();
    toolbarLayout->setSize(Size(winSize.width, toolbarHeight)); // 设置布局大小
    toolbarLayout->setIgnoreAnchorPointForPosition(true);
    toolbarLayout->setPosition(Vec2(0, winSize.height / 2 - toolbarHeight / 2)); // 设置布局位置为屏幕垂直中心
    uiLayer->addChild(toolbarLayout);

    // 创建toolbar并添加到布局

    // 设置toolbar的位置为布局的中心

    toolbar->setPosition(Vec2(toolbarLayout->getContentSize().width / 2, toolbarLayout->getContentSize().height / 2));
    if (toolbar->getParent() == nullptr)
        toolbarLayout->addChild(toolbar);
    CCLOG("add toolbar");
    return true;

}

void Town::showGiftSuccessDialog(NPC* npc, const std::string giftType, int affectionChange) {

    //避免反复触发函数
    _moveDirection = (Vec2::ZERO);
    // 创建弹窗，设置为透明背景
    auto dialog = ui::ImageView::create("window.png");
    dialog->setScale(1.5);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    dialog->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 + 30));  // 弹窗位置
    dialog->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));

    // 显示提示信息
    std::string message1 = "You gave a gift to " + npc->getName() + ". Affection: " + std::to_string(affectionChange);
    auto text1 = ui::Text::create(message1, "fonts/Marker Felt.ttf", 8);
    text1->setPosition(cocos2d::Vec2(visibleSize.width / 8 + 10, visibleSize.height / 8 + 30));

    std::string message2 = "Now:" + std::to_string(npc->getAffection());
    auto text2 = ui::Text::create(message2, "fonts/Marker Felt.ttf", 8);
    text2->setPosition(cocos2d::Vec2(visibleSize.width / 8 + 10, visibleSize.height / 8 + 20));

    // 创建关闭按钮
    auto closeButton = cocos2d::ui::Button::create();
    closeButton->setTitleText("OK");
    closeButton->setTitleFontName("fonts/Marker Felt.ttf");
    closeButton->setPosition(cocos2d::Vec2(visibleSize.width / 8 + 10, visibleSize.height / 8));  // 关闭按钮位置
    closeButton->addClickEventListener([this, dialog, npc](Ref* sender) {
        // 点击关闭按钮时移除弹窗
        CCLOG("Close button clicked, removing dialog...");
        Director::getInstance()->getRunningScene()->removeChild(dialog);
        });
    dialog->addChild(text1);
    dialog->addChild(text2);
    dialog->addChild(closeButton);

    // 将弹窗添加到当前场景
    cocos2d::Director::getInstance()->getRunningScene()->addChild(dialog);
}

void Town::giveGift(NPC* npc, const std::string giftType) {
    // 假设不同礼物对 NPC 的好感度有不同的影响
    int affectionChange = 0;

    if (giftType == "fish1") {
        affectionChange = 1;  // 花朵增加好感度 5
    }
    else if (giftType == "Ring") {
        affectionChange = 1;  // 戒指增加好感度 10
    }
    else if (giftType == "Apple") {
        affectionChange = 1;  // 苹果增加好感度 2
    }
    else {
        CCLOG("Unknown gift type: %s", giftType.c_str());
        return;  // 如果礼物类型不认识，直接返回
    }
    _playerInstance->getInventory()->removeItem(giftType, 1);
    // 更新 NPC 的好感度
    npc->setAffection(affectionChange);
    showGiftSuccessDialog(npc, giftType, affectionChange);
    // 显示提示信息（UI部分）
    CCLOG("You gave a %s to %s. Affection increased by %d.", giftType.c_str(), npc->getName().c_str(), affectionChange);
}


void Town::showGiftDialog(NPC* npc) {

    //避免反复触发函数
    _moveDirection = (Vec2::ZERO);
    // 创建弹窗，设置为透明背景
    auto dialog = ui::ImageView::create("window.png");
    dialog->setScale(1.5);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    dialog->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 + 30));  // 弹窗位置
    dialog->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));

    // 显示提示信息
    std::string question= "Do you want to gift something to " + npc->getName() + "?";
    auto text = ui::Text::create(question, "fonts/Marker Felt.ttf", 8);
    text->setPosition(cocos2d::Vec2(visibleSize.width / 8+10, visibleSize.height / 8+30));
    

    // 创建按钮，打开背包
    auto giftButton = cocos2d::ui::Button::create();
    giftButton->setTitleText("Y");
    giftButton->setTitleFontName("fonts/Marker Felt.ttf");
    giftButton->setPosition(cocos2d::Vec2(visibleSize.width / 8, visibleSize.height / 8));

    auto sendButton = cocos2d::ui::Button::create();
    sendButton->setTitleText("Send");
    sendButton->setTitleFontName("fonts/Marker Felt.ttf");
    sendButton->setPosition(cocos2d::Vec2(visibleSize.width / 2-15, visibleSize.height / 2));
    sendButton->addClickEventListener([this, dialog, npc, sendButton](Ref* sender) {
        giveGift(npc, _playerInstance->getInventory()->getSelectedItem().name);
        });
    sendButton->retain();

    auto closeButton2 = cocos2d::ui::Button::create();
    closeButton2->setTitleText("Close");
    closeButton2->setTitleFontName("fonts/Marker Felt.ttf");
    closeButton2->setPosition(cocos2d::Vec2(visibleSize.width / 2+15, visibleSize.height / 2));
    closeButton2->addClickEventListener([this, dialog, npc, sendButton, closeButton2](Ref* sender) {
        Director::getInstance()->getRunningScene()->removeChild(sendButton);
        Director::getInstance()->getRunningScene()->removeChild(closeButton2);
        _playerInstance->getInventory()->displayInventory();
        });
    closeButton2->retain();

    // 捕获 dialog 和 npc
    giftButton->addClickEventListener([this, dialog, npc, sendButton, closeButton2](Ref* sender) {
        // 使用类中的 _playerInstance 成员打开背包界面
        _playerInstance->getInventory()->displayInventory();  // 打开背包界面
        // 背包打开后关闭弹窗
        Director::getInstance()->getRunningScene()->removeChild(dialog); // 从父节点移除弹窗       
        Director::getInstance()->getRunningScene()->addChild(sendButton);  
        Director::getInstance()->getRunningScene()->addChild(closeButton2);
        });

    // 创建关闭按钮
    auto closeButton = cocos2d::ui::Button::create();
    closeButton->setTitleText("N");
    closeButton->setTitleFontName("fonts/Marker Felt.ttf");
    closeButton->setPosition(cocos2d::Vec2(visibleSize.width / 8+20, visibleSize.height / 8));  // 关闭按钮位置
    closeButton->addClickEventListener([this, dialog, npc](Ref* sender) {
        // 点击关闭按钮时移除弹窗
        CCLOG("Close button clicked, removing dialog...");
        Director::getInstance()->getRunningScene()->removeChild(dialog);
        });

    dialog->addChild(text);
    dialog->addChild(giftButton);
    dialog->addChild(closeButton);

    // 将弹窗添加到当前场景
    cocos2d::Director::getInstance()->getRunningScene()->addChild(dialog);
}


void Town::checkPlayerInteractionWithNPC(NPC* npc, const cocos2d::Vec2& nextPosition) {
    // 获取玩家位置
    Vec2 playerPos = _playerInstance->getPosition();

    if (npc->npcrec.containsPoint(playerPos)) {
        CCLOG("hit_object");
        // 获取目标地图名称
        showGiftDialog(npc);
    }
}

void Town::update(float delta) {
    // 如果存在玩家并且有按键被按下，执行持续移动
    if (_playerInstance && !_moveDirection.equals(Vec2::ZERO)) {
        handlePlayerMovement(_moveDirection);
        for (NPC* npc : npcs) {
            checkPlayerInteractionWithNPC(npc, _moveDirection);
        } // 持续移动
    }
}



