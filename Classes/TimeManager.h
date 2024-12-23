
#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__

#include "cocos2d.h"
#include <vector>

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

        _minutesPerDay = 2.0f;  // 1����Ϸʱ�� = 2������ʵʱ��
        _currentGameMinutes = 0;
        _currentGameHour = 6;  // ������6�㿪ʼ
        _currentGameDay = 1;
        _currentWeekday = 0;   // ����һ

        // ��ʼ��ʱ����ʾUI
        initTimeUI();

        // ÿ�����ʱ��
        this->scheduleUpdate();

        return true;
    }

    void update(float dt) override {
        // ÿ2������ʵʱ�䣬��Ϸʱ���ƽ�24Сʱ
        float gameMinutesPerRealSecond = 24.0f * 60.0f / (_minutesPerDay * 60.0f);

        // ������Ϸ������
        _currentGameMinutes += dt * gameMinutesPerRealSecond;

        // ������ӽ�λ
        while (_currentGameMinutes >= 60) {
            _currentGameMinutes -= 60;
            _currentGameHour++;

            // ����Сʱ��λ����Сʱ���ﵽ�򳬹� 23 ʱ����ת���ڶ���� 6:00
            if (_currentGameHour >= 24) {
                _currentGameHour = 6;  // ��ת���ڶ����6��
                _currentGameMinutes = 0;
                _currentGameDay++;
                _currentWeekday = (_currentWeekday + 1) % 7;  // ���ڼ�����

                // �����µ�һ�쿪ʼ���¼�
                EventCustom event("new_day");
                _eventDispatcher->dispatchEvent(&event);
            }
            _darkLayer = LayerColor::create(Color4B(0, 0, 0, 0));
            Size visibleSize = Director::getInstance()->getVisibleSize();
            _darkLayer->setContentSize(visibleSize);
            this->addChild(_darkLayer, 99);  // UI �㼶�����ϲ�

            updateTimeUI();
            updateWeekdayUI();
            adjustScreenBrightness();
        }
    }
        void adjustScreenBrightness() {
            if (_currentGameHour >= 16) {
                float darkeningFactor = (_currentGameHour - 16) / 8.0f;  // 16:00 �� 24:00 �𽥱䰵
                darkeningFactor = std::min(darkeningFactor + (_currentGameMinutes / 60.0f / 8.0f), 1.0f);
                _darkLayer->setOpacity(200 * darkeningFactor);  // ��󰵶ȵ���Ϊ 200
            }
            else if (_currentGameHour >= 0 && _currentGameHour < 6) {
                _darkLayer->setOpacity(200);  // ҹ���ְ�ɫ
            }
            else {
                _darkLayer->setOpacity(0);  // ���챣������
            }
        }

    // �������ڼ�����ʾ
    void updateWeekdayUI() {
        std::vector<std::string> weekdays = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
        _weekdayLabel->setString(weekdays[_currentWeekday] + " " + std::to_string(_currentGameDay));
    }

    // ����ϴ�˯��ʱ�������ڶ���
    void playerGoToBed() {
        _currentGameHour = 6;  // ����Ϊ����6��
        _currentGameMinutes = 0;
        _currentGameDay++;
        _currentWeekday = (_currentWeekday + 1) % 7;

        // �����µ�һ�쿪ʼ���¼�
        EventCustom event("new_day");
        _eventDispatcher->dispatchEvent(&event);

        updateWeekdayUI();  // ����������ʾ
        updateTimeUI();     // ����ʱ����ʾ
        adjustScreenBrightness();
    }

    int getCurrentWeekday() const { return _currentWeekday; }
    int getCurrentDay() const { return _currentGameDay; }
    int getCurrentHour() const { return _currentGameHour; }
    int getCurrentMinutes() const { return static_cast<int>(_currentGameMinutes); }

private:
    static TimeManager* _instance;
    float _minutesPerDay;    // 1�����2������ʵʱ��
    float _currentGameMinutes;
    int _currentGameHour;
    int _currentGameDay;
    int _currentWeekday;     // 0Ϊ����һ��1Ϊ���ڶ�����������

    Label* _timeLabel;   // ������ʾʱ��ı�ǩ
    Label* _weekdayLabel; // ������ʾ���ڼ��ı�ǩ
    LayerColor* _darkLayer;  // �������Ʊ䰵Ч���Ĳ�
    // ��ʼ��ʱ��UI
    void initTimeUI() {
        // ��ʾʱ��ı�ǩ
        _timeLabel = Label::createWithTTF("06:00", "Fonts/pixel_font.ttf", 24);
        _timeLabel->setTextColor(Color4B::BLACK);
        Size visibleSize = Director::getInstance()->getVisibleSize();
        _timeLabel->setPosition(visibleSize.width - 70, visibleSize.height - 0);
        this->addChild(_timeLabel);

        // ��ʾ���ڼ��ı�ǩ
        _weekdayLabel = Label::createWithTTF("Mon 1", "Fonts/pixel_font.ttf", 24);
        _weekdayLabel->setTextColor(Color4B::BLACK);
        _weekdayLabel->setPosition(visibleSize.width - 70, visibleSize.height - 30);
        this->addChild(_weekdayLabel);

        updateWeekdayUI();  // ��ʼ�����ڼ���ʾ

    }

    // ����ʱ����ʾ
    void updateTimeUI() {
        char timeText[10];
        snprintf(timeText, sizeof(timeText), "%02d:%02d",
            _currentGameHour, static_cast<int>(_currentGameMinutes));
        _timeLabel->setString(timeText);
    }

  
};

#endif
