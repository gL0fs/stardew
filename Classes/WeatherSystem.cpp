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
    // 添加日志
    CCLOG("WeatherSystem initialized!");

    return true;
}


void WeatherSystem::initWeatherUI() {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // 创建天气标签
    _weatherLabel = Label::createWithTTF("晴天", "Fonts/pixel_font.ttf", 24);
    if (!_weatherLabel) {
        CCLOG("Failed to create weather label!");
        return;
    }

    // 设置天气标签的位置（时间标签的正下方）
    _weatherLabel->setPosition(visibleSize.width - 70, visibleSize.height - 60);  // 调整 Y 坐标
    _weatherLabel->setTextColor(Color4B::BLACK);
    _weatherLabel->enableShadow(Color4B::GRAY, Size(1, -1));  // 添加阴影效果
    _weatherLabel->enableOutline(Color4B::WHITE, 1);          // 添加描边效果
    this->addChild(_weatherLabel);

    // 添加日志
    CCLOG("Weather label initialized at position: (%.2f, %.2f)", _weatherLabel->getPositionX(), _weatherLabel->getPositionY());
}
void WeatherSystem::generateNewDayWeather() {
    int random = rand() % 100;
    setWeather(random < 30 ? Weather::RAINY : Weather::SUNNY); // 30%概率下雨
}

void WeatherSystem::setWeather(Weather weather) {
    _currentWeather = weather;
    _weatherLabel->setString(_currentWeather == Weather::SUNNY ? "晴天" : "雨天");

}