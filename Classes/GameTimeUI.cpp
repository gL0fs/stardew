//#include "GameTimeUI.h"
//USING_NS_CC;
//
//GameTimeUI* GameTimeUI::create() {
//    GameTimeUI* timeUI = new (std::nothrow) GameTimeUI();
//    if (timeUI && timeUI->init()) {
//        timeUI->autorelease();
//        return timeUI;
//    }
//    CC_SAFE_DELETE(timeUI);
//    return nullptr;
//}
//
//bool GameTimeUI::init() {
//    if (!Node::init()) {
//        return false;
//    }
//
//    m_currentDay = 1;
//    m_currentHour = 6;
//    m_currentMinute = 0;
//    m_progressWidth = 200.0f; // ���������
//
//    initUI();
//    updateTimeDisplay();
//    this->scheduleUpdate();
//
//    return true;
//}
//
//bool GameTimeUI::initUI() {
//    // ���ر���ͼƬ
//    //m_backgroundSprite = Sprite::create("game_time_bg.png");
//    //if (!m_backgroundSprite) {
//    //    return false;
//    //}
//
//    //// ���ñ���ͼƬ��СΪ 60x45
//    //m_backgroundSprite->setTextureRect(Rect(0, 0, 60, 45));
//    //m_backgroundSprite->setAnchorPoint(Vec2(1, 1));  // ���ϽǶ���
//    //m_backgroundSprite->setPosition(Vec2(0, 0));
//    //this->addChild(m_backgroundSprite);
//
//    // ��ȡ����ͼƬ��ʵ�ʴ�С
//    Size bgSize = m_backgroundSprite->getContentSize();
//
//    // �������ڱ�ǩ
//    m_dateLabel = Label::createWithSystemFont("Mon. 1", "Arial", 12);
//    if (!m_dateLabel) {
//        return false;
//    }
//    m_dateLabel->setAnchorPoint(Vec2(0.5, 0.5));  // ���Ķ���
//    m_dateLabel->setPosition(Vec2(bgSize.width / 2, bgSize.height * 0.7));  // λ���ϲ�
//    m_dateLabel->setTextColor(Color4B(88, 48, 16, 255));
//    m_backgroundSprite->addChild(m_dateLabel);
//
//    // ����ʱ���ǩ
//    m_timeLabel = Label::createWithSystemFont("6:30 am", "Arial", 12);
//    if (!m_timeLabel) {
//        return false;
//    }
//    m_timeLabel->setAnchorPoint(Vec2(0.5, 0.5));  // ���Ķ���
//    m_timeLabel->setPosition(Vec2(bgSize.width / 2, bgSize.height * 0.3));  // λ���²�
//    m_timeLabel->setTextColor(Color4B(88, 48, 16, 255));
//    m_backgroundSprite->addChild(m_timeLabel);
//
//    // ����������
//    m_progressBar = DrawNode::create();
//    if (!m_progressBar) {
//        return false;
//    }
//    m_progressBar->setPosition(Vec2(5, 5));  // λ�ڵײ�
//    m_backgroundSprite->addChild(m_progressBar);
//
//    return true;
//}
//
//
//void GameTimeUI::createProgressBar() {
//    // ����������
//    m_progressBarBg = DrawNode::create();
//    m_progressBarBg->drawSolidRect(
//        Vec2(-m_progressWidth / 2, -5),
//        Vec2(m_progressWidth / 2, 5),
//        Color4F(0.3f, 0.3f, 0.3f, 0.5f)
//    );
//    m_progressBarBg->setPosition(Vec2(80, -30));
//    this->addChild(m_progressBarBg);
//
//    // ���������
//    m_progressBarFill = DrawNode::create();
//    m_progressBarFill->setPosition(Vec2(80, -30));
//    this->addChild(m_progressBarFill);
//}
//
//void GameTimeUI::timeupdate(float dt) {
//    // ����ÿ��Ӧ�����ӵ���Ϸ������
//    const float MINUTES_PER_SECOND = 8.0f;  // ÿ��ʵ������8����Ϸ����
//
//    float minutesToAdd = dt * MINUTES_PER_SECOND;
//    m_currentMinute += static_cast<int>(minutesToAdd);
//
//    if (m_currentMinute >= 60) {
//        m_currentHour += m_currentMinute / 60;
//        m_currentMinute %= 60;
//
//        if (m_currentHour >= 24) {
//            m_currentDay += m_currentHour / 24;
//            m_currentHour %= 24;
//        }
//    }
//
//    updateTimeDisplay();
//}
//
//void GameTimeUI::updateTimeDisplay() {
//    if (!m_dateLabel || !m_timeLabel) {
//        return;
//    }
//
//    // ����������ʾ
//    std::string dayStr = "Mon. " + std::to_string(m_currentDay);
//    m_dateLabel->setString(dayStr);
//
//    // ����ʱ����ʾ
//    std::string ampm = m_currentHour >= 12 ? "pm" : "am";
//    int displayHour = m_currentHour > 12 ? m_currentHour - 12 : m_currentHour;
//    if (displayHour == 0) displayHour = 12;
//
//    char timeStr[32];
//    sprintf(timeStr, "%d:%02d %s", displayHour, m_currentMinute, ampm.c_str());
//    m_timeLabel->setString(timeStr);
//
//    // ���½�����
//    if (m_progressBar) {
//        m_progressBar->clear();
//        float progress = (m_currentHour * 60 + m_currentMinute) / (24.0f * 60.0f);
//        float barWidth = 140.0f;  // �������ܿ��
//        float currentWidth = barWidth * progress;
//
//        // ���ƽ���������
//        m_progressBar->drawSolidRect(
//            Vec2(0, 0),
//            Vec2(barWidth, 10),
//            Color4F(0.3f, 0.3f, 0.3f, 0.5f)
//        );
//
//        // ���ƽ��������
//        m_progressBar->drawSolidRect(
//            Vec2(0, 0),
//            Vec2(currentWidth, 10),
//            Color4F(1.0f, 0.5f, 0.0f, 1.0f)
//        );
//    }
//}
//
//void GameTimeUI::setGameTime(int days, int hours, int minutes) {
//    m_currentDay = days;
//    m_currentHour = hours;
//    m_currentMinute = minutes;
//    updateTimeDisplay();
//}
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
    // ����ӽ������ͱ�ǩ����û�б���ͼƬ
    // �������ڱ�ǩ
    m_dateLabel = Label::createWithSystemFont("Mon. 1", "Arial", 12);
    if (!m_dateLabel) {
        return false;
    }
    m_dateLabel->setAnchorPoint(Vec2(0.5, 0.5));  // ���Ķ���
    m_dateLabel->setPosition(Vec2(100, 50));  // ����λ��
    m_dateLabel->setTextColor(Color4B(88, 48, 16, 255));
    this->addChild(m_dateLabel);

    // ����ʱ���ǩ
    m_timeLabel = Label::createWithSystemFont("6:30 am", "Arial", 12);
    if (!m_timeLabel) {
        return false;
    }
    m_timeLabel->setAnchorPoint(Vec2(0.5, 0.5));  // ���Ķ���
    m_timeLabel->setPosition(Vec2(100, 30));  // ����λ��
    m_timeLabel->setTextColor(Color4B(88, 48, 16, 255));
    this->addChild(m_timeLabel);

    // ����������
    m_progressBar = DrawNode::create();
    if (!m_progressBar) {
        return false;
    }
    m_progressBar->setPosition(Vec2(0, -30));  // ����λ��
    this->addChild(m_progressBar);

    return true;
}

void GameTimeUI::timeupdate(float dt) {
    // ����ÿ��Ӧ�����ӵ���Ϸ������
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
