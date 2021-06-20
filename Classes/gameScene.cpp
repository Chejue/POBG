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

    auto timeFrame = Sprite::create("res//frame1.png");
    timeFrame->setPosition(150, 670);
    timeFrame->setOpacity(90);
    timeFrame->setScale(0.8);
    addChild(timeFrame, 1);

    auto restEnemyFrame = Sprite::create("res//frame1.png");
    restEnemyFrame->setPosition(1130, 670);
    restEnemyFrame->setOpacity(90);
    restEnemyFrame->setScale(0.8);
    restEnemyFrame->setFlippedX(true);
    addChild(restEnemyFrame, 1);

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
    healthFrame->setPosition(640, 20);
    addChild(healthFrame);

    auto chapterFrame = Sprite::create("res//frame2.png");
    chapterFrame->setPosition(640, 670);
    chapterFrame->setOpacity(90);
    addChild(chapterFrame, 1);

    auto rollCDFrame = Sprite::create("res//frame.png");
    rollCDFrame->setPosition(640, 50);
    rollCDFrame->setScaleX(0.6);
    rollCDFrame->setScaleY(0.3);
    addChild(rollCDFrame, 1);

    auto gunInfoFrame = Sprite::create("res//frame2.png");
    gunInfoFrame->setPosition(640, 90);
    gunInfoFrame->setOpacity(90);
    gunInfoFrame->setScaleX(0.96);
    gunInfoFrame->setScaleY(0.8);
    addChild(gunInfoFrame, 1);

    chapterLabel->setPosition(640, 670);
    chapterLabel->setTextColor(Color4B::WHITE);
    chapterLabel->enableOutline(Color4B::BLACK);
    addChild(chapterLabel, 2);

    timeLabel->setTextColor(Color4B::WHITE);
    timeLabel->setPosition(145, 670);
    addChild(timeLabel, 2);

    numOfRifleBullet->setPosition(65, 60);
    numOfRifleBullet->setTextColor(Color4B::WHITE);
    numOfRifleBullet->enableOutline(Color4B::BLACK);
    numOfRifleBullet->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    addChild(numOfRifleBullet, 2);

    numOfPistolBullet->setPosition(65, 20);
    numOfPistolBullet->setTextColor(Color4B::WHITE);
    numOfPistolBullet->enableOutline(Color4B::BLACK);
    numOfPistolBullet->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    addChild(numOfPistolBullet, 2);

    numOfHealth->setPosition(530, 20);
    numOfHealth->setTextColor(Color4B::WHITE);
    numOfHealth->enableOutline(Color4B::BLACK);
    numOfHealth->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    addChild(numOfHealth, 2);

    rifleBulletBar->setDirection(LoadingBar::Direction::LEFT);
    rifleBulletBar->::gameScene::setPosition(155, 60);
    rifleBulletBar->setScaleX(0.5);
    rifleBulletBar->setScaleY(0.7);
    rifleBulletBar->setPercent(100);
    addChild(rifleBulletBar, 1);

    pistolBulletBar->setDirection(LoadingBar::Direction::LEFT);
    pistolBulletBar->::gameScene::setPosition(155, 20);
    pistolBulletBar->setScaleX(0.5);
    pistolBulletBar->setScaleY(0.7);
    pistolBulletBar->setPercent(100);
    addChild(pistolBulletBar, 1);

    healthBar->setDirection(LoadingBar::Direction::RIGHT);
    healthBar->::gameScene::setPosition(640, 20);
    healthBar->setScaleX(0.6);
    healthBar->setScaleY(0.6);
    healthBar->setPercent(100);
    addChild(healthBar, 1);

    rollTimer->::gameScene::setPosition(640, 50);
    rollTimer->setScaleX(0.6);
    rollTimer->setScaleY(0.3);
    rollTimer->setType(ProgressTimer::Type::BAR);
    rollTimer->setBarChangeRate(Vec2(1, 0));
    rollTimer->setMidpoint(Vec2(0, 0));
    rollTimer->setPercentage(100.0f);

    addChild(rollTimer, 1);


    auto listenerKeyEsc = EventListenerKeyboard::create();
    listenerKeyEsc->onKeyPressed = ([=](EventKeyboard::KeyCode code, Event *event) {
        switch (code) {
            case EventKeyboard::KeyCode::KEY_ESCAPE: {
                gameScene::doPause();
                break;
            }
            case EventKeyboard::KeyCode::KEY_SPACE: {
                    gameScene::rollCD();
                break;
            }
            default:
                break;
        }
    });

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listenerKeyEsc, this);

    this->schedule(CC_SCHEDULE_SELECTOR(gameScene::timeCounter), 1.0f);
    //this->schedule(CC_SCHEDULE_SELECTOR(gameScene::rollCD), 3.0f);
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

    numOfPistolBullet->setString(std::to_string(player->pistolBulletSum[1]));
    numOfRifleBullet->setString(std::to_string(player->rifleBulletSum[1]));
    numOfHealth->setString(std::to_string(player->HP));

    pistolBulletBar->setPercent(player->pistolBulletSum[1] * 100 / player->pistolBulletSum[2]);
    rifleBulletBar->setPercent(player->rifleBulletSum[1] * 100 / player->rifleBulletSum[2]);
    healthBar->setPercent(player->HP);

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

    std::string time = "Time   ";

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

void gameScene::rollCD() {
    if (!player->canRoll) {
        rollTimer->setPercentage(0.0f);
        rollTimer->runAction(ProgressTo::create(3, 100));
    }

}

