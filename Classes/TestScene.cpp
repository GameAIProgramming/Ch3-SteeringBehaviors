//
//  TestScene.cpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 22..
//
//

#include "TestScene.hpp"

using namespace cocos2d;
using namespace realtrick;
using namespace realtrick::physics;

Scene* TestScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TestScene::create();
    scene->addChild(layer);
    
    return scene;

}

bool TestScene::init()
{
    if(!cocos2d::LayerColor::initWithColor(Color4B::BLUE))
    {
        return false;
    }
    
    this->scheduleUpdate();
    _winSize = Director::getInstance()->getVisibleSize();
    
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = CC_CALLBACK_2(TestScene::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(TestScene::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(TestScene::onTouchesEnded, this);
    touchListener->onTouchesCancelled = CC_CALLBACK_2(TestScene::onTouchesCancelled, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    _touchPos = Vec2::ZERO;
    _rect = realtrick::Rect(0.0, 0.0, 100.0, 100.0);
    _circle = realtrick::Circle(568.0, 320.0, 100.0);
    
    _node1 = DrawNode::create();
    addChild(_node1);
    
    _node2 = DrawNode::create();
    addChild(_node2);
    
//    Vec2 v[5]
//    {
//        Vec2(_winSize.width / 2 - 50, _winSize.height / 2 - 100),
//        Vec2(_winSize.width / 2 - 100, _winSize.height / 2 - 20),
//        Vec2(_winSize.width / 2, _winSize.height / 2 + 50),
//        Vec2(_winSize.width / 2 + 100, _winSize.height / 2 - 20),
//        Vec2(_winSize.width / 2 + 50, _winSize.height / 2 - 100)
//    };
//    _node->drawPolygon(v, 5, Color4F(0.0f, 0.0f, 0.0f, 0.0f), 1.0f, Color4F::RED);
//
//    _node->drawSegment(Vec2(100.0f, _winSize.height / 2), Vec2(_winSize.width - 100, _winSize.height / 2), 1.0f, Color4F::WHITE);
//    
//    _node->drawDot(Vec2(_winSize/2), 3.0f, Color4F::YELLOW);

    
    return true;
}


void TestScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    for(auto &d : touches)
    {
        Vec2 touchPos = d->getLocation();
        _touchPos = touchPos;
    }
}

void TestScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    for(auto &d : touches)
    {
        Vec2 touchPos = d->getLocation();
        _touchPos = touchPos;
    }
}

void TestScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    for(auto &d : touches)
    {
        Vec2 touchPos = d->getLocation();
        _touchPos = touchPos;
    }
}

void TestScene::onTouchesCancelled(const std::vector<Touch*>& touches, Event *unused_event)
{
    for(auto &d : touches)
    {
        Vec2 touchPos = d->getLocation();
        _touchPos = touchPos;
    }
}

void TestScene::update(float dt)
{
    _node1->clear();
    _node2->clear();
    
    _node1->drawCircle(Vec2(_circle.origin.x, _circle.origin.y), _circle.radius, 360.0f, 100.0f, true, 1.0f, 1.0f, Color4F::MAGENTA);
    
//    Vec2 v[4]
//    {
//        Vec2(_touchPos.x - _rect.width / 2, _touchPos.y - _rect.height / 2),
//        Vec2(_touchPos.x - _rect.width / 2, _touchPos.y + _rect.height / 2),
//        Vec2(_touchPos.x + _rect.width / 2, _touchPos.y + _rect.height / 2),
//        Vec2(_touchPos.x + _rect.width / 2, _touchPos.y - _rect.height / 2)
//    };
//    _rect.setRect(v[0].x, v[0].y, 100.0, 100.0);
//    _node2->drawPolygon(v, 4, Color4F(0.0f, 0.0f, 0.0f, 0.0f), 1.0f, Color4F::WHITE);
//    
//    if(physics::intersect(_rect, _circle) == true)
//    {
//        log("intersect.");
//    }
//    else
//    {
//        log("not intersect.");
//    }
    
    _circle2.setCircle(_touchPos.x, _touchPos.y, 100.0);
    
    _node2->drawCircle(Vec2(_circle2.origin.x, _circle2.origin.y), 100.0, 360.0f, 100.0f, true, 1.0f, 1.0f, Color4F::WHITE);
    
    if(physics::intersect(_circle, _circle2))
        log("intersect");
    else
        log("not intersect");
    
}
















