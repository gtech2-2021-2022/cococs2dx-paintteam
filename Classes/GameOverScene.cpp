#include "AppDelegate.h"
#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    return GameOver::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Add map
    /*auto sprite = Sprite::create("main.png");
    sprite->setScale(1.7f,1.25f);
    if (sprite == nullptr)
    {
        problemLoading("'main.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }*/

    //Add font
    auto restartLabel = Label::createWithTTF("Restart", "fonts/PokemonSolid.ttf", 40);
    restartLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(restartLabel, 0);

    auto menuLabel = Label::createWithTTF("Menu", "fonts/PokemonSolid.ttf", 40);
    menuLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 50));
    this->addChild(menuLabel, 0);

    //Detect click on label
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        Vec2 pos = touch->getLocation();
        auto nodePosStart = restartLabel->convertToNodeSpace(pos);
        auto restart = restartLabel->getContentSize();
        if (nodePosStart.x >= 0 && nodePosStart.y >= 0 && nodePosStart.x < restart.width && nodePosStart.y < restart.height) {
            auto director = Director::getInstance();
            auto scene = HelloWorld::createScene();
            director->replaceScene(scene);
        }
        auto nodePosLeave = menuLabel->convertToNodeSpace(pos);
        auto menu = menuLabel->getContentSize();
        if (nodePosLeave.x >= 0 && nodePosLeave.y >= 0 && nodePosLeave.x < menu.width && nodePosLeave.y < menu.height) {
            auto director = Director::getInstance();
            auto scene = MainMenu::createScene();
            director->replaceScene(scene);
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}