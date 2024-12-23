#include "Town.h"
#include "Toolbar.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

NPC::NPC() : affection(3) {  // ���캯������ʼ���øж�Ϊ 3
    // ������ʼ�������������������
}

void NPC::setAffection(int value) {
    affection += value;  // ���ӻ���ٺøж�
}

int NPC::getAffection() {
    return affection;  // ���ص�ǰ�øж�
}

std::string NPC::getName() {
    return name;  // ���� NPC ������
}

void NPC::setName(std::string new_name) {
    name = new_name;  // ���� NPC ������
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
        scene->addChild(layer);
    }
    auto toolbarLayer = Toolbar::getInstance();
    toolbarLayer->setPositionOnLeft(); // ���ù�������λ��

    if (toolbarLayer->getParent() == nullptr)
        scene->addChild(toolbarLayer, 1); // ������������ӵ�������
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
        // ��ȡÿ���������Ϣ������ npc �����ڸ����ж��壩
        for (std::string name : npcs_name) {
            auto& npcData = npcGroup->getObject(name);

            if (!npcData.empty()) {
                // ��ȡλ�úͳߴ����ݣ���������Ҫ����
                float obx = npcData["x"].asFloat() * 2.5;
                float oby = npcData["y"].asFloat() * 2.5;
                float obw = npcData["width"].asFloat() * 2;
                float obh = npcData["height"].asFloat() * 2;

                // ��ȡ��ͼ�ߴ�
                cocos2d::Size mapSize = _map->getMapSize();

                // ���� NPC �ľ���
                cocos2d::Rect npcrec(obx, oby, obw, obh);
                CCLOG("NPC position: %f %f", obx, oby);

                // ���� NPC ����
                NPC* npc = new NPC();
                npcs.push_back(npc);  // �� NPC ��ӵ� npcs ������
                npc->npcrec = npcrec;  // ���� NPC �ľ��η�Χ

                // ���� NPC ������
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


    loadMap("Town/town.tmx");//�����ͼ�� 
    initializePlayer(spawnPointName);//������Ҳ�
    loadNPCsFromTMX(_map);

    auto toolbar = Toolbar::getInstance();//������ʵ��
    auto uiLayer = Layer::create();
    this->addChild(uiLayer);

    // ��UI�������toolbar
    int toolbarHeight = 16; // ���蹤�����ĸ߶���16����
    auto winSize = Director::getInstance()->getWinSize();
    auto toolbarLayout = ui::Layout::create();
    toolbarLayout->setSize(Size(winSize.width, toolbarHeight)); // ���ò��ִ�С
    toolbarLayout->setIgnoreAnchorPointForPosition(true);
    toolbarLayout->setPosition(Vec2(0, winSize.height / 2 - toolbarHeight / 2)); // ���ò���λ��Ϊ��Ļ��ֱ����
    uiLayer->addChild(toolbarLayout);

    // ����toolbar����ӵ�����

    // ����toolbar��λ��Ϊ���ֵ�����

    toolbar->setPosition(Vec2(toolbarLayout->getContentSize().width / 2, toolbarLayout->getContentSize().height / 2));
    if (toolbar->getParent() == nullptr)
        toolbarLayout->addChild(toolbar);
    CCLOG("add toolbar");
    return true;

}

void Town::showGiftSuccessDialog(NPC* npc, const std::string giftType, int affectionChange) {

    //���ⷴ����������
    _moveDirection = (Vec2::ZERO);
    // ��������������Ϊ͸������
    auto dialog = ui::ImageView::create("window.png");
    dialog->setScale(1.5);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    dialog->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 + 30));  // ����λ��
    dialog->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));

    // ��ʾ��ʾ��Ϣ
    std::string message1 = "You gave a gift to " + npc->getName() + ". Affection: " + std::to_string(affectionChange);
    auto text1 = ui::Text::create(message1, "fonts/Marker Felt.ttf", 8);
    text1->setPosition(cocos2d::Vec2(visibleSize.width / 8 + 10, visibleSize.height / 8 + 30));

    std::string message2 = "Now:" + std::to_string(npc->getAffection());
    auto text2 = ui::Text::create(message2, "fonts/Marker Felt.ttf", 8);
    text2->setPosition(cocos2d::Vec2(visibleSize.width / 8 + 10, visibleSize.height / 8 + 20));

    // �����رհ�ť
    auto closeButton = cocos2d::ui::Button::create();
    closeButton->setTitleText("OK");
    closeButton->setTitleFontName("fonts/Marker Felt.ttf");
    closeButton->setPosition(cocos2d::Vec2(visibleSize.width / 8 + 10, visibleSize.height / 8));  // �رհ�ťλ��
    closeButton->addClickEventListener([this, dialog, npc](Ref* sender) {
        // ����رհ�ťʱ�Ƴ�����
        CCLOG("Close button clicked, removing dialog...");
        Director::getInstance()->getRunningScene()->removeChild(dialog);
        });
    dialog->addChild(text1);
    dialog->addChild(text2);
    dialog->addChild(closeButton);

    // ��������ӵ���ǰ����
    cocos2d::Director::getInstance()->getRunningScene()->addChild(dialog);
}

void Town::giveGift(NPC* npc, const std::string giftType) {
    // ���費ͬ����� NPC �ĺøж��в�ͬ��Ӱ��
    int affectionChange = 0;

    if (giftType == "fish1") {
        affectionChange = 1;  // �������Ӻøж� 5
    }
    else if (giftType == "Ring") {
        affectionChange = 1;  // ��ָ���Ӻøж� 10
    }
    else if (giftType == "Apple") {
        affectionChange = 1;  // ƻ�����Ӻøж� 2
    }
    else {
        CCLOG("Unknown gift type: %s", giftType.c_str());
        return;  // ����������Ͳ���ʶ��ֱ�ӷ���
    }
    _playerInstance->getInventory()->removeItem(giftType, 1);
    // ���� NPC �ĺøж�
    npc->setAffection(affectionChange);
    showGiftSuccessDialog(npc, giftType, affectionChange);
    // ��ʾ��ʾ��Ϣ��UI���֣�
    CCLOG("You gave a %s to %s. Affection increased by %d.", giftType.c_str(), npc->getName().c_str(), affectionChange);
}


void Town::showGiftDialog(NPC* npc) {

    //���ⷴ����������
    _moveDirection = (Vec2::ZERO);
    // ��������������Ϊ͸������
    auto dialog = ui::ImageView::create("window.png");
    dialog->setScale(1.5);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    dialog->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 + 30));  // ����λ��
    dialog->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));

    // ��ʾ��ʾ��Ϣ
    std::string question= "Do you want to gift something to " + npc->getName() + "?";
    auto text = ui::Text::create(question, "fonts/Marker Felt.ttf", 8);
    text->setPosition(cocos2d::Vec2(visibleSize.width / 8+10, visibleSize.height / 8+30));
    

    // ������ť���򿪱���
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

    // ���� dialog �� npc
    giftButton->addClickEventListener([this, dialog, npc, sendButton, closeButton2](Ref* sender) {
        // ʹ�����е� _playerInstance ��Ա�򿪱�������
        _playerInstance->getInventory()->displayInventory();  // �򿪱�������
        // �����򿪺�رյ���
        Director::getInstance()->getRunningScene()->removeChild(dialog); // �Ӹ��ڵ��Ƴ�����       
        Director::getInstance()->getRunningScene()->addChild(sendButton);  
        Director::getInstance()->getRunningScene()->addChild(closeButton2);
        });

    // �����رհ�ť
    auto closeButton = cocos2d::ui::Button::create();
    closeButton->setTitleText("N");
    closeButton->setTitleFontName("fonts/Marker Felt.ttf");
    closeButton->setPosition(cocos2d::Vec2(visibleSize.width / 8+20, visibleSize.height / 8));  // �رհ�ťλ��
    closeButton->addClickEventListener([this, dialog, npc](Ref* sender) {
        // ����رհ�ťʱ�Ƴ�����
        CCLOG("Close button clicked, removing dialog...");
        Director::getInstance()->getRunningScene()->removeChild(dialog);
        });

    dialog->addChild(text);
    dialog->addChild(giftButton);
    dialog->addChild(closeButton);

    // ��������ӵ���ǰ����
    cocos2d::Director::getInstance()->getRunningScene()->addChild(dialog);
}


void Town::checkPlayerInteractionWithNPC(NPC* npc, const cocos2d::Vec2& nextPosition) {
    // ��ȡ���λ��
    Vec2 playerPos = _playerInstance->getPosition();

    if (npc->npcrec.containsPoint(playerPos)) {
        CCLOG("hit_object");
        // ��ȡĿ���ͼ����
        showGiftDialog(npc);
    }
}

void Town::update(float delta) {
    // ���������Ҳ����а��������£�ִ�г����ƶ�
    if (_playerInstance && !_moveDirection.equals(Vec2::ZERO)) {
        handlePlayerMovement(_moveDirection);
        for (NPC* npc : npcs) {
            checkPlayerInteractionWithNPC(npc, _moveDirection);
        } // �����ƶ�
    }
}



