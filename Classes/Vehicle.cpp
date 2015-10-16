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
        
    }
}