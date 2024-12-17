#include "SceneManager.h"

using namespace cocos2d;

// 获取单例实例
SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

// 进入新地图
void SceneManager::goToScene(Scene* newScene, const std::string& mapID) {
    auto director = Director::getInstance();
    if (!mapHistory.empty() && mapHistory.back() == mapID) {
        CCLOG("Already in the target map: %s", mapID.c_str());
        return;
    }

    // 如果有运行中的场景，压入当前场景
    if (director->getRunningScene()) {
        director->pushScene(newScene);
    }
    else {
        director->runWithScene(newScene);
    }

    // 记录地图 ID
    mapHistory.push_back(mapID);
    CCLOG("Entered new map: %s", mapID.c_str());
}

// 返回上一地图
void SceneManager::returnToPreviousScene() {
    auto director = Director::getInstance();

    if (mapHistory.size() > 1) {
        director->popScene(); // 返回上一场景
        mapHistory.pop_back(); // 删除当前地图记录
        CCLOG("Returned to previous map: %s", mapHistory.back().c_str());
    }
    else {
        CCLOG("No previous map to return to.");
    }
}

// 检查是否存在某地图
bool SceneManager::isMapInHistory(const std::string& mapID) const {
    return std::find(mapHistory.begin(), mapHistory.end(), mapID) != mapHistory.end();
}

// 获取当前场景对应的地图 ID
std::string SceneManager::getCurrentMapID() const {
    if (!mapHistory.empty()) {
        return mapHistory.back();
    }
    return "Unknown";
}
