// Created by 冯天阳

#ifndef POBG_MAPLAYER_H
#define POBG_MAPLAYER_H


#include "cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"

using namespace ui;

class mapLayer : public Layer {
public:
    static Layer *createMapLayer();

    virtual bool init();

    CREATE_FUNC(mapLayer);

private:

};


#endif //POBG_MAPLAYER_H
