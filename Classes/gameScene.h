// Created by 冯天阳

#ifndef POBG_GAMESCENE_H
#define POBG_GAMESCENE_H

#include "cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"
#include "playerData.h"

using namespace ui;

class gameScene : public Scene {
public:

    virtual bool init();

    CREATE_FUNC(gameScene);

    TMXTiledMap *map;
    Player *player;

    bool isCanReach(float x, float y);

    void update(float dt);

    void timeCounter(float dt);

    void doPause();

    void rollCD();

    int chapter = 1;
    int second = 0;
    int minute = 0;
    int score = 0;

    Label *timeLabel = Label::createWithTTF("Time   00 : 00", "fonts//arial.ttf", 30);
    Label *numOfHealth = Label::createWithTTF("100", "fonts//arial.ttf", 21);
    Label *numOfPistolBullet = Label::createWithTTF("0", "fonts//arial.ttf", 21);
    Label *numOfRifleBullet = Label::createWithTTF("0", "fonts//arial.ttf", 21);
    Label *chapterLabel = Label::createWithTTF("CHAPTER  1", "fonts//arial.ttf", 30);

    LoadingBar *rifleBulletBar = LoadingBar::create("res//rifleBulletBar.png");
    LoadingBar *pistolBulletBar = LoadingBar::create("res//pistolBulletBar.png");
    LoadingBar *healthBar = LoadingBar::create("res//healthBar.png");

    Sprite *rollCDBar = Sprite::create("res//rollCDBar.png");
    ProgressTimer *rollTimer = ProgressTimer::create(rollCDBar);

private:

    Vec2 tileCoordForPosition(const Vec2 position);

};


#endif //POBG_GAMESCENE_H
