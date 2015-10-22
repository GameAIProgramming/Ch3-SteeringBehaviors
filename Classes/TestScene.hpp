//
//  TestScene.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 22..
//
//

#pragma once

#include "cocos2d.h"

class TestScene : public cocos2d::LayerColor
{
    
private:
    
    cocos2d::Size           _winSize;
    cocos2d::DrawNode*      _node;
    
    
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(TestScene);
    
};