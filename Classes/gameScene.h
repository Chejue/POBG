//
// Created by 冯天阳 on 2021/6/14.
//

#ifndef POBG_GAMESCENE_H
#define POBG_GAMESCENE_H

#include "cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"

using namespace ui;

class gameScene : public Scene {
public:
    static Scene *createGameScene();
    virtual bool init();

    CREATE_FUNC(gameScene);

private:

};


#endif //POBG_GAMESCENE_H
