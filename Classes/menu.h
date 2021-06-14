//
// Created by 冯天阳 on 2021/5/14.
//

#ifndef POBG_MENU_H
#define POBG_MENU_H

#include "cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"

using namespace ui;

class menu : public Scene {
public:
    static Scene *createMenuScene();
    virtual bool init();

    void enterModeScene(Ref* sender);
    void enterGameScene(Ref* sender);
    void enterSettingsScene(Ref* sender);
    void menuClose(Ref* sender);

    CREATE_FUNC(menu);

private:

};


#endif //POBG_MENU_H
