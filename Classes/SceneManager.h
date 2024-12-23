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


// 场景管理器类，用于管理场景 ID
class SceneManager {
private:
    // 单例模式，构造函数私有化
    SceneManager() = default;

public:
    // 获取单例实例
    static SceneManager& getInstance();
    // 切换地图逻辑
    void SceneManager::switchMap(const std::string& mapName, const std::string& mapName_now, Scene* scene);
    // 进入新地图
    void goToScene(cocos2d::Scene* newScene);

    // 返回上一地图
    void returnToPreviousScene();

    // 禁止拷贝和赋值操作
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
};

#endif // SCENE_MANAGER_H
