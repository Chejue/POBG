// Created by 冯天阳

#include "gameScene.h"
#include "settings.h"
#include "AudioEngine.h"
#include "playerData.h"
#include "pauseLayer.h"

bool gameScene::init() {
    AudioEngine::stop(settings::getInstance().backgroundAudioOfMenuID);
    settings::getInstance().bgmOfMenu_started = false;
    if (!settings::getInstance().bgmOfGaming_started) {
        auto backgroundAudioOfGamingID = AudioEngine::play2d("music//bgmOfGaming.mp3", true);
        AudioEngine::setVolume(backgroundAudioOfGamingID, settings::getInstance().backgroundAudioOfGamingVolume);
        settings::getInstance().backgroundAudioOfGamingID = backgroundAudioOfGamingID;
        settings::getInstance().bgmOfGaming_started = true;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    map = TMXTiledMap::create("map//Desert.tmx");
    map->setPosition(-325, -300);
    addChild(map);

    player = Player::create();
    Vec2 position = player->sprite->getPosition();
    addChild(player);


    auto listenerKey = EventListenerKeyboard::create();
    listenerKey->onKeyPressed = ([=](EventKeyboard::KeyCode code, Event *event) {
        switch (code) {
            case EventKeyboard::KeyCode::KEY_ESCAPE: {
                gameScene::doPause();
                break;
            }

            default:
                break;
        }
    });

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);


    this->scheduleUpdate();

    return Scene::init();
}

bool gameScene::isCanReach(float x, float y) {
    bool result;


    return result;
}

void gameScene::update(float delta) {

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto playerPosition = player->sprite->getPosition();
    auto mapPosition = map->getPosition();

    Size mapTiledNum = map->getMapSize();
    Size tiledSize = map->getTileSize();
    Size mapSize = Size(mapTiledNum.width * tiledSize.width, mapTiledNum.height * tiledSize.height);

    float x = MAX(playerPosition.x, visibleSize.width / 2);

    float y = MAX(playerPosition.y, visibleSize.height / 2);

    x = MIN(x, mapSize.width - visibleSize.width / 2);

    y = MIN(y, mapSize.height - visibleSize.height / 2);

    Vec2 destPos = Vec2(x, y);

    Vec2 centerPos = Vec2(visibleSize.width / 2, visibleSize.height / 2);

    Vec2 viewPos = centerPos - destPos;

    //CCLOG("%f %f", playerPosition.x, playerPosition.y);

    map->setPosition(viewPos);

}

void gameScene::doPause() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
    renderTexture->begin();
    Director::getInstance()->getRunningScene()->visit();
    renderTexture->end();
    Director::getInstance()->pushScene(pauseLayer::createScene(renderTexture));
}



