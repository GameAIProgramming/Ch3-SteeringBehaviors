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
    
    Vehicle::Vehicle(cocos2d::Node* world, int id) : MovingEntity(id)
    {
        _gameWorld = world;
        _type = EntityType::kVehicle;
        _steering = new SteeringBehaviors(this);
    }
    
    Vehicle::Vehicle(cocos2d::Node* world, int id, const Vector2& pos, double radius) : MovingEntity(id, pos, radius)
    {
        _gameWorld = world;
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
        
        Vector2 oldPos = getPos();
        Vector2 steeringForce = _steering->calculate();
        Vector2 acceleration = steeringForce / getMass();
        
        _velocity += acceleration * dt;
        _velocity.truncate(_maxSpeed);
        _pos += _velocity * dt;
        
        if(_velocity.getLengthSq() > kMathEpsilonSq)
        {
            _heading = _velocity.getNormalized();
        }
        
        if(_pos.x > 600.0f) _pos.x = 1.0f;
        else if(_pos.x < 0.0f) _pos.x = 599.0f;
        
        if(_pos.y > 600.0f) _pos.y = 1.0f;
        else if(_pos.y < 0.0f) _pos.y = 599.0f;
        
    }
}