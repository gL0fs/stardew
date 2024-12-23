#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__

#include "cocos2d.h"
#include <vector>

USING_NS_CC;

class TimeManager : public Node {
public:
    static TimeManager* getInstance() {
        if (!_instance) {
            _instance = new TimeManager();
        }
        return _instance;
    }

    static void destroyInstance() {
        if (_instance) {
            _instance->release();
            _instance = nullptr;
        }
    }

    bool init() {
        if (!Node::init()) {
            return false;
        }

        _minutesPerDay = 2.0f;
        _currentGameMinutes = 0;
        _currentGameHour = 6;
        _currentGameDay = 1;
        _currentWeekday = 0;

        initTimeUI();
        this->scheduleUpdate();
        return true;
    }

    void update(float dt) {
        float gameMinutesPerRealSecond = 24.0f * 60.0f / (_minutesPerDay * 60.0f);
        _currentGameMinutes += dt * gameMinutesPerRealSecond;

        while (_currentGameMinutes >= 60) {
            _currentGameMinutes -= 60;
            _currentGameHour++;

            if (_currentGameHour >= 23) {  // 在23点切换到第二天
                _currentGameHour = 6;
                _currentGameMinutes = 0;
                _currentGameDay++;
                _currentWeekday = (_currentWeekday + 1) % 7;

                EventCustom event("new_day");
                _eventDispatcher->dispatchEvent(&event);
            }

            updateTimeUI();
            updateWeekdayUI();
        }
    }

    void updateWeekdayUI() {
        static const std::vector<std::string> weekdays = { "周一", "周二", "周三", "周四", "周五", "周六", "周日" };
        if (_weekdayLabel) {
            _weekdayLabel->setString(weekdays[_currentWeekday] + " " + std::to_string(_currentGameDay));
        }
    }

    void playerGoToBed() {
        _currentGameHour = 6;
        _currentGameMinutes = 0;
        _currentGameDay++;
        _currentWeekday = (_currentWeekday + 1) % 7;

        EventCustom event("new_day");
        _eventDispatcher->dispatchEvent(&event);

        updateWeekdayUI();
        updateTimeUI();
    }

    int getCurrentWeekday() const { return _currentWeekday; }
    int getCurrentDay() const { return _currentGameDay; }
    int getCurrentHour() const { return _currentGameHour; }
    int getCurrentMinutes() const { return static_cast<int>(_currentGameMinutes); }

private:
    static TimeManager* _instance;
    float _minutesPerDay;
    float _currentGameMinutes;
    int _currentGameHour;
    int _currentGameDay;
    int _currentWeekday;
    Label* _timeLabel;
    Label* _weekdayLabel;

    void initTimeUI() {
        _timeLabel = Label::createWithTTF("06:00", "Fonts/pixel_font.ttf", 24);
        _timeLabel->setTextColor(Color4B::BLACK);
        Size visibleSize = Director::getInstance()->getVisibleSize();
        _timeLabel->setPosition(visibleSize.width - 70, visibleSize.height - 0);
        this->addChild(_timeLabel);

        _weekdayLabel = Label::createWithTTF("周一 1", "Fonts/pixel_font.ttf", 24);
        _weekdayLabel->setTextColor(Color4B::BLACK);
        _weekdayLabel->setPosition(visibleSize.width - 70, visibleSize.height - 30);
        this->addChild(_weekdayLabel);

        updateWeekdayUI();
    }

    void updateTimeUI() {
        if (_timeLabel) {
            char timeText[10];
            snprintf(timeText, sizeof(timeText), "%02d:%02d",
                _currentGameHour, static_cast<int>(_currentGameMinutes));
            _timeLabel->setString(timeText);
        }
    }
};

#endif