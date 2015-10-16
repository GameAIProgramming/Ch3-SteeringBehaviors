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

namespace realtrick
{
    
    class Vehicle : public MovingEntity
    {
        
    private:
        
        cocos2d::Scene*             _gameWorld;
        
        
        Vehicle() = delete;
        Vehicle(const Vehicle&) = delete;
        Vehicle& operator=(const Vehicle&) = delete;
        
    public:
        
        Vehicle(int id);
        Vehicle(int id, const Vector2& pos, double radius);
        
        virtual ~Vehicle()
        {}
        
        virtual bool handleMessage(const Telegram& msg) override;
        virtual void update(float dt) override;
        
    };
    
}