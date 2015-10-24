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

class HelloWorldScene;

namespace realtrick
{
    
    class Vehicle : public MovingEntity
    {
        
    private:
        
        HelloWorldScene*            _gameWorld;
        SteeringBehaviors*          _steering;
        
        float                       _timeElapsed;
        
    private:
        
        Vehicle();
        
    public:
        
        static Vehicle* create(const std::string& fileName);
        
        virtual ~Vehicle()
        {
            delete _steering;
        }
        
        virtual bool handleMessage(const Telegram& msg) override;
        virtual void update(float dt) override;

        HelloWorldScene* getGameWorld() const           { return _gameWorld; }
        void setGameWorld(HelloWorldScene* world)       { _gameWorld = world; }
        
        SteeringBehaviors* getSteering() const          { return _steering; }
        float getTimeElapsed() const                    { return _timeElapsed; }
        
    };
    
}