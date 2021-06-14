//
// Created by 冯天阳 on 2021/6/8.
//

#ifndef POBG_MAPLAYER_H
#define POBG_MAPLAYER_H


#include "cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"

using namespace ui;

class mapLayer : public Layer {
public:
    CREATE_FUNC(mapLayer);

    virtual bool init();

    static Layer* createMapLayer();

private:

};


#endif //POBG_MAPLAYER_H
