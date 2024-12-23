#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <string>
#include <vector>
#include "cocos2d.h"
#include "BaseMapLayer.h"
#include "MyFarm.h"
#include "Mine.h"
#include "House.h"
#include "Forest.h"
#include "Test.h"
#include "Festival.h"


// �����������࣬���ڹ����� ID
class SceneManager {
private:
    // ����ģʽ�����캯��˽�л�
    SceneManager() = default;

public:
    // ��ȡ����ʵ��
    static SceneManager& getInstance();
    // �л���ͼ�߼�
    void SceneManager::switchMap(const std::string& mapName, const std::string& mapName_now, Scene* scene);
    // �����µ�ͼ
    void goToScene(cocos2d::Scene* newScene);

    // ������һ��ͼ
    void returnToPreviousScene();

    // ��ֹ�����͸�ֵ����
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
};

#endif // SCENE_MANAGER_H
