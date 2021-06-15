//
// Created by 冯天阳 on 2021/6/15.
//

#ifndef POBG_SETTINGS_H
#define POBG_SETTINGS_H


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

    int backgroundAudioID;
    float backgroundAudioVolume;

private:
    settings() {
    }
};


#endif //POBG_SETTINGS_H
