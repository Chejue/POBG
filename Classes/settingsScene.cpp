// Created by 冯天阳

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
    addChild(backToMenuButton);

    auto soundOffLabel = Label::createWithTTF("Sound off", "fonts//arial.ttf", 24);
    soundOffLabel->setPosition(200, 500);
    addChild(soundOffLabel);

    auto volumeControlLabel1 = Label::createWithTTF("BGM Volume", "fonts//arial.ttf", 24);
    volumeControlLabel1->setPosition(200, 400);
    addChild(volumeControlLabel1);

    auto volumeControlLabel2 = Label::createWithTTF("Gaming Volume", "fonts//arial.ttf", 24);
    volumeControlLabel2->setPosition(200, 300);
    addChild(volumeControlLabel2);

    auto volumeControlLabel3 = Label::createWithTTF("Effects Volume", "fonts//arial.ttf", 24);
    volumeControlLabel3->setPosition(200, 200);
    addChild(volumeControlLabel3);

    auto bgmOfMenuVolumeSlider = Slider::create();
    bgmOfMenuVolumeSlider->loadBarTexture("res//Slider_Back.png");
    bgmOfMenuVolumeSlider->loadSlidBallTextures("res//SliderNode_Normal.png", "res//SliderNode_Press.png",
                                                "res//SliderNode_Disable.png");
    bgmOfMenuVolumeSlider->loadProgressBarTexture("res//Slider_PressBar.png");
    bgmOfMenuVolumeSlider->::settingsScene::setPosition(500, 400);
    bgmOfMenuVolumeSlider->setPercent(settings::getInstance().backgroundAudioOfMenuVolume * 100);
    bgmOfMenuVolumeSlider->addEventListener(CC_CALLBACK_2(settingsScene::sliderChangesMenuVolume, this));
    addChild(bgmOfMenuVolumeSlider);

    auto bgmOfGamingVolumeSlider = Slider::create();
    bgmOfGamingVolumeSlider->loadBarTexture("res//Slider_Back.png");
    bgmOfGamingVolumeSlider->loadSlidBallTextures("res//SliderNode_Normal.png", "res//SliderNode_Press.png",
                                                  "res//SliderNode_Disable.png");
    bgmOfGamingVolumeSlider->loadProgressBarTexture("res//Slider_PressBar.png");
    bgmOfGamingVolumeSlider->::settingsScene::setPosition(500, 300);
    bgmOfGamingVolumeSlider->setPercent(settings::getInstance().backgroundAudioOfGamingVolume * 100);
    bgmOfGamingVolumeSlider->addEventListener(CC_CALLBACK_2(settingsScene::sliderChangesGamingVolume, this));
    addChild(bgmOfGamingVolumeSlider);

    auto effectsVolumeSlider = Slider::create();
    effectsVolumeSlider->loadBarTexture("res//Slider_Back.png");
    effectsVolumeSlider->loadSlidBallTextures("res//SliderNode_Normal.png", "res//SliderNode_Press.png",
                                              "res//SliderNode_Disable.png");
    effectsVolumeSlider->loadProgressBarTexture("res//Slider_PressBar.png");
    effectsVolumeSlider->::settingsScene::setPosition(500, 200);
    effectsVolumeSlider->setPercent(settings::getInstance().effectsVolume * 100);
    effectsVolumeSlider->addEventListener(CC_CALLBACK_2(settingsScene::sliderChangesEffectsVolume, this));
    addChild(effectsVolumeSlider);


    auto soundOffCheckbox = CheckBox::create("res//check_box_background.png", "res//check_box_cross.png");

    soundOffCheckbox->::settingsScene::setPosition(300, 500);
    soundOffCheckbox->addEventListener(
            CC_CALLBACK_2(settingsScene::soundOff, this, bgmOfMenuVolumeSlider, bgmOfGamingVolumeSlider,
                          effectsVolumeSlider));

    addChild(soundOffCheckbox);

    return Scene::init();
}

void settingsScene::backToMenu(Ref *sender) {
    if (!settings::getInstance().silenced) {
        auto buttonClickedSound = AudioEngine::play2d("music//button_clicked.mp3", false);
        AudioEngine::setVolume(buttonClickedSound, settings::getInstance().effectsVolume);
    }
    auto menuScene = menu::createMenuScene();
    auto transitionScene = TransitionFade::create(0.5f, menuScene);
    Director::getInstance()->replaceScene(transitionScene);
}

void settingsScene::soundOff(Ref *sender, CheckBox::EventType type, Slider *slider1, Slider *slider2, Slider *slider3) {
    switch (type) {
        case CheckBox::EventType::SELECTED:
            AudioEngine::setVolume(settings::getInstance().backgroundAudioOfMenuID, 0);
            AudioEngine::setVolume(settings::getInstance().backgroundAudioOfGamingID, 0);
            settings::getInstance().backgroundAudioOfMenuVolume = 0;
            settings::getInstance().backgroundAudioOfGamingVolume = 0;
            settings::getInstance().effectsVolume = 0;
            slider1->setEnabled(false);
            slider2->setEnabled(false);
            slider3->setEnabled(false);
            break;
        case CheckBox::EventType::UNSELECTED:
            settings::getInstance().backgroundAudioOfMenuVolume = slider1->getPercent() / 100.0f;
            settings::getInstance().backgroundAudioOfGamingVolume = slider2->getPercent() / 100.0f;
            settings::getInstance().effectsVolume = slider3->getPercent() / 100.0f;
            AudioEngine::setVolume(settings::getInstance().backgroundAudioOfMenuID,
                                   settings::getInstance().backgroundAudioOfMenuVolume);
            AudioEngine::setVolume(settings::getInstance().backgroundAudioOfGamingID,
                                   settings::getInstance().backgroundAudioOfGamingVolume);

            slider1->setEnabled(true);
            slider2->setEnabled(true);
            slider3->setEnabled(true);
            break;
        default:
            break;
    }
}

void settingsScene::sliderChangesMenuVolume(Ref *sender, Slider::EventType type) {
    auto item = (Slider *) (sender);
    float Volume = item->getPercent() / 100.0f;
    settings::getInstance().backgroundAudioOfMenuVolume = Volume;
    if (settings::getInstance().bgmOfMenu_started) {
        AudioEngine::setVolume(settings::getInstance().backgroundAudioOfMenuID,
                               settings::getInstance().backgroundAudioOfMenuVolume);
    }
}

void settingsScene::sliderChangesGamingVolume(Ref *sender, Slider::EventType type) {
    auto item = (Slider *) (sender);
    float Volume = item->getPercent() / 100.0f;
    settings::getInstance().backgroundAudioOfGamingVolume = Volume;
    if (settings::getInstance().bgmOfGaming_started) {
        AudioEngine::setVolume(settings::getInstance().backgroundAudioOfGamingID,
                               settings::getInstance().backgroundAudioOfGamingVolume);
    }


}

void settingsScene::sliderChangesEffectsVolume(Ref *sender, Slider::EventType type) {
    auto item = (Slider *) (sender);
    float Volume = item->getPercent() / 100.0f;
    settings::getInstance().effectsVolume = Volume;
}
