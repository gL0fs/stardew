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
    Weather getCurrentWeather() const { return _currentWeather; }
    void generateNewDayWeather();

private:
    static WeatherSystem* _instance;
    Weather _currentWeather;
    Label* _weatherLabel;


    void initWeatherUI();

    void setWeather(Weather weather);

};

#endif

