// WeatherSystem.h
#ifndef __WEATHER_SYSTEM_H__
#define __WEATHER_SYSTEM_H__

#include "cocos2d.h"
USING_NS_CC;

class WeatherSystem : public Node {
public:
    static WeatherSystem* getInstance();

    enum class Weather {
        SUNNY,
        RAINY
    };

    bool init() override;
    void setWeather(Weather weather);
    Weather getCurrentWeather() const { return _currentWeather; }
    void generateNewDayWeather();
    void startRainEffect();
    void stopRainEffect();

private:
    static WeatherSystem* _instance;
    Weather _currentWeather;
    Label* _weatherLabel;
    ParticleSystemQuad* _rainParticle;

    void initWeatherUI();
    void createRainParticle();
};
#endif

