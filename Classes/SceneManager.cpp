#include "SceneManager.h"

using namespace cocos2d;

// 获取单例实例
SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

// 进入新地图
void SceneManager::goToScene(Scene* newScene) {
    auto director = Director::getInstance();
    director->replaceScene(newScene);
}

// 返回上一地图
void SceneManager::returnToPreviousScene() {
    auto director = Director::getInstance();
    director->popScene(); // 返回上一场景
    CCLOG("Returned to previous map");
}


void SceneManager::switchMap(const std::string& mapName, const std::string& mapName_now, Scene* _scene)
{
    //如果现在是farm地图，就存起来  
    if (mapName_now == "farm")
    {
        auto director = Director::getInstance();
        auto scene = MyFarm::createScene(mapName_now);
        director->pushScene(scene);
    }

    if (mapName == "mine")
    {
        _scene->removeAllChildren();
        auto scene = Mine::createScene(mapName_now);
        SceneManager::getInstance().goToScene(scene);
    }
    else if (mapName == "forest")
    {
        _scene->removeAllChildren();
        auto scene = Forest::createScene(mapName_now);
        SceneManager::getInstance().goToScene(scene);
    }
    // 如果是farm地图，就把保存的farm地图弹出来
    else if (mapName == "farm")
    {
        _scene->removeAllChildren();
        SceneManager::getInstance().returnToPreviousScene();
    }
    /*
    else if (mapName == "house")
    {
        _scene->removeAllChildren();
        auto scene = House::createScene(mapName_now);
        SceneManager::getInstance().goToScene(scene);
    }
    */
    else if (mapName == "festival")
    {
        _scene->removeAllChildren();
        auto scene = Festival::createScene(mapName_now);
        SceneManager::getInstance().goToScene(scene);
    }
    /*
    else if (mapName == "town")
    {
        _scene->removeAllChildren();
        auto scene = Town::createScene(mapName_now);
        SceneManager::getInstance().goToScene(scene);
    }
    */
    else if (mapName == "test")
    {
        _scene->removeAllChildren();
        auto scene = Test::createScene(mapName_now);
        SceneManager::getInstance().goToScene(scene);
    }
    else
    {
        CCLOG("Unknown map: %s", mapName.c_str());
    }
}


