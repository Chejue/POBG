// Created by 冯天阳

#include "gameScene.h"
#include "settings.h"
#include "AudioEngine.h"
#include "playerData.h"
#include "pauseLayer.h"
#include "ui/CocosGUI.h"
#include "string"

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
    map->setPosition(-150, -240);
    map->setScale(0.8);
    addChild(map);

    player = Player::create();
    Vec2 position = player->sprite->getPosition();
    addChild(player);

    auto rifleBulletPic = Sprite::create("res//rifle_Bullet.png");
    rifleBulletPic->setPosition(30, 60);
    rifleBulletPic->setScale(0.6);
    addChild(rifleBulletPic);

    auto pistolBulletPic = Sprite::create("res//pistol_Bullet.png");
    pistolBulletPic->setPosition(30, 20);
    pistolBulletPic->setScale(0.6);
    addChild(pistolBulletPic);

    auto rifleBulletFrame = Sprite::create("res//frame.png");
    rifleBulletFrame->setScaleX(0.5);
    rifleBulletFrame->setScaleY(0.7);
    rifleBulletFrame->setPosition(155, 60);
    addChild(rifleBulletFrame);

    auto pistolBulletFrame = Sprite::create("res//frame.png");
    pistolBulletFrame->setScaleX(0.5);
    pistolBulletFrame->setScaleY(0.7);
    pistolBulletFrame->setPosition(155, 20);
    addChild(pistolBulletFrame);

    auto healthFrame = Sprite::create("res//frame.png");
    healthFrame->setScaleX(0.6);
    healthFrame->setScaleY(0.6);
    healthFrame->setPosition(640, 40);
    addChild(healthFrame);

    auto numOfRifleBullet = Label::createWithTTF("0", "fonts//arial.ttf", 18);
    numOfRifleBullet->setPosition(70, 60);
    numOfRifleBullet->setTextColor(Color4B::WHITE);
    numOfRifleBullet->enableOutline(Color4B::BLACK);
    addChild(numOfRifleBullet, 2);

    auto numOfPistolBullet = Label::createWithTTF("0", "fonts//arial.ttf", 18);
    numOfPistolBullet->setPosition(70, 20);
    numOfPistolBullet->setTextColor(Color4B::WHITE);
    numOfPistolBullet->enableOutline(Color4B::BLACK);
    addChild(numOfPistolBullet, 2);

    auto numOfHealth = Label::createWithTTF("100", "fonts//arial.ttf", 18);
    numOfHealth->setPosition(540, 40);
    numOfHealth->setTextColor(Color4B::WHITE);
    numOfHealth->enableOutline(Color4B::BLACK);
    addChild(numOfHealth, 2);


    auto rifleBulletBar = LoadingBar::create("res//rifleBulletBar.png");
    rifleBulletBar->setDirection(LoadingBar::Direction::LEFT);
    rifleBulletBar->::gameScene::setPosition(155, 60);
    rifleBulletBar->setScaleX(0.5);
    rifleBulletBar->setScaleY(0.7);
    rifleBulletBar->setPercent(100);
    addChild(rifleBulletBar, 1);

    auto pistolBulletBar = LoadingBar::create("res//pistolBulletBar.png");
    pistolBulletBar->setDirection(LoadingBar::Direction::LEFT);
    pistolBulletBar->::gameScene::setPosition(155, 20);
    pistolBulletBar->setScaleX(0.5);
    pistolBulletBar->setScaleY(0.7);
    pistolBulletBar->setPercent(100);
    addChild(pistolBulletBar, 1);

    auto healthBar = LoadingBar::create("res//healthBar.png");
    healthBar->setDirection(LoadingBar::Direction::RIGHT);
    healthBar->::gameScene::setPosition(640, 40);
    healthBar->setScaleX(0.6);
    healthBar->setScaleY(0.6);
    healthBar->setPercent(100);
    addChild(healthBar, 1);

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

    this->schedule(CC_SCHEDULE_SELECTOR(gameScene::timeCounter), 1.0f);
    this->scheduleUpdate();

    return Scene::init();
}

bool gameScene::isCanReach(float x, float y) {
    bool result;

    auto boundariesLayer = map->getLayer("边界");
    auto obstaclesLayer = map->getLayer("装饰");

    Vec2 mapPos = tileCoordForPosition(Vec2(x, y));

    if (boundariesLayer->getTileGIDAt(mapPos) || obstaclesLayer->getTileGIDAt(mapPos)) {
        result = false;
    } else {
        result = true;
    }

    return result;
}

void gameScene::update(float dt) {

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto playerPosition = player->sprite->getPosition();
    auto mapPosition = map->getPosition();

    Size mapTiledNum = map->getMapSize();
    Size tiledSize = map->getTileSize();
    Size mapSize = Size(mapTiledNum.width * tiledSize.width, mapTiledNum.height * tiledSize.height);

    player->canMove = true;
    if (player->keyMap[EventKeyboard::KeyCode::KEY_A]) {
        if (!isCanReach(player->sprite->getPositionX() - 35, player->sprite->getPositionY())) {
            player->canMove = false;
        }
    } else if (player->keyMap[EventKeyboard::KeyCode::KEY_W]) {
        if (!isCanReach(player->sprite->getPositionX(), player->sprite->getPositionY() + 35)) {
            player->canMove = false;
        }
    } else if (player->keyMap[EventKeyboard::KeyCode::KEY_S]) {
        if (!isCanReach(player->sprite->getPositionX(), player->sprite->getPositionY() - 35)) {
            player->canMove = false;
        }
    } else if (player->keyMap[EventKeyboard::KeyCode::KEY_D]) {
        if (!isCanReach(player->sprite->getPositionX() + 35, player->sprite->getPositionY())) {
            player->canMove = false;
        }
    }


    Vec2 deltaPos = Vec2(0, 0);

    if (playerPosition.x > 0.85 * visibleSize.width) {
        deltaPos.x = -3;
        player->sprite->setPosition(0.85 * visibleSize.width, playerPosition.y);
    }
    if (playerPosition.y > 0.8 * visibleSize.height) {
        deltaPos.y = -3;
        player->sprite->setPosition(playerPosition.x, 0.8 * visibleSize.height);
    }
    if (playerPosition.x < 0.15 * visibleSize.width) {
        deltaPos.x = 3;
        player->sprite->setPosition(0.15 * visibleSize.width, playerPosition.y);
    }
    if (playerPosition.y < 0.2 * visibleSize.height) {
        deltaPos.y = 3;
        player->sprite->setPosition(playerPosition.x, 0.2 * visibleSize.height);
    }

    map->setPosition(map->getPosition() + deltaPos);

    /*auto floorLayer = map->getLayer("地面");
    auto boundariesLayer = map->getLayer("边界");
    auto obstaclesLayer = map->getLayer("装饰");

    auto mapPos = tileCoordForPosition(playerPosition);


    floorLayer->setTileGID(0, mapPos);*/


}

void gameScene::doPause() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
    renderTexture->begin();
    Director::getInstance()->getRunningScene()->visit();
    renderTexture->end();
    Director::getInstance()->pushScene(pauseLayer::createScene(renderTexture));
}

// OpenGL坐标转成格子坐标
Vec2 gameScene::tileCoordForPosition(const Vec2 position) {
    Size mapSize = map->getMapSize();
    Size tileSize = map->getTileSize();
    int x = (position.x - map->getPositionX()) / tileSize.width;
    int y = (mapSize.height * tileSize.height - position.y + map->getPositionY()) / tileSize.height;

    return Vec2(x, y);
}

void gameScene::timeCounter(float dt) {

    static auto timeLabel = Label::createWithTTF("Time: 00 : 00", "fonts//arial.ttf", 30);
    timeLabel->setTextColor(Color4B::WHITE);
    timeLabel->setPosition(100, 700);

    static bool add = false;
    if (!add) {
        addChild(timeLabel);
        add = true;
    }

    static int second = 0;
    static int minute = 0;
    std::string time = "Time: ";

    second++;
    if (second == 60) {
        second = 0;
        minute++;
    }

    if (minute >= 10) {
        time += std::to_string(minute);
    } else {
        time += "0" + std::to_string(minute);
    }

    time += " : ";

    if (second >= 10) {
        time += std::to_string(second);
    } else {
        time += "0" + std::to_string(second);
    }

    timeLabel->setString(time);

}