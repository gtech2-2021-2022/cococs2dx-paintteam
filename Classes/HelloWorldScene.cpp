/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "entities.h"
#include "Utils.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    Director::getInstance()->setContentScaleFactor(1);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*/////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////*/

    //Add map
  
    _tileMap = CCTMXTiledMap::create("Texture/TestRoom.tmx");
    // _tileMap->initWithTMXFile("Texture/TestRoom.tmx");

    /* 
    Doors
    Collisions
    Doors
    Grass
    Rocks
    Wall2
    Wall
    Ground2
    Ground
    */

    _collisions = _tileMap->layerNamed("Collisions");
    _collisions->setVisible(false);


    this->addChild(_tileMap);

    //Add character
    Player player;
    player.setPlayerSprite("player/player.png", Rect(0, 0, 20, 20));
    auto _player = player.getPlayerSprite();
    _player->setScale(2,2);
    if (_player == nullptr)
    {
        problemLoading("'player/player.png'");
    }
    else
    {
        _player->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(_player, 0);
    }

    //Move character on click
    auto listener = EventListenerTouchOneByOne::create();
    const int movementTag = 1;
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        Vec2 pos;
        pos = touch->getLocation();
        auto move = MoveTo::create(3, pos);
        move->setTag(movementTag);
        if (_player->getNumberOfRunningActions() == 0) {
            _player->runAction(move);
        }
        else if (_player->getNumberOfRunningActions() != 0) {
            _player->stopActionByTag(movementTag);
            _player->runAction(move);
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //Animation of the character
    Utils utils;
    utils.createAnimation();
    auto anim = AnimationCache::getInstance()->getAnimation("walkAnimation");
    auto sf = anim->getFrames().at(0)->getSpriteFrame();
    auto action = Animate::create(anim);
    _player->runAction(RepeatForever::create(action));

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

