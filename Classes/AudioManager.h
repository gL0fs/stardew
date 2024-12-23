#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

class AudioManager {
public:
    static AudioManager* getInstance();

    void playBackgroundMusic(const std::string& filePath, bool loop = true, float volume = 1.0f);
    void stopBackgroundMusic();
    void playEffect(const std::string& filePath, float volume = 1.0f);

private:
    AudioManager();
    ~AudioManager();

    int _backgroundMusicId; // �������ֵ� ID

    static AudioManager* _instance; // ��̬����ʵ��
};

#endif // AUDIOMANAGER_H