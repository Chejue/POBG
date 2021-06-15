//
// Created by 冯天阳 on 2021/6/8.
//

#ifndef POBG_MODESCENE_H
#define POBG_MODESCENE_H

#include "cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"

using namespace ui;

class modeScene : public Scene {
public:
    static Scene *createModeScene();

    virtual bool init();

    CREATE_FUNC(modeScene);

private:

};


#endif //POBG_MODESCENE_H
