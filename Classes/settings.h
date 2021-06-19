// Created by 冯天阳

#ifndef POBG_SETTINGS_H
#define POBG_SETTINGS_H

#include "AudioEngine.h"

USING_NS_CC;

class settings {
public:
    ~settings() {
    }

    settings(const settings &) = delete;

    settings &operator=(const settings &) = delete;

    static settings &getInstance() {
        static settings instance;
        return instance;
    }

    bool silenced = false;
    bool bgmOfMenu_started = false;
    bool bgmOfGaming_started = false;
    int backgroundAudioOfMenuID;
    float backgroundAudioOfMenuVolume = 1.0f;
    int backgroundAudioOfGamingID;
    float backgroundAudioOfGamingVolume = 1.0f;
    float effectsVolume = 1.0f;

private:
    settings() {
    }
};


#endif //POBG_SETTINGS_H
