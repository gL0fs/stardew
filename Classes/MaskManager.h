//#ifndef __MASK_MANAGER_H__
//#define __MASK_MANAGER_H__
//
//#include "cocos2d.h"
//
//USING_NS_CC;
//
//class MaskManager : public Node {
//public:
//    // ��ȡ��������
//    static MaskManager* getInstance() {
//        if (!_instance) {
//            _instance = new MaskManager();
//            _instance->init();  // ��ʼ������
//        }
//        return _instance;
//    }
//
//    bool init() {
//        if (!Node::init()) {
//            return false;
//        }
//
//        // ����һ��͸�������ֲ㣨LayerColor��������ģ��ҹ���Ч��
//        _maskLayer = LayerColor::create(Color4B(0, 0, 0, 0));  // ��ʼ͸��
//        _maskLayer->setContentSize(Director::getInstance()->getVisibleSize());
//        _maskLayer->setPosition(0, 0);
//        this->addChild(_maskLayer);
//
//        return true;
//    }
//
//   
//    void updateNightMask(int currentHour) {
//        // �������ֲ��͸���ȣ�ҹ��ʱ����͸����
//        int alpha = 0;
//
//        // ҹ���18�㿪ʼ���ڶ���6�����
//        if (currentHour >= 18 || currentHour < 6) {
//            alpha = 255;  // ҹ��ʱ��ȫ��ɫ
//        }
//
//        // �������ֲ�͸����
//        _maskLayer->setOpacity(alpha);
//    }
//
//private:
//    static MaskManager* _instance;  // ��������
//    LayerColor* _maskLayer;  // ������ʾ���ֲ�Ĳ�
//};
//
//// ��̬ʵ����ʼ��
//MaskManager* MaskManager::_instance = nullptr;
//
//#endif


