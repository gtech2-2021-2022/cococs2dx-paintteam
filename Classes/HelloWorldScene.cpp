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
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <math.h>
#define PI           3.14159265358979323846  /* possiblement */

USING_NS_CC;
using namespace std;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


Size HelloWorld::setTileMap() {

    m_tileMap = CCTMXTiledMap::create("Texture/TestRoom.tmx");
    m_collisions = m_tileMap->layerNamed("Collisions");
    m_collisions->setVisible(false);
    /*
    All layers with != y level 
    DoorsOrigin 8
    Doors 7
    Collisions 6...
    Grass
    Rocks
    Wall2
    Wall
    Ground2 ...1
    Ground 0
    */
    //_tileMap->setTileSize({ 32, 32 }); Does not work maybe call before create?
    m_intermediateNode->addChild(m_tileMap);

    Size const screenSize = Director::getInstance()->getVisibleSize();
    Size const tileMapSize = { m_tileMap->getMapSize().width * m_tileMap->getTileSize().width, m_tileMap->getMapSize().height * m_tileMap->getTileSize().height };

    Size followSize;
    if (screenSize.width < screenSize.height) {
        m_mapRatio = (tileMapSize.height > screenSize.height) ? screenSize.height / tileMapSize.height : tileMapSize.height / screenSize.height;
        followSize = Size({ tileMapSize.width* m_mapRatio, screenSize.height });
    }
    else {
        m_mapRatio = (tileMapSize.width > screenSize.width) ? screenSize.width / tileMapSize.width : tileMapSize.width / screenSize.width;
        followSize = (screenSize.width == screenSize.height) ? Size({ screenSize.width, screenSize.height }) : Size({screenSize.width, tileMapSize.height* m_mapRatio });
    }
    
    m_tileMap->setScale(m_mapRatio);
    return followSize;
}

Vec2 HelloWorld::getTileNumber(Vec2 coords) {
    Vec2 tileSize = m_tileMap->getTileSize() * m_mapRatio;
    Vec2 tileCoord = coords - Vec2(fmod(coords.x, tileSize.x), fmod(coords.y, tileSize.y));
    Vec2 tileNumber = Vec2(floor(tileCoord.x/tileSize.x), ceil(m_tileMap->getMapSize().height - 1 - tileCoord.y/tileSize.y)); // -1 because y starts at 0 for tiles but height must be < mapSize
    return tileNumber;
}

float HelloWorld::compareToOffset(float player, float screen, float tileMap) {
    if (player > screen / 2) {
        if (player < tileMap - (screen / 2)) {
            // Follow transition
            return player - (screen / 2);
        }
        // Top fixed
        return tileMap - screen;
    }
    return 0.f;
}

Vec2 HelloWorld::offSetScreen(Vec2 playerLocation) {
    Size const screenSize = Director::getInstance()->getVisibleSize();
    if (screenSize.width > screenSize.height) {
        return Vec2(0.f, compareToOffset(playerLocation.y, screenSize.height, m_tileMap->getMapSize().height * m_tileMap->getTileSize().height * m_mapRatio));
    }
    else if (screenSize.width < screenSize.height) {
        return Vec2(0.f, compareToOffset(playerLocation.x, screenSize.width, m_tileMap->getMapSize().width * m_tileMap->getTileSize().width * m_mapRatio));
    } 
    else {
        return Vec2(0.f, 0.f);
    }
}

void HelloWorld::setDirection(float directionAngle) {
    if (directionAngle > 45 && directionAngle < 135)
    {
        player.setDirection(UP);
        pokemon.setDirection(DOWN);
    }
    else if (directionAngle > 135 && directionAngle < 225)
    {
        player.setDirection(LEFT);
        pokemon.setDirection(RIGHT);
    }
    else if (directionAngle > 225 && directionAngle < 315)
    {
        player.setDirection(DOWN);
        pokemon.setDirection(UP);
    }
    else
    {
        player.setDirection(RIGHT);
        pokemon.setDirection(LEFT);
    }
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

    m_intermediateNode = Node::create();
    this->addChild(m_intermediateNode);

    Director::getInstance()->setContentScaleFactor(1);
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Add map
    Size const followSize = setTileMap();
    

    //Add character
    player.setPlayerSprite("player/player.png", Rect(0, 0, 32, 32));
    auto _player = player.getPlayerSprite();
    _player->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    _player->setScale(1.5f, 1.5f);
    m_intermediateNode->addChild(_player, 1);

    // follow the player
    auto followTheSprite = Follow::create(_player, Rect(0,0,followSize.width, followSize.height));
    m_intermediateNode->runAction(followTheSprite);

    //Animation of the character
    player.createAnimation();

    //Character's life
    auto _charaLife = charaLife->getLifeBar();
    if (_charaLife == nullptr)
    {
        Utils::problemLoading("'life.png'");
    }
    else
    {
        _charaLife->setPosition(Vec2(16, 35));
        _charaLife->setPercent(100);
        _charaLife->setScale(1.5f, 1.5f);
        _player->addChild(_charaLife, 1);
    }

    //Add characters's stat
    auto _playerAtkSprite = Sprite::create("atk.png");
    _playerAtkSprite->setScale(0.025f, 0.025f);
    _playerAtkSprite->setPosition(Vec2(3, 44));
    _player->addChild(_playerAtkSprite, 1);
    auto _playerAtk = Label::createWithTTF(to_string(player.getWeaponDamage(player.getWeapon())), "fonts/arial.ttf", 8);
    _playerAtk->setTextColor(Color4B::BLACK);
    _playerAtk->setPosition(Vec2(12, 42));
    _player->addChild(_playerAtk, 1);

    auto _playerDefSprite = Sprite::create("def.png");
    _playerDefSprite->setScale(0.025f, 0.025f);
    _playerDefSprite->setPosition(Vec2(23, 44));
    _player->addChild(_playerDefSprite, 1);
    auto _playerDef = Label::createWithTTF(to_string(player.getDefense()), "fonts/arial.ttf", 8);
    _playerDef->setTextColor(Color4B::BLACK);
    _playerDef->setPosition(Vec2(31, 42));
    _player->addChild(_playerDef, 1);

    //Add pokemon
    pokemon.setMonsterSprite();
    auto _pokemon = pokemon.getMonsterSprite();
    _pokemon->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 1.25 + origin.y));
    _pokemon->setScale(1.5f, 1.5f);
    _pokemon->setName("pokemon");
    m_intermediateNode->addChild(_pokemon, 0);

    //Animation of the pokemon
    pokemon.createAnimation();

    //Pokemon's life
    auto _pokeLife = pokeLife->getLifeBar();
    if (_pokeLife == nullptr)
    {
        Utils::problemLoading("'life.png'");
    }
    else
    {
        _pokeLife->setPosition(Vec2(16, 35));
        _pokeLife->setPercent(100);
        _pokeLife->setScale(1.5f, 1.5f);
        _pokemon->addChild(_pokeLife, 0);
    }

    //Add pokemon's stat
    auto _pokeAtkSprite = Sprite::create("atk.png");
    _pokeAtkSprite->setScale(0.025f, 0.025f);
    _pokeAtkSprite->setPosition(Vec2(6, 44));
    _pokemon->addChild(_pokeAtkSprite, 0);
    auto _pokeAtk = Label::createWithTTF(to_string(pokemon.getDamage()), "fonts/arial.ttf", 8);
    _pokeAtk->setTextColor(Color4B::BLACK);
    _pokeAtk->setPosition(Vec2(15, 42));
    _pokemon->addChild(_pokeAtk, 0);

    //Add pokeball
    pokeball.setTreasureSprite("player/pokeball.png", Rect(0, 0, 16, 24));
    auto _pb = pokeball.getTreasureSprite();
    _pb->setPosition(Vec2(visibleSize.width / 2 + origin.x + 50, visibleSize.height / 1.25 + origin.y));
    _pb->setScale(1.5f, 1.5f);
    m_intermediateNode->addChild(_pb, 0);

    //Add fightButton
    auto fightButton = MenuItemImage::create("fight.png", "fight.png",
        [=](Ref*) {
            fightPokemon(_player, _pokemon);
        });
    if (fightButton == nullptr || fightButton->getContentSize().width <= 0 || fightButton->getContentSize().height <= 0) {
        Utils::problemLoading("'fight.png'");
    }
    auto fight = Menu::create(fightButton, NULL);
    fight->setPosition(Vec2::ZERO);
    fight->setVisible(false);
    fight->setName("fight");
    m_intermediateNode->addChild(fight, 1);

    //Add pickButton
    auto pickButton = MenuItemImage::create("pick.png", "pick.png",
        [=](Ref*) {
            pickPockeball(_pb, visibleSize, origin);
        });
    if (pickButton == nullptr || pickButton->getContentSize().width <= 0 || pickButton->getContentSize().height <= 0) {
        Utils::problemLoading("'pick.png'");
    }
    auto pick = Menu::create(pickButton, NULL);
    pick->setPosition(Vec2::ZERO);
    pick->setVisible(false);
    pick->setName("pick");
    m_intermediateNode->addChild(pick, 1);
    
    //Add MapButton
    auto mapButton = MenuItemImage::create("map.png", "map.png",
        [=](Ref*) {
    
        });
    if (mapButton == nullptr || mapButton->getContentSize().width <= 0 || mapButton->getContentSize().height <= 0) {
        Utils::problemLoading("'map.png'");
    }
    auto mapB = Menu::create(mapButton, NULL);
    mapB->setPosition(Vec2(visibleSize.width - (mapB->getContentSize().width/20), visibleSize.height - (mapB->getContentSize().height /20)));
    mapB->setScale(m_mapButtonRatio);
    mapB->setVisible(true);
    m_intermediateNode->addChild(mapB, 1);

    //Move character on click
    auto listener = EventListenerTouchOneByOne::create();
    const int movementTag = 1; // constexpr
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        fight->setVisible(false);
        pick->setVisible(false);
        Vec2 const pos = touch->getLocation() + offSetScreen(_player->getPosition());
        MoveTo* move = MoveTo::create(Vec2(pos - _player->getPosition()).length() / player.getPixelSpeed(), pos);
        setDirection(fmod(Vec2(_player->getPosition().x - pos.x, _player->getPosition().y - pos.y).getAngle() * 180 / PI + 180, 360));
        player.updateAnimation(_player, player.getDirection());
        auto playerStop = [=]() {
            player.becomeIdle();
            CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/walk/walk1.wav"));
            if (_player->getBoundingBox().intersectsRect(_pb->getBoundingBox()) && !pokeball.isOpen()) {
                float x = origin.x + visibleSize.width - pickButton->getContentSize().width / 20;
                float y = origin.y + pickButton->getContentSize().height / 20;
                pickButton->setPosition(Vec2(x, y) + offSetScreen(pos));
                pickButton->setScale(0.1f, 0.1f);
                pick->setVisible(true);
            }
            if (m_intermediateNode->getChildByName("pokemon")) {
                if (_player->getBoundingBox().intersectsRect(_pokemon->getBoundingBox())) {
                    float x = origin.x + visibleSize.width - fightButton->getContentSize().width / 20;
                    float y = origin.y + fightButton->getContentSize().height / 20;
                    fightButton->setPosition(Vec2(x, y) + offSetScreen(pos));
                    fightButton->setScale(0.1f, 0.1f);
                    fight->setVisible(true);
                }
            }
        };
        CallFunc* becomeIdle = CallFunc::create(playerStop);
        //move->setTag(movementTag);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/walk/walk1.wav");
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/walk/walk1.wav", true);
        Sequence* moveThenIdle = Sequence::create({move, becomeIdle});

        if (_player->getNumberOfRunningActions() == 0) {
            _player->runAction(moveThenIdle);
        }
        else if (_player->getNumberOfRunningActions() != 0) {
            _player->stopActionByTag(movementTag);
            _player->runAction(moveThenIdle);
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void HelloWorld::fightPokemon(Sprite* _player , Sprite* _pk) {
    player.updateAnimation(_player, player.getDirection());
    pokemon.updateAnimation(_pk, pokemon.getDirection());
    Vec2 playerPos = _player->getPosition();
    Vec2 pokemonPos = _pk->getPosition();
    MoveTo* move1 = MoveTo::create(Vec2(pokemonPos - playerPos).length() / player.getPixelSpeed(), Vec2((playerPos.x + pokemonPos.x) / 2, (playerPos.y + pokemonPos.y) / 2));
    MoveTo* move2 = MoveTo::create(Vec2(playerPos - pokemonPos).length() / player.getPixelSpeed(), Vec2((playerPos.x + pokemonPos.x) / 2, (playerPos.y + pokemonPos.y) / 2));
    auto idlePlayer = [=]() {
        player.becomeIdle();
        _player->setPosition(playerPos);
    };
    auto idlePokemon = [=]() {
        pokemon.becomeIdle();
        _pk->setPosition(pokemonPos);
        pokemon.receiveDammage(player.getWeaponDamage(player.getWeapon()));
        pokeLife->updateLife(player.getWeaponDamage(player.getWeapon()));
        if (pokeLife->getLife() != 0) {
            player.receiveDammage(pokemon.getDamage());
            charaLife->updateLife(pokemon.getDamage());
            if (charaLife->getLife() <= 0) {
                auto director = Director::getInstance();
                auto scene = GameOver::createScene();
                director->replaceScene(scene);
            }
        }
        else {
            m_intermediateNode->removeChild(_pk);
            Node* _button = m_intermediateNode->getChildByName("fight");
            _button->setVisible(false);
        }
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/damage/uuuu.wav");
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/damage/uuuu.wav");
    };
    CallFunc* becomeIdlePlayer = CallFunc::create(idlePlayer);
    Sequence* attackPlayer = Sequence::create({ move1, becomeIdlePlayer});
    _player->runAction(attackPlayer);
    CallFunc* becomeIdlePokemon = CallFunc::create(idlePokemon);
    Sequence* attackPokemon = Sequence::create({ move2, becomeIdlePokemon }); 
    _pk->runAction(attackPokemon);
}

void HelloWorld::pickPockeball(Sprite* _pb, Size _size, Vec2 _origin) {
    if (!pokeball.isOpen()) {
        player.setGold(pokeball.getGoldNumber());
        pokeball.setOpen(true);
        auto anim = [=] {
            Animation* openAnimation = Animation::create();
            for (int i = 0; i < 3; i++)
            {
                openAnimation->addSpriteFrame(SpriteFrame::create("player/pokeball.png", Rect(i * 16, 0, 16, 24)));
            }
            openAnimation->setDelayPerUnit(0.25);
            auto sf = openAnimation->getFrames().at(0)->getSpriteFrame();
            auto action = Animate::create(openAnimation);
            _pb->runAction(action);
        };
        auto timer1 = DelayTime::create(0.75);
        static Label* amount;
        static Sprite* dollard;
        auto showPKD = [=] {
            amount = Label::createWithTTF("+" + to_string(pokeball.getGoldNumber()), "fonts/arial.ttf", 14);
            amount->setPosition(Vec2(_size.width / 2 + _origin.x + 40, _size.height / 1.25 + _origin.y + 24));
            amount->setTextColor(Color4B::BLACK);
            m_intermediateNode->addChild(amount, 0);
            dollard = Sprite::create("tresure.png");
            dollard->setScale(0.1f, 0.1f);
            dollard->setPosition(Vec2(_size.width / 2 + _origin.x + 56, _size.height / 1.25 + _origin.y + 24));
            m_intermediateNode->addChild(dollard, 1);
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/tresure/coins2.wav");
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/tresure/coins2.wav");
            Node* _button = m_intermediateNode->getChildByName("pick");
            _button->setVisible(false);
        };
        auto timer2 = DelayTime::create(2);
        auto hidePKD = [=] {
            m_intermediateNode->removeChild(amount);
            m_intermediateNode->removeChild(dollard);
        };
        CallFunc* open = CallFunc::create(anim);
        CallFunc* show = CallFunc::create(showPKD);
        CallFunc* hide = CallFunc::create(hidePKD);
        Sequence* getPKD = Sequence::create({ open, timer1, show, timer2, hide });
        runAction(getPKD);
    }
}