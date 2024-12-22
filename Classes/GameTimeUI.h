#ifndef __GAME_TIME_UI_H__
#define __GAME_TIME_UI_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameTimeUI : public cocos2d::Node {
public:
    static GameTimeUI* create();
    virtual bool init();

    void timeupdate(float dt);
    void setGameTime(int days, int hours, int minutes);

private:
    bool initUI();
    void updateTimeDisplay();
    void createProgressBar();
    cocos2d::DrawNode* m_progressBar;

    cocos2d::Sprite* m_backgroundSprite;
    cocos2d::Label* m_dateLabel;
    cocos2d::Label* m_timeLabel;
    cocos2d::DrawNode* m_progressBarBg;
    cocos2d::DrawNode* m_progressBarFill;

    int m_currentDay;
    int m_currentHour;
    int m_currentMinute;
    float m_progressWidth;

    const float MINUTES_PER_SECOND = 7.0f;
    const cocos2d::Color4F PROGRESS_COLOR = cocos2d::Color4F(1.0f, 0.5f, 0.0f, 1.0f); // ³ÈÉ«
};

#endif
