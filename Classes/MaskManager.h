//#ifndef __MASK_MANAGER_H__
//#define __MASK_MANAGER_H__
//
//#include "cocos2d.h"
//
//USING_NS_CC;
//
//class MaskManager : public Node {
//public:
//    // 获取单例对象
//    static MaskManager* getInstance() {
//        if (!_instance) {
//            _instance = new MaskManager();
//            _instance->init();  // 初始化单例
//        }
//        return _instance;
//    }
//
//    bool init() {
//        if (!Node::init()) {
//            return false;
//        }
//
//        // 创建一个透明的遮罩层（LayerColor），用来模拟夜晚的效果
//        _maskLayer = LayerColor::create(Color4B(0, 0, 0, 0));  // 初始透明
//        _maskLayer->setContentSize(Director::getInstance()->getVisibleSize());
//        _maskLayer->setPosition(0, 0);
//        this->addChild(_maskLayer);
//
//        return true;
//    }
//
//   
//    void updateNightMask(int currentHour) {
//        // 计算遮罩层的透明度，夜晚时增加透明度
//        int alpha = 0;
//
//        // 夜晚从18点开始到第二天6点结束
//        if (currentHour >= 18 || currentHour < 6) {
//            alpha = 255;  // 夜晚时完全黑色
//        }
//
//        // 设置遮罩层透明度
//        _maskLayer->setOpacity(alpha);
//    }
//
//private:
//    static MaskManager* _instance;  // 单例对象
//    LayerColor* _maskLayer;  // 用来显示遮罩层的层
//};
//
//// 静态实例初始化
//MaskManager* MaskManager::_instance = nullptr;
//
//#endif


