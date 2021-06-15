//
// Created by 冯天阳 on 2021/6/14.
//

#include "settingsScene.h"
#include "menu.h"
#include "ui/CocosGUI.h"
#include "settings.h"
#include "AudioEngine.h"

USING_NS_CC;
using namespace ui;

Scene *settingsScene::createSettingsScene() {
    return settingsScene::create();
}

bool settingsScene::init() {

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto backToMenuButton = Button::create("res//Normal_Button.png");
    backToMenuButton->addClickEventListener(CC_CALLBACK_1(settingsScene::backToMenu, this));
    backToMenuButton->::settingsScene::setPosition(100, 600);

    auto soundOffLabel = Label::createWithTTF("Silence", "fonts//arial.ttf", 24);
    soundOffLabel->setPosition(200, 500);
    addChild(soundOffLabel);

    auto volumeControlLabel = Label::createWithTTF("Volume", "fonts//arial.ttf", 24);
    volumeControlLabel->setPosition(200, 400);
    addChild(volumeControlLabel);

    auto backgroundAudioVolumeSlider = Slider::create();
    backgroundAudioVolumeSlider->loadBarTexture("res//Slider_Back.png");
    backgroundAudioVolumeSlider->loadSlidBallTextures("res//SliderNode_Normal.png", "res//SliderNode_Press.png",
                                                      "res//SliderNode_Disable.png");
    backgroundAudioVolumeSlider->loadProgressBarTexture("res//Slider_PressBar.png");
    backgroundAudioVolumeSlider->::settingsScene::setPosition(400, 400);

    backgroundAudioVolumeSlider->setPercent(settings::getInstance().backgroundAudioVolume * 100);

    backgroundAudioVolumeSlider->addEventListener(CC_CALLBACK_2(settingsScene::sliderChangesVolume, this));

    addChild(backgroundAudioVolumeSlider);

    auto soundOffCheckbox = CheckBox::create("res//check_box_background.png", "res//check_box_cross.png");

    soundOffCheckbox->::settingsScene::setPosition(300, 500);
    soundOffCheckbox->addEventListener(CC_CALLBACK_2(settingsScene::soundOff, this, backgroundAudioVolumeSlider));

    addChild(soundOffCheckbox);

    return Scene::init();
}

void settingsScene::backToMenu(Ref *sender) {
    auto menuScene = menu::createMenuScene();
    auto transitionScene = TransitionFade::create(0.5f, menuScene);
    Director::getInstance()->replaceScene(transitionScene);
}

void settingsScene::soundOff(Ref *sender, CheckBox::EventType type, Slider *slider) {
    switch (type) {
        case CheckBox::EventType::SELECTED:
            AudioEngine::setVolume(settings::getInstance().backgroundAudioID, 0);
            slider->setEnabled(false);
            break;
        case CheckBox::EventType::UNSELECTED:
            AudioEngine::setVolume(settings::getInstance().backgroundAudioID,
                                   settings::getInstance().backgroundAudioVolume);
            slider->setEnabled(true);
            break;
        default:
            break;
    }
}

void settingsScene::sliderChangesVolume(Ref *sender, Slider::EventType type) {
    auto item = (Slider *) (sender);
    float backgroundAudioVolume = item->getPercent() / 100.0f;
    settings::getInstance().backgroundAudioVolume = backgroundAudioVolume;
    AudioEngine::setVolume(settings::getInstance().backgroundAudioID,
                           settings::getInstance().backgroundAudioVolume);
}
