// Created by 冯天阳

#ifndef POBG_PAUSELAYER_H
#define POBG_PAUSELAYER_H

#include "cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"

using namespace ui;

class pauseLayer : public Layer {
public:

    virtual bool init();

    CREATE_FUNC(pauseLayer);

    static Scene *createScene(RenderTexture *sqr);

    void resumeCallback(Ref *sender);
    void settingsCallback(Ref *sender);
    void quitCallback(Ref *sender);

private:

};

#endif //POBG_PAUSELAYER_H
