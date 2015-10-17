//
//  SteeringBehaviors.cpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 17..
//
//

#include "SteeringBehaviors.hpp"

#include "Vehicle.hpp"

namespace realtrick
{
    
    SteeringBehaviors::SteeringBehaviors(Vehicle* owner)
    {
        _vehicle = owner;
        _steeringForce = Vector2::kZero;
        
        _targetEntity1 = nullptr;
        _targetEntity2 = nullptr;
        
        _target = Vector2::kZero;
    }
    
    Vector2 SteeringBehaviors::calculate()
    {
        return Vector2::kZero;
    }
    
    Vector2 SteeringBehaviors::_seek(const Vector2& targetPos)
    {
        return Vector2::kZero;
    }
    
    Vector2 SteeringBehaviors::_flee(const Vector2& targetPos)
    {
        return Vector2::kZero;
    }
    
    Vector2 SteeringBehaviors::_arrive(const Vector2& targetPos, double deceleration)
    {
        return Vector2::kZero;
    }
    
}