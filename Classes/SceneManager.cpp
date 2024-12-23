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
    /*
    if (mapName_now == "farm")
    {
        auto director = Director::getInstance();
        auto scene = MyFarm::createScene(mapName_now);
        director->pushScene(scene);
    }
    */
    if (mapName == "mine")
    {
        auto scene = Mine::createScene(mapName_now);
        SceneManager::getInstance().goToScene(scene);
    }
    else if (mapName == "forest")
    {

        auto scene = Forest::createScene(mapName_now);
        SceneManager::getInstance().goToScene(scene);
    }
    // �����farm��ͼ���Ͱѱ����farm��ͼ������
    else if (mapName == "farm")
    {
        auto scene = MyFarm::createScene(mapName_now);
        SceneManager::getInstance().goToScene(scene);
    }
    else if (mapName == "house")
    {

        auto scene = House::createScene(mapName_now);
        SceneManager::getInstance().goToScene(scene);
    }
    else if (mapName == "festival")
    {

        auto scene = Festival::createScene(mapName_now);
        SceneManager::getInstance().goToScene(scene);
    }
    else if (mapName == "town")
    {

        auto scene = Town::createScene(mapName_now);
        SceneManager::getInstance().goToScene(scene);
    }
    else if (mapName == "test")
    {

        auto scene = Test::createScene(mapName_now);
        SceneManager::getInstance().goToScene(scene);
    }
    else
    {
        CCLOG("Unknown map: %s", mapName.c_str());
    }
}


