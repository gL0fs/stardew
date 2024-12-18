#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <string>
#include <vector>
#include "cocos2d.h"

// 场景管理器类，用于管理场景 ID
class SceneManager {
private:
    std::vector<std::string> mapHistory; // 记录场景（地图）的 ID 顺序

    // 单例模式，构造函数私有化
    SceneManager() = default;

public:
    // 获取单例实例
    static SceneManager& getInstance();

    // 进入新地图
    void goToScene(cocos2d::Scene* newScene, const std::string& mapID);

    // 返回上一地图
    void returnToPreviousScene();

    // 检查是否存在某地图
    bool isMapInHistory(const std::string& mapID) const;

    // 获取当前场景对应的地图 ID
    std::string getCurrentMapID() const;

    // 禁止拷贝和赋值操作
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
};

#endif // SCENE_MANAGER_H
