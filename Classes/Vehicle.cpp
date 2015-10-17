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
    
    Vehicle::Vehicle(int id) : MovingEntity(id)
    {
        _type = EntityType::kVehicle;
    }
    
    Vehicle::Vehicle(int id, const Vector2& pos, double radius) : MovingEntity(id, pos, radius)
    {
        
    }
    
    bool Vehicle::handleMessage(const Telegram& msg)
    {
        return false;
    }
    
    void Vehicle::update(float dt)
    {
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
    }
}