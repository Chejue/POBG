//
// Created by 冯天阳 on 2021/5/24.
//

#ifndef POBG_MENUBUTTON_H
#define POBG_MENUBUTTON_H


#include "cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"

using namespace ui;

class menuButton : public Button {
public:
    virtual bool init();
    static Button* create(std::string text);

private:

};



#endif //POBG_MENUBUTTON_H