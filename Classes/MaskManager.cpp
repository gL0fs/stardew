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
//    //// ����һ����ʼ͸�������ֲ�
//    //_nightMask = LayerColor::create(Color4B(0, 0, 0, 0));  // ��ʼ͸��
//    //_nightMask->setContentSize(Director::getInstance()->getVisibleSize());
//    //_nightMask->setPosition(0, 0);
//
//    //// �����ֲ���ӵ���ǰ������
//    //Scene* currentScene = Director::getInstance()->getRunningScene();
//    //currentScene->addChild(_nightMask, 10);  // ȷ�����ڵ�ͼ��֮��
//
//    //return true;
//    if (!Node::init()) {
//        return false;
//    }
//
//    // ����һ��͸�������ֲ㣨LayerColor��������ģ��ҹ���Ч��
//    _maskLayer = LayerColor::create(Color4B(0, 0, 0, 0));  // ��ʼ͸��
//    _maskLayer->setContentSize(Director::getInstance()->getVisibleSize());
//    _maskLayer->setPosition(0, 0);
//    this->addChild(_maskLayer);
//
//    return true;
//}
//
//void MaskManager::updateNightMask(int currentHour) {
//    // �������ֲ��͸���ȣ�ҹ��ʱ����͸����
//    int alpha = 0;
//
//    // ҹ���18�㿪ʼ���ڶ���6�����
//    if (currentHour >= 18 || currentHour < 6) {
//        alpha = 255;  // ҹ��ʱ��ȫ��ɫ
//    }
//
//    // �������ֲ�͸����
//    _nightMask->setOpacity(alpha);
//}
