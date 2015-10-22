#include "HelloWorldScene.hpp"
#include "EntityManager.hpp"
#include "Vehicle.hpp"
#include "ParamLoader.hpp"

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
    if ( !LayerColor::initWithColor(Color4B::GRAY) )
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
    int numOfEntity = Prm.getValueAsInt("NumOfEntity");
    for(int i = 0 ; i < numOfEntity ; ++ i)
    {
        Vehicle* vehicle = new Vehicle(this, getNextValidID());
        vehicle->setPos(Vector2(rand() % 600, rand() % 600));
        EntMgr.registEntity(vehicle);
    }
    
    _spriteManager = Sprite::create();
    _gameView->addChild(_spriteManager);
    
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
    
    _gameView = Sprite::create();
    _gameView->setPosition(Vec2(20.0f, 20.0f));
    DrawNode* gameViewNode = DrawNode::create();
    gameViewNode->drawSegment(Vec2::ZERO, Vec2(600.0f, 0.0f), 1.0f, Color4F::RED);
    gameViewNode->drawSegment(Vec2(600.0f, 0.0f), Vec2(600.0f, 600.0f), 1.0f, Color4F::RED);
    gameViewNode->drawSegment(Vec2(600.0f, 600.0f), Vec2(0.0f, 600.0f), 1.0f, Color4F::RED);
    gameViewNode->drawSegment(Vec2(0.0f, 600.0f), Vec2::ZERO, 1.0f, Color4F::RED);
    //_gameView->addChild(gameViewNode);
    addChild(_gameView, 0);
    
    _optionView = Sprite::create();
    _optionView->setPosition(Vec2(640.0f, 20.0f));
    DrawNode* optionViewNode = DrawNode::create();
    optionViewNode->drawSegment(Vec2::ZERO, Vec2(476.0f, 0.0f), 1.0f, Color4F::RED);
    optionViewNode->drawSegment(Vec2(476.0f, 0.0f), Vec2(476.0f, 600.0f), 1.0f, Color4F::RED);
    optionViewNode->drawSegment(Vec2(476.0f, 600.0f), Vec2(0.0f, 600.0f), 1.0f, Color4F::RED);
    optionViewNode->drawSegment(Vec2(0.0f, 600.0f), Vec2::ZERO, 1.0f, Color4F::RED);
    //_optionView->addChild(optionViewNode);
    addChild(_optionView, 0);
    
    _uiLayer = Sprite::create();
    addChild(_uiLayer, 1);
    
    DrawNode* bgNode = DrawNode::create();
    bgNode->drawSolidRect(Vec2::ZERO, Vec2(1136.0f, 20.0f), Color4F::BLACK);
    bgNode->drawSolidRect(Vec2::ZERO, Vec2(20.0f, 640.0f), Color4F::BLACK);
    bgNode->drawSolidRect(Vec2(620.0f, 0.0f), Vec2(640.0f, 640.0f), Color4F::BLACK);
    bgNode->drawSolidRect(Vec2(1116.0f, 0.0f), Vec2(1136.0f, 640.0f), Color4F::BLACK);
    bgNode->drawSolidRect(Vec2(0.0f, 620.0f), Vec2(1136.0f, 640.0f), Color4F::BLACK);
    addChild(bgNode,2);
    
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
        
        if(touchPos.x > 620.0f) touchPos.x = 620.0f;
        else if(touchPos.x < 20.0f) touchPos.x = 20.0f;
        
        if(touchPos.y > 620.0f) touchPos.y = 620.0f;
        else if(touchPos.y < 20.0f) touchPos.y = 20.0f;
        
        _crossHair->setPosition(touchPos);
    }
}

void HelloWorldScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    for(auto &d : touches)
    {
        Vec2 touchPos = d->getLocation();
        
        if(touchPos.x > 620.0f) touchPos.x = 620.0f;
        else if(touchPos.x < 20.0f) touchPos.x = 20.0f;
        
        if(touchPos.y > 620.0f) touchPos.y = 620.0f;
        else if(touchPos.y < 20.0f) touchPos.y = 20.0f;
        
        _crossHair->setPosition(touchPos);
    }
}

void HelloWorldScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    for(auto &d : touches)
    {
        Vec2 touchPos = d->getLocation();
        
        if(touchPos.x > 620.0f) touchPos.x = 620.0f;
        else if(touchPos.x < 20.0f) touchPos.x = 20.0f;
        
        if(touchPos.y > 620.0f) touchPos.y = 620.0f;
        else if(touchPos.y < 20.0f) touchPos.y = 20.0f;
        
        _crossHair->setPosition(touchPos);
    }
}

void HelloWorldScene::onTouchesCancelled(const std::vector<Touch*>& touches, Event *unused_event)
{
    for(auto &d : touches)
    {
        Vec2 touchPos = d->getLocation();
        
        if(touchPos.x > 620.0f) touchPos.x = 620.0f;
        else if(touchPos.x < 20.0f) touchPos.x = 20.0f;
        
        if(touchPos.y > 620.0f) touchPos.y = 620.0f;
        else if(touchPos.y < 20.0f) touchPos.y = 20.0f;
        
        _crossHair->setPosition(touchPos);
    }
}


float HelloWorldScene::calAngle(const Vec2& v)
{
    Vec2 axis(0.0f, 1.0f);
    Vec2 rotated90 = axis.getRPerp();
    
    float angle = MathRadianToDegree(acos((rotated90.x * v.x + rotated90.y * v.y) / (sqrt(rotated90.x * rotated90.x + rotated90.y * rotated90.y) * sqrt(v.x * v.x + v.y * v.y))));
    if (angle > 90.0f)
    {
        return 360.0f - MathRadianToDegree(acos((axis.x * v.x + axis.y * v.y) / (sqrt(axis.x * axis.x + axis.y * axis.y) * sqrt(v.x * v.x + v.y * v.y))));
    }
    
    return MathRadianToDegree(acos((axis.x * v.x + axis.y * v.y) / (sqrt(axis.x * axis.x + axis.y * axis.y) * sqrt(v.x * v.x + v.y * v.y))));
}





