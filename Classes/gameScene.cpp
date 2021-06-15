// Created by 冯天阳

#include "gameScene.h"
#include "mapLayer.h"
#include "settings.h"
#include "AudioEngine.h"
#include "playerData.h"

Scene *gameScene::createGameScene() {
    return gameScene::create();
}

bool gameScene::init() {
    AudioEngine::stop(settings::getInstance().backgroundAudioOfMenuID);
    if (!settings::getInstance().bgmOfGaming_started) {
        auto backgroundAudioOfGamingID = AudioEngine::play2d("music//bgm_of_gaming.mp3", true);
        AudioEngine::setVolume(backgroundAudioOfGamingID, settings::getInstance().backgroundAudioOfGamingVolume);
        settings::getInstance().backgroundAudioOfGamingID = backgroundAudioOfGamingID;
        settings::getInstance().bgmOfGaming_started = true;
    }

    addChild(mapLayer::createMapLayer());

    addChild(Player::create());

    return Scene::init();
}
