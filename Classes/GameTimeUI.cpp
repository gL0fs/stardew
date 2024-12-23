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
//    m_progressWidth = 200.0f; // 进度条宽度
//
//    initUI();
//    updateTimeDisplay();
//    this->scheduleUpdate();
//
//    return true;
//}
//
//bool GameTimeUI::initUI() {
//    // 加载背景图片
//    //m_backgroundSprite = Sprite::create("game_time_bg.png");
//    //if (!m_backgroundSprite) {
//    //    return false;
//    //}
//
//    //// 设置背景图片大小为 60x45
//    //m_backgroundSprite->setTextureRect(Rect(0, 0, 60, 45));
//    //m_backgroundSprite->setAnchorPoint(Vec2(1, 1));  // 右上角对齐
//    //m_backgroundSprite->setPosition(Vec2(0, 0));
//    //this->addChild(m_backgroundSprite);
//
//    // 获取背景图片的实际大小
//    Size bgSize = m_backgroundSprite->getContentSize();
//
//    // 创建日期标签
//    m_dateLabel = Label::createWithSystemFont("Mon. 1", "Arial", 12);
//    if (!m_dateLabel) {
//        return false;
//    }
//    m_dateLabel->setAnchorPoint(Vec2(0.5, 0.5));  // 中心对齐
//    m_dateLabel->setPosition(Vec2(bgSize.width / 2, bgSize.height * 0.7));  // 位于上部
//    m_dateLabel->setTextColor(Color4B(88, 48, 16, 255));
//    m_backgroundSprite->addChild(m_dateLabel);
//
//    // 创建时间标签
//    m_timeLabel = Label::createWithSystemFont("6:30 am", "Arial", 12);
//    if (!m_timeLabel) {
//        return false;
//    }
//    m_timeLabel->setAnchorPoint(Vec2(0.5, 0.5));  // 中心对齐
//    m_timeLabel->setPosition(Vec2(bgSize.width / 2, bgSize.height * 0.3));  // 位于下部
//    m_timeLabel->setTextColor(Color4B(88, 48, 16, 255));
//    m_backgroundSprite->addChild(m_timeLabel);
//
//    // 创建进度条
//    m_progressBar = DrawNode::create();
//    if (!m_progressBar) {
//        return false;
//    }
//    m_progressBar->setPosition(Vec2(5, 5));  // 位于底部
//    m_backgroundSprite->addChild(m_progressBar);
//
//    return true;
//}
//
//
//void GameTimeUI::createProgressBar() {
//    // 进度条背景
//    m_progressBarBg = DrawNode::create();
//    m_progressBarBg->drawSolidRect(
//        Vec2(-m_progressWidth / 2, -5),
//        Vec2(m_progressWidth / 2, 5),
//        Color4F(0.3f, 0.3f, 0.3f, 0.5f)
//    );
//    m_progressBarBg->setPosition(Vec2(80, -30));
//    this->addChild(m_progressBarBg);
//
//    // 进度条填充
//    m_progressBarFill = DrawNode::create();
//    m_progressBarFill->setPosition(Vec2(80, -30));
//    this->addChild(m_progressBarFill);
//}
//
//void GameTimeUI::timeupdate(float dt) {
//    // 计算每秒应该增加的游戏分钟数
//    const float MINUTES_PER_SECOND = 8.0f;  // 每真实秒增加8个游戏分钟
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
//    // 更新日期显示
//    std::string dayStr = "Mon. " + std::to_string(m_currentDay);
//    m_dateLabel->setString(dayStr);
//
//    // 更新时间显示
//    std::string ampm = m_currentHour >= 12 ? "pm" : "am";
//    int displayHour = m_currentHour > 12 ? m_currentHour - 12 : m_currentHour;
//    if (displayHour == 0) displayHour = 12;
//
//    char timeStr[32];
//    sprintf(timeStr, "%d:%02d %s", displayHour, m_currentMinute, ampm.c_str());
//    m_timeLabel->setString(timeStr);
//
//    // 更新进度条
//    if (m_progressBar) {
//        m_progressBar->clear();
//        float progress = (m_currentHour * 60 + m_currentMinute) / (24.0f * 60.0f);
//        float barWidth = 140.0f;  // 进度条总宽度
//        float currentWidth = barWidth * progress;
//
//        // 绘制进度条背景
//        m_progressBar->drawSolidRect(
//            Vec2(0, 0),
//            Vec2(barWidth, 10),
//            Color4F(0.3f, 0.3f, 0.3f, 0.5f)
//        );
//
//        // 绘制进度条填充
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
    m_progressWidth = 200.0f; // 进度条宽度

    initUI();
    updateTimeDisplay();
    this->scheduleUpdate();

    return true;
}

bool GameTimeUI::initUI() {
    // 仅添加进度条和标签，而没有背景图片
    // 创建日期标签
    m_dateLabel = Label::createWithSystemFont("Mon. 1", "Arial", 12);
    if (!m_dateLabel) {
        return false;
    }
    m_dateLabel->setAnchorPoint(Vec2(0.5, 0.5));  // 中心对齐
    m_dateLabel->setPosition(Vec2(100, 50));  // 调整位置
    m_dateLabel->setTextColor(Color4B(88, 48, 16, 255));
    this->addChild(m_dateLabel);

    // 创建时间标签
    m_timeLabel = Label::createWithSystemFont("6:30 am", "Arial", 12);
    if (!m_timeLabel) {
        return false;
    }
    m_timeLabel->setAnchorPoint(Vec2(0.5, 0.5));  // 中心对齐
    m_timeLabel->setPosition(Vec2(100, 30));  // 调整位置
    m_timeLabel->setTextColor(Color4B(88, 48, 16, 255));
    this->addChild(m_timeLabel);

    // 创建进度条
    m_progressBar = DrawNode::create();
    if (!m_progressBar) {
        return false;
    }
    m_progressBar->setPosition(Vec2(0, -30));  // 调整位置
    this->addChild(m_progressBar);

    return true;
}

void GameTimeUI::timeupdate(float dt) {
    // 计算每秒应该增加的游戏分钟数
    const float MINUTES_PER_SECOND = 8.0f;  // 每真实秒增加8个游戏分钟

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

    // 更新日期显示
    std::string dayStr = "Mon. " + std::to_string(m_currentDay);
    m_dateLabel->setString(dayStr);

    // 更新时间显示
    std::string ampm = m_currentHour >= 12 ? "pm" : "am";
    int displayHour = m_currentHour > 12 ? m_currentHour - 12 : m_currentHour;
    if (displayHour == 0) displayHour = 12;

    char timeStr[32];
    sprintf(timeStr, "%d:%02d %s", displayHour, m_currentMinute, ampm.c_str());
    m_timeLabel->setString(timeStr);

    // 更新进度条
    if (m_progressBar) {
        m_progressBar->clear();
        float progress = (m_currentHour * 60 + m_currentMinute) / (24.0f * 60.0f);
        float barWidth = 140.0f;  // 进度条总宽度
        float currentWidth = barWidth * progress;

        // 绘制进度条背景
        m_progressBar->drawSolidRect(
            Vec2(0, 0),
            Vec2(barWidth, 10),
            Color4F(0.3f, 0.3f, 0.3f, 0.5f)
        );

        // 绘制进度条填充
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
