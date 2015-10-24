//
//  Vehicle.cpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 17..
//
//

#include "Vehicle.hpp"

namespace realtrick
{
    Vehicle* Vehicle::create(const std::string& fileName)
    {
        Vehicle *pRet = new(std::nothrow) Vehicle();
        if (pRet && pRet->initWithFile(fileName))
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
    
    Vehicle::Vehicle() : MovingEntity()
    {
        _type = EntityType::kVehicle;
        _steering = new SteeringBehaviors(this);
    }
    
    bool Vehicle::handleMessage(const Telegram& msg)
    {
        return false;
    }
    
    void Vehicle::update(float dt)
    {
        _timeElapsed = dt;
        
        cocos2d::Vec2 oldPos = getPosition();
        cocos2d::Vec2 steeringForce = _steering->calculate();
        cocos2d::Vec2 acceleration = steeringForce / getMass();
        
        _velocity += acceleration * dt;
        //_velocity.truncate(_maxSpeed);
        if(_velocity.getLengthSq() > _maxSpeed * _maxSpeed)
        {
            _velocity.normalize();
            _velocity *= _maxSpeed;
        }
        setPosition(getPosition() + _velocity * dt);
        
        if(_velocity.getLengthSq() > kMathEpsilonSq)
        {
            _heading = _velocity.getNormalized();
        }
        
        if(getPosition().x > 600.0f) setPosition(1.0f, getPosition().y);
        else if(getPosition().x < 0.0f) setPosition(599.0f, getPosition().y);
        
        if(getPosition().y > 600.0f) setPosition(getPosition().x, 1.0f);
        else if(getPosition().y < 0.0f) setPosition(getPosition().x, 599.0f);
    }
}



