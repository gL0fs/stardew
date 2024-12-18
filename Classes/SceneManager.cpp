#include "SceneManager.h"

using namespace cocos2d;

// ��ȡ����ʵ��
SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

// �����µ�ͼ
void SceneManager::goToScene(Scene* newScene, const std::string& mapID) {
    auto director = Director::getInstance();
    if (!mapHistory.empty() && mapHistory.back() == mapID) {
        CCLOG("Already in the target map: %s", mapID.c_str());
        return;
    }

    // ����������еĳ�����ѹ�뵱ǰ����
    if (director->getRunningScene()) {
        director->pushScene(newScene);
    }
    else {
        director->runWithScene(newScene);
    }

    // ��¼��ͼ ID
    mapHistory.push_back(mapID);
    CCLOG("Entered new map: %s", mapID.c_str());
}

// ������һ��ͼ
void SceneManager::returnToPreviousScene() {
    auto director = Director::getInstance();

    if (mapHistory.size() > 1) {
        director->popScene(); // ������һ����
        mapHistory.pop_back(); // ɾ����ǰ��ͼ��¼
        CCLOG("Returned to previous map: %s", mapHistory.back().c_str());
    }
    else {
        CCLOG("No previous map to return to.");
    }
}

// ����Ƿ����ĳ��ͼ
bool SceneManager::isMapInHistory(const std::string& mapID) const {
    return std::find(mapHistory.begin(), mapHistory.end(), mapID) != mapHistory.end();
}

// ��ȡ��ǰ������Ӧ�ĵ�ͼ ID
std::string SceneManager::getCurrentMapID() const {
    if (!mapHistory.empty()) {
        return mapHistory.back();
    }
    return "Unknown";
}
