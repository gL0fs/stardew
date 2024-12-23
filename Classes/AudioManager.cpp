#include "AudioManager.h"

// 静态成员变量的定义和初始化
AudioManager* AudioManager::_instance = nullptr;

AudioManager* AudioManager::getInstance() {
    if (!_instance) {
        _instance = new AudioManager();
    }
    return _instance;
}

AudioManager::AudioManager() : _backgroundMusicId(-1) {}

AudioManager::~AudioManager() {
    stopBackgroundMusic();
}

void AudioManager::playBackgroundMusic(const std::string& filePath, bool loop, float volume) {
    if (_backgroundMusicId != -1) {
        AudioEngine::stop(_backgroundMusicId);
    }
    _backgroundMusicId = AudioEngine::play2d(filePath, loop, volume);
}

void AudioManager::stopBackgroundMusic() {
    if (_backgroundMusicId != -1) {
        AudioEngine::stop(_backgroundMusicId);
        _backgroundMusicId = -1;
    }
}

void AudioManager::playEffect(const std::string& filePath, float volume) {
    AudioEngine::play2d(filePath, false, volume);
}