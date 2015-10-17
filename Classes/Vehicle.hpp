//
//  Vehicle.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 17..
//
//

#pragma once

#include "MovingEntity.hpp"
#include "cocos2d.h"
#include "SteeringBehaviors.hpp"

namespace realtrick
{
    
    class Vehicle : public MovingEntity
    {
        
    private:
        
        cocos2d::Node*              _gameWorld;
        SteeringBehaviors*          _steering;
        
        Vehicle() = delete;
        Vehicle(const Vehicle&) = delete;
        Vehicle& operator=(const Vehicle&) = delete;
        
    public:
        
        Vehicle(cocos2d::Node* world, int id);
        Vehicle(cocos2d::Node* world, int id, const Vector2& pos, double radius);
        
        virtual ~Vehicle()
        {
            delete _steering;
        }
        
        virtual bool handleMessage(const Telegram& msg) override;
        virtual void update(float dt) override;
        
        cocos2d::Node* getGameWorld() const             { return _gameWorld; }
        SteeringBehaviors* getSteering() const          { return _steering; }
        
    };
    
}