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
    Node *player;

    bool isCanReach(float x, float y);

    void update(float delta);

private:

};


#endif //POBG_GAMESCENE_H
