// Created by 冯天阳

#ifndef POBG_MENU_H
#define POBG_MENU_H

#include "cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"

using namespace ui;

class menu : public Scene {
public:
    virtual bool init();

    CREATE_FUNC(menu);

    void enterModeScene(Ref *sender);

    void enterGameScene(Ref *sender);

    void enterSettingsScene(Ref *sender);

    void menuClose(Ref *sender);


private:

};


#endif //POBG_MENU_H
