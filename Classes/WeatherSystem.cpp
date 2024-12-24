#include "WeatherSystem.h"

WeatherSystem* WeatherSystem::_instance = nullptr;

WeatherSystem* WeatherSystem::getInstance() {
    if (!_instance) {
        _instance = new WeatherSystem();
        _instance->init();
    }
    return _instance;
}

bool WeatherSystem::init() {
    if (!Node::init()) return false;

    _currentWeather = Weather::SUNNY;
    initWeatherUI();
    // �����־
    CCLOG("WeatherSystem initialized!");

    return true;
}


void WeatherSystem::initWeatherUI() {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // ����������ǩ
    _weatherLabel = Label::createWithTTF("����", "Fonts/pixel_font.ttf", 24);
    if (!_weatherLabel) {
        CCLOG("Failed to create weather label!");
        return;
    }

    // ����������ǩ��λ�ã�ʱ���ǩ�����·���
    _weatherLabel->setPosition(visibleSize.width - 70, visibleSize.height - 60);  // ���� Y ����
    _weatherLabel->setTextColor(Color4B::BLACK);
    _weatherLabel->enableShadow(Color4B::GRAY, Size(1, -1));  // �����ӰЧ��
    _weatherLabel->enableOutline(Color4B::WHITE, 1);          // ������Ч��
    this->addChild(_weatherLabel);

    // �����־
    CCLOG("Weather label initialized at position: (%.2f, %.2f)", _weatherLabel->getPositionX(), _weatherLabel->getPositionY());
}
void WeatherSystem::generateNewDayWeather() {
    int random = rand() % 100;
    setWeather(random < 30 ? Weather::RAINY : Weather::SUNNY); // 30%��������
}

void WeatherSystem::setWeather(Weather weather) {
    _currentWeather = weather;
    _weatherLabel->setString(_currentWeather == Weather::SUNNY ? "����" : "����");

}