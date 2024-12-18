#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "cocos2d.h"

class Toolbar : public cocos2d::Layer
{
public:
    static Toolbar* getInstance(); // ��ȡ����ʵ���ľ�̬����
    int getCurrentToolIndex(); // ���ص�ǰ���ߵ�����

    CREATE_FUNC(Toolbar);

    int currentToolIndex; // ��ǰ��ʾ�Ĺ��ߵ�����

private:
    Toolbar(); // ˽�й��캯��
    virtual ~Toolbar(); // ˽����������

    static Toolbar* _instance; // ����ʵ���ľ�ָ̬��

    cocos2d::Vector<cocos2d::Sprite*> _tools; // �洢����ͼ�������
   

    bool init(); // ��ʼ������
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); // �����¼��ص�����
    void switchTool(int toolIndex); // �л����ߵķ���
};
#endif