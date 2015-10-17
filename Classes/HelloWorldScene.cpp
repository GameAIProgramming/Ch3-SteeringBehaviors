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
    initEntites();
    
    
    
    return true;
}

void HelloWorldScene::initEntites()
{
    for(int i = 0 ; i < 200 ; ++ i)
    {
        Vehicle* vehicle = new Vehicle(getNextValidID());
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
        Sprite* entity = (Sprite*)_spriteManager->getChildByTag(d.second->getID());
        entity->setPosition(Vec2(d.second->getPos().x, d.second->getPos().y));
    }
}















