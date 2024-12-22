#include "GameTimeUI.h"

USING_NS_CC;

GameTimeUI* GameTimeUI::create() {
    GameTimeUI* timeUI = new (std::nothrow) GameTimeUI();
    if (timeUI && timeUI->init()) {
        timeUI->autorelease();
        return timeUI;
    }
    CC_SAFE_DELETE(timeUI);
    return nullptr;
}

bool GameTimeUI::init() {
    if (!Node::init()) {
        return false;
    }

    m_currentDay = 1;
    m_currentHour = 6;
    m_currentMinute = 0;
    m_progressWidth = 200.0f; // ���������

    initUI();
    updateTimeDisplay();
    this->scheduleUpdate();

    return true;
}


bool GameTimeUI::initUI() {
    // ���ر���ͼƬ
    m_backgroundSprite = Sprite::create("game_time_bg.png");
    if (!m_backgroundSprite) {
        return false;
    }

    // ������ê������Ϊ���Ͻ�
    m_backgroundSprite->setAnchorPoint(Vec2(0, 1));
    m_backgroundSprite->setPosition(Vec2(0, 0));
    this->addChild(m_backgroundSprite);

    // �������ڱ�ǩ
    m_dateLabel = Label::createWithSystemFont("Mon. 1", "Arial", 16);
    if (!m_dateLabel) {
        return false;
    }
    m_dateLabel->setAnchorPoint(Vec2(0, 1));  // ����Ϊ���ϽǶ���
    m_dateLabel->setPosition(Vec2(30, -10));   // ����ڱ���ͼƬ��λ��
    m_dateLabel->setTextColor(Color4B(88, 48, 16, 255));
    m_backgroundSprite->addChild(m_dateLabel);

    // ����ʱ���ǩ
    m_timeLabel = Label::createWithSystemFont("6:30 am", "Arial", 16);
    if (!m_timeLabel) {
        return false;
    }
    m_timeLabel->setAnchorPoint(Vec2(0, 1));  // ����Ϊ���ϽǶ���
    m_timeLabel->setPosition(Vec2(30, -35));   // ����ڱ���ͼƬ��λ��
    m_timeLabel->setTextColor(Color4B(88, 48, 16, 255));
    m_backgroundSprite->addChild(m_timeLabel);

    // ����������
    m_progressBar = DrawNode::create();
    if (!m_progressBar) {
        return false;
    }
    m_progressBar->setPosition(Vec2(30, -60)); // ����ڱ���ͼƬ��λ��
    m_backgroundSprite->addChild(m_progressBar);

    return true;
}


void GameTimeUI::createProgressBar() {
    // ����������
    m_progressBarBg = DrawNode::create();
    m_progressBarBg->drawSolidRect(
        Vec2(-m_progressWidth / 2, -5),
        Vec2(m_progressWidth / 2, 5),
        Color4F(0.3f, 0.3f, 0.3f, 0.5f)
    );
    m_progressBarBg->setPosition(Vec2(80, -30));
    this->addChild(m_progressBarBg);

    // ���������
    m_progressBarFill = DrawNode::create();
    m_progressBarFill->setPosition(Vec2(80, -30));
    this->addChild(m_progressBarFill);
}

void GameTimeUI::timeupdate(float dt) {
    // ����ÿ��Ӧ�����ӵ���Ϸ������
    // 3���� = 180����ʵʱ���Ӧ24Сʱ = 1440������Ϸʱ��
    // ����ÿ����Ҫ���ӵ���Ϸ�������ǣ�1440 / 180 = 8����
    const float MINUTES_PER_SECOND = 8.0f;  // ÿ��ʵ������8����Ϸ����

    float minutesToAdd = dt * MINUTES_PER_SECOND;
    m_currentMinute += static_cast<int>(minutesToAdd);

    if (m_currentMinute >= 60) {
        m_currentHour += m_currentMinute / 60;
        m_currentMinute %= 60;

        if (m_currentHour >= 24) {
            m_currentDay += m_currentHour / 24;
            m_currentHour %= 24;
        }
    }

    updateTimeDisplay();
}

void GameTimeUI::updateTimeDisplay() {
    if (!m_dateLabel || !m_timeLabel) {
        return;
    }

    // ����������ʾ
    std::string dayStr = "Mon. " + std::to_string(m_currentDay);
    m_dateLabel->setString(dayStr);

    // ����ʱ����ʾ
    std::string ampm = m_currentHour >= 12 ? "pm" : "am";
    int displayHour = m_currentHour > 12 ? m_currentHour - 12 : m_currentHour;
    if (displayHour == 0) displayHour = 12;

    char timeStr[32];
    sprintf(timeStr, "%d:%02d %s", displayHour, m_currentMinute, ampm.c_str());
    m_timeLabel->setString(timeStr);

    // ���½�����
    if (m_progressBar) {
        m_progressBar->clear();
        float progress = (m_currentHour * 60 + m_currentMinute) / (24.0f * 60.0f);
        float barWidth = 140.0f;  // �������ܿ��
        float currentWidth = barWidth * progress;

        // ���ƽ���������
        m_progressBar->drawSolidRect(
            Vec2(0, 0),
            Vec2(barWidth, 10),
            Color4F(0.3f, 0.3f, 0.3f, 0.5f)
        );

        // ���ƽ��������
        m_progressBar->drawSolidRect(
            Vec2(0, 0),
            Vec2(currentWidth, 10),
            Color4F(1.0f, 0.5f, 0.0f, 1.0f)
        );
    }
}
void GameTimeUI::setGameTime(int days, int hours, int minutes) {
    m_currentDay = days;
    m_currentHour = hours;
    m_currentMinute = minutes;
    updateTimeDisplay();
}