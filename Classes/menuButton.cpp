//
// Created by 冯天阳 on 2021/5/24.
//

#include "menuButton.h"

USING_NS_CC;

bool menuButton::init() {
    return Button::init();
}

Button *menuButton::create(std::string text) {

    auto menuButton = Button::create("res//Normal_Button.png", "res//Selected_Button.png", "res//Normal_Button.png");
    menuButton->setTitleText(text);
    menuButton->setTitleFontName("arial.ttf");
    menuButton->setTitleFontSize(26);
    menuButton->setTitleColor(Color3B::BLACK);
    menuButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    return menuButton;
}
