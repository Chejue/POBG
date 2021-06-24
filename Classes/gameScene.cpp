// Created by 冯天阳

#include "gameScene.h"
#include "settings.h"
#include "AudioEngine.h"
#include "playerData.h"
#include "pauseLayer.h"
#include "gameEndLayer.h"
#include "createBullet.h"
#include "ui/CocosGUI.h"
#include "string"
#include <time.h>

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


    auto rifleBulletPic1 = Sprite::create("res//rifle_Bullet.png");
    rifleBulletPic1->setPosition(30, 60);
    rifleBulletPic1->setScale(0.6);
    addChild(rifleBulletPic1);

    rifleBulletPic2->setPosition(565, 90);
    rifleBulletPic2->setScale(0.6);
    addChild(rifleBulletPic2, 2);

    auto pistolBulletPic1 = Sprite::create("res//pistol_Bullet.png");
    pistolBulletPic1->setPosition(30, 20);
    pistolBulletPic1->setScale(0.6);
    addChild(pistolBulletPic1);

    pistolBulletPic2->setPosition(565, 90);
    pistolBulletPic2->setScale(0.6);
    addChild(pistolBulletPic2, 2);

    auto timeFrame = Sprite::create("res//frame1.png");
    timeFrame->setPosition(150, 670);
    timeFrame->setOpacity(90);
    timeFrame->setScale(0.8);
    addChild(timeFrame, 1);

    auto restEnemyFrame = Sprite::create("res//frame3.png");
    restEnemyFrame->setPosition(1130, 670);
    restEnemyFrame->setOpacity(90);
    restEnemyFrame->setScale(0.8);
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

    numOfEnemy->setTextColor(Color4B::WHITE);
    numOfEnemy->setPosition(1135, 670);
    addChild(numOfEnemy, 2);

    numOfRifleBullet->setPosition(65, 60);
    numOfRifleBullet->setTextColor(Color4B::BLACK);
    numOfRifleBullet->enableOutline(Color4B::BLACK);
    numOfRifleBullet->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    addChild(numOfRifleBullet, 2);

    numOfPistolBullet->setPosition(65, 20);
    numOfPistolBullet->setTextColor(Color4B::BLACK);
    numOfPistolBullet->enableOutline(Color4B::BLACK);
    numOfPistolBullet->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    addChild(numOfPistolBullet, 2);

    numOfRifleBullet1->setPosition(630, 70);
    numOfRifleBullet1->setTextColor(Color4B::WHITE);
    numOfRifleBullet1->enableOutline(Color4B::BLACK);
    numOfRifleBullet1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    addChild(numOfRifleBullet1, 2);

    numOfPistolBullet1->setPosition(630, 70);
    numOfPistolBullet1->setTextColor(Color4B::WHITE);
    numOfPistolBullet1->enableOutline(Color4B::BLACK);
    numOfPistolBullet1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    addChild(numOfPistolBullet1, 2);

    numOfRifleBullet2->setPosition(700, 70);
    numOfRifleBullet2->setTextColor(Color4B::WHITE);
    numOfRifleBullet2->enableOutline(Color4B::BLACK);
    numOfRifleBullet2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    addChild(numOfRifleBullet2, 2);

    numOfPistolBullet2->setPosition(700, 70);
    numOfPistolBullet2->setTextColor(Color4B::WHITE);
    numOfPistolBullet2->enableOutline(Color4B::BLACK);
    numOfPistolBullet2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    addChild(numOfPistolBullet2, 2);

    numOfHealth->setPosition(530, 20);
    numOfHealth->setTextColor(Color4B::BLACK);
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

    healthBar->setDirection(LoadingBar::Direction::LEFT);
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
    this->schedule(CC_SCHEDULE_SELECTOR(gameScene::enemyCounter), 0.5f);
    this->schedule(CC_SCHEDULE_SELECTOR(gameScene::damageOfCollisionUpdate), 0.5f);
    this->schedule(CC_SCHEDULE_SELECTOR(gameScene::damageOfBulletUpdate), 0);
    this->scheduleUpdate();

    nextChapter();

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

    if (player->gunType == 1) {
        rifleBulletPic2->setVisible(false);
        numOfRifleBullet1->setVisible(false);
        numOfRifleBullet2->setVisible(false);

        pistolBulletPic2->setVisible(true);
        numOfPistolBullet1->setVisible(true);
        numOfPistolBullet2->setVisible(true);
    } else if (player->gunType == 2) {
        pistolBulletPic2->setVisible(false);
        numOfPistolBullet1->setVisible(false);
        numOfPistolBullet2->setVisible(false);

        rifleBulletPic2->setVisible(true);
        numOfRifleBullet1->setVisible(true);
        numOfRifleBullet2->setVisible(true);
    }


    numOfPistolBullet->setString(std::to_string(player->pistolBulletSum[1]));
    numOfRifleBullet->setString(std::to_string(player->rifleBulletSum[1]));
    numOfHealth->setString(std::to_string(player->HP));
    numOfPistolBullet1->setString(std::to_string(player->pistolBulletSum[0]));
    numOfPistolBullet2->setString(std::to_string(player->pistolBulletSum[1]));
    numOfRifleBullet1->setString(std::to_string(player->rifleBulletSum[0]));
    numOfRifleBullet2->setString(std::to_string(player->rifleBulletSum[1]));

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

    if (chapterStarted && enemy.empty() && chapter <= 3) {
        chapterStarted = false;
    }
    if (!chapterStarted && enemy.empty() && chapter <= 3) {
        if (playerPosition.y >= 550)
            nextChapter();
    }

    if (chapterStarted && enemy.empty() && chapter >= 4) {
        gameEnd(true);
    }

    healthBar->setPercent(player->HP);
    numOfHealth->setString(std::to_string(player->HP));

    if (player->HP <= 0) {
        gameEnd(false);
    }

}

void gameScene::enemyUpdate(float dt) {
    for (auto &e:enemy) {
        e->move(player->sprite->getPosition());
        e->shoot(player->sprite->getPosition());
        float xDir = e->getPositionX() + e->direct[0] / 50;
        float yDir = e->getPositionY() + e->direct[1] / 50;
        if (!isCanReach(xDir, yDir)) {
            e->canMove = false;
        } else
            e->canMove = true;
    }
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

void gameScene::enemyCounter(float dt) {

    std::string enemyNum = "  ";
    enemyNum += std::to_string(enemy.size());
    enemyNum += "     Enemy";
    numOfEnemy->setString(enemyNum);
}

void gameScene::rollCD() {
    if (!player->canRoll) {
        rollTimer->setPercentage(0.0f);
        rollTimer->runAction(ProgressTo::create(3, 100));
    }

}

void gameScene::damageOfCollisionUpdate(float dt) {
    for (auto &e:enemy) {
        if (player->sprite->getBoundingBox().intersectsRect(e->enemy->getBoundingBox())) {
            player->HP -= 10;
        }

        if (player->HP < 0)
            player->HP = 0;

    }
}

void gameScene::gameEnd(bool isWin) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
    renderTexture->begin();
    Director::getInstance()->getRunningScene()->visit();
    renderTexture->end();
    Director::getInstance()->pushScene(gameEndLayer::createScene(renderTexture, isWin));
}

void gameScene::nextChapter() {
    chapterStarted = true;
    srand((unsigned) time(NULL));
    chapter++;
    chapterLabel->setString("CHAPTER  " + std::to_string(chapter));
    auto mapLayer = map->getLayer("地面");

    int enemyNum = 0;
    int minX = 6;
    int maxX = 24;
    int minY;
    int maxY;

    if (chapter == 1) {
        minY = 65;
        maxY = 76;
        enemyNum = 3;
    } else if (chapter == 2) {
        minY = 60;
        maxY = 65;
        enemyNum = 5;
    } else if (chapter == 3) {
        minY = 65;
        maxY = 70;
        enemyNum = 7;
    } else if (chapter == 4) {
        minY = 65;
        maxY = 70;
        enemyNum = 1;
    }


    for (int enemyPos = 0; enemyPos < enemyNum; enemyPos++) {
        int x = (rand() % (maxX - minX + 1)) + minX;
        int y = (rand() % (maxY - minY + 1)) + minY;
        //CCLOG("%d %d", x, y);
        enemy.pushBack(Enemy::create());
        enemy.back()->enemyInit(mapLayer->getPositionAt(Vec2(x, y)), 1);
        addChild(enemy.back());
        schedule(SEL_SCHEDULE(&gameScene::enemyUpdate), 0.2f);
    }

    auto bulletBonus = createBullet::create();
    bulletBonus->bulletInit(Vec2(640, 360), 1);


}

void gameScene::damageOfBulletUpdate(float dt) {
    for (auto &e:enemy) {
        for (auto &p:player->pistolBullet) {
            if (p->bullet->getBoundingBox().intersectsRect(e->enemy->getBoundingBox()) && !p->crashed) {
                p->crashed = true;
                player->HP -= 1;
                e->HP -= 20;
                removeChild(p);
            }
        }
        for (auto &p:player->rifleBullet) {
            if (p->bullet->getBoundingBox().intersectsRect(e->enemy->getBoundingBox()) && !p->crashed) {
                p->crashed = true;
                player->HP -= 2;
                e->HP -= 40;
                removeChild(p);
            }
        }

        if (e->HP <= 0) {
            e->survive = false;
            if (!e->survive) {
                removeChild(e);
                enemy.erase(enemy.find(e));
            }
        }

    }

    /*for (auto &p:e->pistolBullet) {
        if (p->bullet->getBoundingBox().intersectsRect(player->sprite->getBoundingBox())) {
            player->HP -= 10;
        }
    }
    for (auto &p:e->rifleBullet) {
        if (p->bullet->getBoundingBox().intersectsRect(player->sprite->getBoundingBox())) {
            player->HP -= 20;
        }
    }*/


    if (player->HP < 0)
        player->HP = 0;

}



