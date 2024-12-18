#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "cocos2d.h"

class Toolbar : public cocos2d::Layer
{
public:
    static Toolbar* getInstance(); // 获取单例实例的静态方法
    int getCurrentToolIndex(); // 返回当前工具的索引

    CREATE_FUNC(Toolbar);

    int currentToolIndex; // 当前显示的工具的索引
    void Toolbar::setPositionOnLeft();
private:
    Toolbar(); // 私有构造函数
    virtual ~Toolbar(); // 私有析构函数

    static Toolbar* _instance; // 单例实例的静态指针

    cocos2d::Vector<cocos2d::Sprite*> _tools; // 存储工具图标的向量
   

    bool init(); // 初始化方法
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); // 键盘事件回调函数
    void switchTool(int toolIndex); // 切换工具的方法
};
#endif