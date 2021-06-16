// Created by 冯天阳

#ifndef POBG_SETTINGSSCENE_H
#define POBG_SETTINGSSCENE_H

#include "cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"

using namespace ui;

class settingsScene : public Scene {
public:

    virtual bool init();

    CREATE_FUNC(settingsScene);

    void backToMenu(Ref *sender);

    void soundOff(Ref *sender, CheckBox::EventType type, Slider *slider1, Slider *slider2, Slider *slider3);

    void sliderChangesMenuVolume(Ref *sender, Slider::EventType type);

    void sliderChangesGamingVolume(Ref *sender, Slider::EventType type);

    void sliderChangesEffectsVolume(Ref *sender, Slider::EventType type);


private:

};


#endif //POBG_SETTINGSSCENE_H
