#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <string>
#include <vector>
#include "cocos2d.h"

// �����������࣬���ڹ����� ID
class SceneManager {
private:
    std::vector<std::string> mapHistory; // ��¼��������ͼ���� ID ˳��

    // ����ģʽ�����캯��˽�л�
    SceneManager() = default;

public:
    // ��ȡ����ʵ��
    static SceneManager& getInstance();

    // �����µ�ͼ
    void goToScene(cocos2d::Scene* newScene, const std::string& mapID);

    // ������һ��ͼ
    void returnToPreviousScene();

    // ����Ƿ����ĳ��ͼ
    bool isMapInHistory(const std::string& mapID) const;

    // ��ȡ��ǰ������Ӧ�ĵ�ͼ ID
    std::string getCurrentMapID() const;

    // ��ֹ�����͸�ֵ����
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
};

#endif // SCENE_MANAGER_H
