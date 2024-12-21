#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__

#include "cocos2d.h"

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

        _minutesPerDay = 3.0f; // 3������ʵʱ�� = 1����Ϸʱ��
        _currentGameMinutes = 0;
        _currentGameHour = 6; // ������6�㿪ʼ
        _currentGameDay = 1;

        this->scheduleUpdate();
        return true;
    }

    void update(float dt) override {
        float gameMinutesPerRealSecond = 24.0f * 60.0f / (_minutesPerDay * 60.0f);
        _currentGameMinutes += dt * gameMinutesPerRealSecond;

        while (_currentGameMinutes >= 60) {
            _currentGameMinutes -= 60;
            _currentGameHour++;

            if (_currentGameHour >= 24) {
                _currentGameHour = 0;
                _currentGameDay++;
                // �����µ�һ�쿪ʼ���¼�
                EventCustom event("new_day");
                _eventDispatcher->dispatchEvent(&event);
            }
        }
    }

    int getCurrentDay() const { return _currentGameDay; }
    int getCurrentHour() const { return _currentGameHour; }
    int getCurrentMinutes() const { return static_cast<int>(_currentGameMinutes); }

private:
    static TimeManager* _instance;
    float _minutesPerDay;
    float _currentGameMinutes;
    int _currentGameHour;
    int _currentGameDay;

    TimeManager() {}
};
#endif
