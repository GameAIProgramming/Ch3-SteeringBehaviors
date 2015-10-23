//
//  TestScene.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 22..
//
//

#pragma once

#include "cocos2d.h"

#include "Physics.hpp"

class TestScene : public cocos2d::LayerColor
{
    
private:
    
    cocos2d::Size           _winSize;
    cocos2d::DrawNode*      _node1;
    cocos2d::DrawNode*      _node2;
    cocos2d::Vec2           _touchPos;
    realtrick::Rect         _rect;
    realtrick::Circle       _circle;
    realtrick::Circle       _circle2;
    
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(TestScene);
  
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) override;
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) override;
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) override;
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) override;
    virtual void update(float dt) override;
};