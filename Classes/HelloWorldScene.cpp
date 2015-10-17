#include "HelloWorldScene.h"
#include "EntityManager.hpp"
#include "Vehicle.hpp"

USING_NS_CC;
using namespace realtrick;

int HelloWorldScene::_nextValidID = 0;

Scene* HelloWorldScene::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorldScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool HelloWorldScene::init()
{
    if ( !LayerColor::initWithColor(Color4B::WHITE) )
    {
        return false;
    }

    this->scheduleUpdate();
    srand((unsigned int)time(nullptr));
    _winSize = Director::getInstance()->getVisibleSize();
    
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = CC_CALLBACK_2(HelloWorldScene::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(HelloWorldScene::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(HelloWorldScene::onTouchesEnded, this);
    touchListener->onTouchesCancelled = CC_CALLBACK_2(HelloWorldScene::onTouchesCancelled, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    initUI();
    initEntites();
    
    
    
    return true;
}

void HelloWorldScene::initEntites()
{
    for(int i = 0 ; i < 200 ; ++ i)
    {
        Vehicle* vehicle = new Vehicle(this, getNextValidID());
        vehicle->setPos(Vector2(rand() % 1136, rand() % 640));
        EntMgr.registEntity(vehicle);
    }
    
    _spriteManager = Sprite::create();
    addChild(_spriteManager);
    
    auto entities = EntMgr.getEntMap();
    for(auto &d : entities)
    {
        Sprite* entity = Sprite::create("Vehicle.png");
        entity->setTag(d.second->getID());
        entity->setPosition(Vec2(d.second->getPos().x, d.second->getPos().y));
        _spriteManager->addChild(entity);
    }
}

void HelloWorldScene::update(float dt)
{
    EntMgr.updateEntities(dt);

    auto entities = EntMgr.getEntMap();
    for(auto &d : entities)
    {
        Vehicle* vehicle = (Vehicle*)d.second;
        Sprite* entity = (Sprite*)_spriteManager->getChildByTag(vehicle->getID());
        entity->setPosition(Vec2(vehicle->getPos().x, vehicle->getPos().y));
        entity->setRotation(calAngle(Vec2(vehicle->getHeading().x, vehicle->getHeading().y)));
    }
}

void HelloWorldScene::initUI()
{
    _uiLayer = Sprite::create();
    this->addChild(_uiLayer);
    
    _crossHair = Sprite::create();
    
    DrawNode* node = DrawNode::create();
    node->drawSegment(Vec2(-7.0f, -7.0f), Vec2(-3.0f, -3.0f), 1.0f, Color4F::MAGENTA);
    node->drawSegment(Vec2(7.0f, -7.0f), Vec2(3.0f, -3.0f), 1.0f, Color4F::MAGENTA);
    node->drawSegment(Vec2(7.0f, 7.0f), Vec2(3.0f, 3.0f), 1.0f, Color4F::MAGENTA);
    node->drawSegment(Vec2(-7.0f, 7.0f), Vec2(-3.0f, 3.0f), 1.0f, Color4F::MAGENTA);
    _crossHair->addChild(node);
    _crossHair->setPosition(_winSize / 2);
    _crossHair->runAction(RepeatForever::create(RotateBy::create(1.0f, 90.0f)));
    _uiLayer->addChild(_crossHair);
}


void HelloWorldScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    for(auto &d : touches)
    {
        Vec2 touchPos = d->getLocation();
        _crossHair->setPosition(touchPos);
    }
}

void HelloWorldScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    for(auto &d : touches)
    {
        Vec2 touchPos = d->getLocation();
        _crossHair->setPosition(touchPos);
    }
}

void HelloWorldScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    for(auto &d : touches)
    {
        Vec2 touchPos = d->getLocation();
        _crossHair->setPosition(touchPos);
    }
}

void HelloWorldScene::onTouchesCancelled(const std::vector<Touch*>& touches, Event *unused_event)
{
    for(auto &d : touches)
    {
        Vec2 touchPos = d->getLocation();
        _crossHair->setPosition(touchPos);
    }
}


float HelloWorldScene::calAngle(const Vec2& v)
{
    Vec2 axis(0.f, 1.f);
    Vec2 rotated90 = axis.getRPerp();
    
    float angle = MathRadianToDegree(acos((rotated90.x * v.x + rotated90.y * v.y) / (sqrt(rotated90.x * rotated90.x + rotated90.y * rotated90.y) * sqrt(v.x * v.x + v.y * v.y))));
    if (angle > 90)
    {
        return 360 - MathRadianToDegree(acos((axis.x * v.x + axis.y * v.y) / (sqrt(axis.x * axis.x + axis.y * axis.y) * sqrt(v.x * v.x + v.y * v.y))));
    }
    
    return MathRadianToDegree(acos((axis.x * v.x + axis.y * v.y) / (sqrt(axis.x * axis.x + axis.y * axis.y) * sqrt(v.x * v.x + v.y * v.y))));
}





