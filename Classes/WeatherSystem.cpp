// WeatherSystem.cpp

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
    createRainParticle();
    return true;
}

void WeatherSystem::initWeatherUI() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    _weatherLabel = Label::createWithTTF("晴天", "fonts/pixel_font.ttf", 24);
    _weatherLabel->setPosition(visibleSize.width - 70, visibleSize.height - 60);
    _weatherLabel->setTextColor(Color4B::BLACK);
    this->addChild(_weatherLabel);
}

void WeatherSystem::createRainParticle() {
    _rainParticle = ParticleSystemQuad::create("particles/rain.plist");
    _rainParticle->setPosition(Director::getInstance()->getVisibleSize() / 2);
    _rainParticle->stopSystem();
    this->addChild(_rainParticle);
}

void WeatherSystem::generateNewDayWeather() {
    int random = rand() % 100;
    setWeather(random < 30 ? Weather::RAINY : Weather::SUNNY); // 30%概率下雨
}

void WeatherSystem::setWeather(Weather weather) {
    _currentWeather = weather;
    _weatherLabel->setString(_currentWeather == Weather::SUNNY ? "晴天" : "雨天");

    if (_currentWeather == Weather::RAINY) {
        startRainEffect();
    }
    else {
        stopRainEffect();
    }
}

void WeatherSystem::startRainEffect() {
    if (_rainParticle) _rainParticle->resetSystem();
}

void WeatherSystem::stopRainEffect() {
    if (_rainParticle) _rainParticle->stopSystem();
}