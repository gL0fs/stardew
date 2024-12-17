// Toolbar.cpp
#include "Toolbar.h"

Toolbar* Toolbar::_instance = nullptr; // 初始化单例实例指针

Toolbar* Toolbar::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = Toolbar::create();
        _instance->retain(); // 保持引用，防止被自动释放
    }
    return _instance;
}

Toolbar::Toolbar()
{
    currentToolIndex = -1; // 初始化当前工具索引为-1
}

Toolbar::~Toolbar()
{
    _instance = nullptr; // 清理单例实例指针
}


bool Toolbar::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // 初始化工具图标
    for (int i = 1; i <= 5; ++i)
    {
        std::string toolName = "tool" + std::to_string(i) + ".png";
        cocos2d::Sprite* tool = cocos2d::Sprite::create(toolName);
        tool->setPosition(i * 50, 0); // 根据需要调整位置
        tool->setVisible(false); // 初始时隐藏所有工具
        this->addChild(tool);
        _tools.pushBack(tool);
    }

    // 设置工具栏位置
    this->ignoreAnchorPointForPosition(false);
    this->setAnchorPoint(cocos2d::Vec2(0.5, 1));
    this->setPosition(cocos2d::Director::getInstance()->getVisibleSize().width / 2, cocos2d::Director::getInstance()->getVisibleSize().height);

    // 添加键盘事件监听
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
    // 隐藏所有工具
    for (auto tool : _tools)
    {
        tool->setVisible(false);
    }

    // 显示选中的工具
    if (toolIndex >= 1 && toolIndex <= 5)
    {
        _tools.at(toolIndex - 1)->setVisible(true);
    }
    currentToolIndex = toolIndex; // 更新当前工具索引
    CCLOG("switchtool%d", toolIndex);
}
int Toolbar::getCurrentToolIndex()
{
    int temp = currentToolIndex;
    return temp; // 返回当前工具的索引
}