//
// Created by 冯天阳 on 2021/6/14.
//

#ifndef POBG_SETTINGSSCENE_H
#define POBG_SETTINGSSCENE_H

#include "cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"

using namespace ui;

class settingsScene : public Scene {
public:
    static Scene *createSettingsScene();
    virtual bool init();

    CREATE_FUNC(settingsScene);

private:

};


#endif //POBG_SETTINGSSCENE_H
