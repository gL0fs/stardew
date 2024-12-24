
#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__

#include "cocos2d.h"
#include <vector>
#include"WeatherSystem.h"

USING_NS_CC;

class TimeManager : public Node
{
public:
    static TimeManager* getInstance() {
        if (!_instance) {
            _instance = new TimeManager();
        }
        return _instance;
    }

    bool init() {
        if (!Node::init()) {
            return false;
        }

        _minutesPerDay = 2.0f;  // 1天游戏时间 = 2分钟现实时间
        _currentGameMinutes = 0;
        _currentGameHour = 6;  // 从早上6点开始
        _currentGameDay = 1;
        _currentWeekday = 0;   // 星期一

        // 初始化时间显示UI
        initTimeUI();
        // 创建暗色图层（只创建一次）
        _darkLayer = LayerColor::create(Color4B(0, 0, 0, 0));
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        _darkLayer->setPosition(origin);
        _darkLayer->setContentSize(visibleSize);
        this->addChild(_darkLayer, 95); // 降低层级

        initTimeUI();
        // 每秒更新时间
        this->scheduleUpdate();

        return true;
    }

    void update(float dt) override {
        // 每2分钟现实时间，游戏时间推进24小时
        float gameMinutesPerRealSecond = 24.0f * 60.0f / (_minutesPerDay * 60.0f);

        // 更新游戏分钟数
        _currentGameMinutes += dt * gameMinutesPerRealSecond;

        // 处理分钟进位
        while (_currentGameMinutes >= 60) {
            _currentGameMinutes -= 60;
            _currentGameHour++;

            // 处理小时进位：当小时数达到或超过 23 时，跳转到第二天的 6:00
            if (_currentGameHour >= 24) {
                _currentGameHour = 6;  // 跳转到第二天的6点
                _currentGameMinutes = 0;
                _currentGameDay++;
                _currentWeekday = (_currentWeekday + 1) % 7;  // 星期几更新

                // 发送新的一天开始的事件
                EventCustom event("new_day");
                _eventDispatcher->dispatchEvent(&event);
                // 通知天气系统生成新的一天的天气
                WeatherSystem::getInstance()->generateNewDayWeather();
            }
 
            updateTimeUI();
            updateWeekdayUI();
            adjustScreenBrightness();
        }
    }
        
    void adjustScreenBrightness() {
        if (_currentGameHour >= 16 && _currentGameHour < 24) {
            float darkeningFactor = (_currentGameHour - 16) / 8.0f;
            darkeningFactor = std::min(darkeningFactor + (_currentGameMinutes / 60.0f / 8.0f), 0.7f); // 最大暗度70%
            _darkLayer->setOpacity(255 * darkeningFactor);
        }
        else if (_currentGameHour >= 0 && _currentGameHour < 6) {
            _darkLayer->setOpacity(255 * 0.7f);
        }
        else {
            _darkLayer->setOpacity(0);
        }
    }

    // 更新星期几的显示
    void updateWeekdayUI() {
        std::vector<std::string> weekdays = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
        _weekdayLabel->setString(weekdays[_currentWeekday] + " " + std::to_string(_currentGameDay));
    }

    // 玩家上床睡觉时，跳到第二天
    void playerGoToBed() {
        _currentGameHour = 6;  // 重置为早上6点
        _currentGameMinutes = 0;
        _currentGameDay++;
        _currentWeekday = (_currentWeekday + 1) % 7;

        // 发送新的一天开始的事件
        EventCustom event("new_day");
        _eventDispatcher->dispatchEvent(&event);

        updateWeekdayUI();  // 更新星期显示
        updateTimeUI();     // 更新时间显示
        adjustScreenBrightness();
    }

    int getCurrentWeekday() const { return _currentWeekday; }
    int getCurrentDay() const { return _currentGameDay; }
    int getCurrentHour() const { return _currentGameHour; }
    int getCurrentMinutes() const { return static_cast<int>(_currentGameMinutes); }

private:
    static TimeManager* _instance;
    float _minutesPerDay;    // 1天等于2分钟真实时间
    float _currentGameMinutes;
    int _currentGameHour;
    int _currentGameDay;
    int _currentWeekday;     // 0为星期一，1为星期二，依此类推

    Label* _timeLabel;   // 用来显示时间的标签
    Label* _weekdayLabel; // 用来显示星期几的标签
    LayerColor* _darkLayer;  // 用来控制变暗效果的层
    // 初始化时间UI
    void initTimeUI() {
       
        // 显示时间的标签
        _timeLabel = Label::createWithTTF("06:00", "Fonts/pixel_font.ttf", 24);
        _timeLabel->setTextColor(Color4B::BLACK);
        _timeLabel->enableShadow(Color4B::GRAY, Size(1, -1));  // 添加阴影效果
        _timeLabel->enableOutline(Color4B::WHITE, 1);          // 添加描边效果
        Size visibleSize = Director::getInstance()->getVisibleSize();
        _timeLabel->setPosition(visibleSize.width - 70, visibleSize.height - 0);
        this->addChild(_timeLabel);

        // 显示星期几的标签
        _weekdayLabel = Label::createWithTTF("Mon 1", "Fonts/pixel_font.ttf", 24);
        _weekdayLabel->setTextColor(Color4B::BLACK);
        _weekdayLabel->enableShadow(Color4B::GRAY, Size(1, -1));  // 添加阴影效果
        _weekdayLabel->enableOutline(Color4B::WHITE, 1);          // 添加描边效果
        _weekdayLabel->setPosition(visibleSize.width - 70, visibleSize.height - 30);
        this->addChild(_weekdayLabel);

        updateWeekdayUI();  // 初始化星期几显示
        updateWeekdayUI();  // 初始化星期几显示

    }

    // 更新时间显示
    void updateTimeUI() {

        // 清除旧的字符串内容
        _timeLabel->setString("");

        // 设置新的时间字符串
        char timeText[10];
        snprintf(timeText, sizeof(timeText), "%02d:%02d",
            _currentGameHour, static_cast<int>(_currentGameMinutes));
        _timeLabel->setString(timeText);
    }

  
};

#endif
