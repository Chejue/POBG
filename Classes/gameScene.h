// Created by 冯天阳

#ifndef POBG_GAMESCENE_H
#define POBG_GAMESCENE_H

#include "cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"
#include "playerData.h"
#include "enemyData.h"

using namespace ui;

class gameScene : public Scene {
public:

    virtual bool init();

    CREATE_FUNC(gameScene);

    TMXTiledMap *map;
    Player *player;
    Vector<Enemy *> enemy;

    bool isCanReach(float x, float y);

    void update(float dt);

    void enemyUpdate(float dt);

    void damageOfCollisionUpdate(float dt);

    void damageOfBulletUpdate(float dt);

    void timeCounter(float dt);

    void enemyCounter(float dt);

    void rollCD();

    void doPause();

    void gameEnd(bool isWin);

    void nextChapter();

    int chapter = 0;
    bool chapterStarted = false;
    int second = 0;
    int minute = 0;
    int score = 0;

    Label *timeLabel = Label::createWithTTF("Time   00 : 00", "fonts//arial.ttf", 30);
    Label *numOfHealth = Label::createWithTTF("100", "fonts//arial.ttf", 21);
    Label *numOfEnemy = Label::createWithTTF("  0     Enemy", "fonts//arial.ttf", 30);
    Label *numOfPistolBullet = Label::createWithTTF("0", "fonts//arial.ttf", 21);
    Label *numOfRifleBullet = Label::createWithTTF("0", "fonts//arial.ttf", 21);
    Label *numOfPistolBullet1 = Label::createWithTTF("0", "fonts//arial.ttf", 30);
    Label *numOfRifleBullet1 = Label::createWithTTF("0", "fonts//arial.ttf", 30);
    Label *numOfPistolBullet2 = Label::createWithTTF("0", "fonts//arial.ttf", 25);
    Label *numOfRifleBullet2 = Label::createWithTTF("0", "fonts//arial.ttf", 25);
    Label *chapterLabel = Label::createWithTTF("CHAPTER  1", "fonts//arial.ttf", 30);

    LoadingBar *rifleBulletBar = LoadingBar::create("res//rifleBulletBar.png");
    LoadingBar *pistolBulletBar = LoadingBar::create("res//pistolBulletBar.png");
    LoadingBar *healthBar = LoadingBar::create("res//healthBar.png");

    Sprite *rollCDBar = Sprite::create("res//rollCDBar.png");
    ProgressTimer *rollTimer = ProgressTimer::create(rollCDBar);

    Sprite *rifleBulletPic2 = Sprite::create("res//rifle_Bullet.png");
    Sprite *pistolBulletPic2 = Sprite::create("res//pistol_Bullet.png");

private:

    Vec2 tileCoordForPosition(const Vec2 position);

};


#endif //POBG_GAMESCENE_H
