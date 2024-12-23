#include "SceneManager.h"

using namespace cocos2d;

// ��ȡ����ʵ��
SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

// �����µ�ͼ
void SceneManager::goToScene(Scene* newScene) {
    auto director = Director::getInstance();
    director->replaceScene(newScene);
}

// ������һ��ͼ
void SceneManager::returnToPreviousScene() {
    auto director = Director::getInstance();
    director->popScene(); // ������һ����
    CCLOG("Returned to previous map");
}


void SceneManager::switchMap(const std::string& mapName, const std::string& mapName_now, Scene* _scene)
{
    //���������farm��ͼ���ʹ�����  
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
    // �����farm��ͼ���Ͱѱ����farm��ͼ������
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


