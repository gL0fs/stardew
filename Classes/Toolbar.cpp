// Toolbar.cpp
#include "Toolbar.h"

Toolbar* Toolbar::_instance = nullptr; // ��ʼ������ʵ��ָ��

Toolbar* Toolbar::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = Toolbar::create();
        _instance->retain(); // �������ã���ֹ���Զ��ͷ�
    }
    return _instance;
}

Toolbar::Toolbar()
{
    currentToolIndex = -1; // ��ʼ����ǰ��������Ϊ-1
}

Toolbar::~Toolbar()
{
    _instance = nullptr; // ������ʵ��ָ��
}


bool Toolbar::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // ��ʼ������ͼ��
    for (int i = 1; i <= 5; ++i)
    {
        std::string toolName = "tool" + std::to_string(i) + ".png";
        cocos2d::Sprite* tool = cocos2d::Sprite::create(toolName);
        tool->setPosition(i * 50, 0); // ������Ҫ����λ��
        tool->setVisible(false); // ��ʼʱ�������й���
        this->addChild(tool);
        _tools.pushBack(tool);
    }

    // ���ù�����λ��
    this->ignoreAnchorPointForPosition(false);
    this->setAnchorPoint(cocos2d::Vec2(0.5, 1));
    this->setPosition(cocos2d::Director::getInstance()->getVisibleSize().width / 2, cocos2d::Director::getInstance()->getVisibleSize().height);

    // ��Ӽ����¼�����
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Toolbar::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}

void Toolbar::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_1:
            switchTool(1);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_2:
            switchTool(2);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_3:
            switchTool(3);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_4:
            switchTool(4);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_5:
            switchTool(5);
            break;
        default:
            break;
    }
}

void Toolbar::switchTool(int toolIndex)
{
    // �������й���
    for (auto tool : _tools)
    {
        tool->setVisible(false);
    }

    // ��ʾѡ�еĹ���
    if (toolIndex >= 1 && toolIndex <= 5)
    {
        _tools.at(toolIndex - 1)->setVisible(true);
    }
    currentToolIndex = toolIndex; // ���µ�ǰ��������
    CCLOG("switchtool%d", toolIndex);
}
int Toolbar::getCurrentToolIndex()
{
    int temp = currentToolIndex;
    return temp; // ���ص�ǰ���ߵ�����
}