// Created by 冯天阳

#include "gameScene.h"
#include "settings.h"
#include "AudioEngine.h"
#include "playerData.h"

bool gameScene::init() {
    AudioEngine::stop(settings::getInstance().backgroundAudioOfMenuID);
    if (!settings::getInstance().bgmOfGaming_started) {
        auto backgroundAudioOfGamingID = AudioEngine::play2d("music//bgm_of_gaming.mp3", true);
        AudioEngine::setVolume(backgroundAudioOfGamingID, settings::getInstance().backgroundAudioOfGamingVolume);
        settings::getInstance().backgroundAudioOfGamingID = backgroundAudioOfGamingID;
        settings::getInstance().bgmOfGaming_started = true;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    map = TMXTiledMap::create("map//Desert1.tmx");
    map->setPosition(-325, -300);
    addChild(map);

    player = Player::create();
    Vec2 position = player->sprite->getPosition();
    addChild(player);

    this->scheduleUpdate();

    return Scene::init();
}

bool gameScene::isCanReach(float x, float y) {
    bool result;


    return result;
}

void gameScene::update(float delta) {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto playerPosition = player->getPosition();
    auto mapPosition = map->getPosition();

    Size mapTiledNum = map->getMapSize();
    Size tiledSize = map->getTileSize();
    Size mapSize = Size(mapTiledNum.width * tiledSize.width, mapTiledNum.height * tiledSize.height);

    /*float x = MAX(playerPosition.x, visibleSize.width / 2);

    float y = MAX(playerPosition.x, visibleSize.height / 2);

    x = MIN(x, mapSize.width - visibleSize.width / 2);

    y = MIN(y, mapSize.height - visibleSize.height / 2);

    Vec2 destPos = Vec2(x, y);

    Vec2 centerPos = Vec2(visibleSize.width / 2, visibleSize.height / 2);

    Vec2 viewPos = centerPos - destPos;*/

    Vec2 deltaPos = Vec2(0, 0);
    CCLOG("%f %f", playerPosition.x, playerPosition.y);
    /*if (playerPosition.x >= visibleSize.width * 0.8) {
        deltaPos.x += 3;

    }*/

    map->setPosition(mapPosition + deltaPos);


    //CCLOG("%f %f", x, y);

}




