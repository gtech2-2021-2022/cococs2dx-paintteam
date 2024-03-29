#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenu::init()
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
    auto sprite = Sprite::create("main.png");
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
    }

    //Add font
    auto nameLabel = Label::createWithTTF("Pokemon Dungeon", "fonts/PokemonSolid.ttf", 40);
    nameLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 75));
    nameLabel->setTextColor(Color4B::BLACK);
    this->addChild(nameLabel, 0);

    auto startLabel = Label::createWithTTF("Start", "fonts/PokemonSolid.ttf", 40);
    startLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    startLabel->setTextColor(Color4B::BLACK);
    this->addChild(startLabel, 0);

    auto leaveLabel = Label::createWithTTF("Leave", "fonts/PokemonSolid.ttf", 40);
    leaveLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 70));
    leaveLabel->setTextColor(Color4B::BLACK);
    this->addChild(leaveLabel, 0);

    //Detect click on label
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        Vec2 pos = touch->getLocation();
        auto nodePosStart = startLabel->convertToNodeSpace(pos);
        auto start = startLabel->getContentSize();
        if (nodePosStart.x >= 0 && nodePosStart.y >= 0 && nodePosStart.x < start.width && nodePosStart.y < start.height) {
            auto director = Director::getInstance();
            auto scene = HelloWorld::createScene();
            director->replaceScene(scene);
        }
        auto nodePosLeave = leaveLabel->convertToNodeSpace(pos);
        auto leave = leaveLabel->getContentSize();
        if (nodePosLeave.x >= 0 && nodePosLeave.y >= 0 && nodePosLeave.x < leave.width && nodePosLeave.y < leave.height) {
            menuCloseCallback(this);
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}