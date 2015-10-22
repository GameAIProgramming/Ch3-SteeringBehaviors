//
//  TestScene.cpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 22..
//
//

#include "TestScene.hpp"

using namespace cocos2d;

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
    
    _winSize = Director::getInstance()->getVisibleSize();
    
    _node = DrawNode::create();
    addChild(_node);
    
    Vec2 v[5]
    {
        Vec2(_winSize.width / 2 - 50, _winSize.height / 2 - 100),
        Vec2(_winSize.width / 2 - 100, _winSize.height / 2 - 20),
        Vec2(_winSize.width / 2, _winSize.height / 2 + 50),
        Vec2(_winSize.width / 2 + 100, _winSize.height / 2 - 20),
        Vec2(_winSize.width / 2 + 50, _winSize.height / 2 - 100)
    };
    _node->drawPolygon(v, 5, Color4F(0.0f, 0.0f, 0.0f, 0.0f), 1.0f, Color4F::RED);

    _node->drawSegment(Vec2(100.0f, _winSize.height / 2), Vec2(_winSize.width - 100, _winSize.height / 2), 1.0f, Color4F::WHITE);
    
    _node->drawDot(Vec2(_winSize/2), 3.0f, Color4F::YELLOW);
    
    return true;
}








