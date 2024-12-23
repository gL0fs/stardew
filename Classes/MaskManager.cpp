//#include "MaskManager.h"
//
//MaskManager* MaskManager::_instance = nullptr;
//MaskManager::MaskManager()
//    : _nightMask(nullptr)
//{}
//
//MaskManager::~MaskManager()
//{}
//
//bool MaskManager::init() {
//    //// 创建一个初始透明的遮罩层
//    //_nightMask = LayerColor::create(Color4B(0, 0, 0, 0));  // 初始透明
//    //_nightMask->setContentSize(Director::getInstance()->getVisibleSize());
//    //_nightMask->setPosition(0, 0);
//
//    //// 将遮罩层添加到当前场景中
//    //Scene* currentScene = Director::getInstance()->getRunningScene();
//    //currentScene->addChild(_nightMask, 10);  // 确保它在地图层之上
//
//    //return true;
//    if (!Node::init()) {
//        return false;
//    }
//
//    // 创建一个透明的遮罩层（LayerColor），用来模拟夜晚的效果
//    _maskLayer = LayerColor::create(Color4B(0, 0, 0, 0));  // 初始透明
//    _maskLayer->setContentSize(Director::getInstance()->getVisibleSize());
//    _maskLayer->setPosition(0, 0);
//    this->addChild(_maskLayer);
//
//    return true;
//}
//
//void MaskManager::updateNightMask(int currentHour) {
//    // 计算遮罩层的透明度，夜晚时增加透明度
//    int alpha = 0;
//
//    // 夜晚从18点开始到第二天6点结束
//    if (currentHour >= 18 || currentHour < 6) {
//        alpha = 255;  // 夜晚时完全黑色
//    }
//
//    // 设置遮罩层透明度
//    _nightMask->setOpacity(alpha);
//}
