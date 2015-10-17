//
//  SteeringBehaviors.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 17..
//
//

#pragma once

#include "Vector2.hpp"

namespace realtrick
{
    
    class Vehicle;
    
    class SteeringBehaviors
    {
        
    private:
        
        enum class BehaviorType : int
        {
            kNone               = 0x00000,
            kSeek               = 0x00002,
            kFlee               = 0x00004,
            kArrive             = 0x00008,
            kWander             = 0x00010,
            kCohesion           = 0x00020,
            kSeparation         = 0x00040,
            kAllignment         = 0x00080,
            kObstacleAvoidance  = 0x00100,
            kAallAvoidance      = 0x00200,
            kFollowPath         = 0x00400,
            kPursuit            = 0x00800,
            kEvade              = 0x01000,
            kInterpose          = 0x02000,
            kHide               = 0x04000,
            kFlock              = 0x08000,
            kOffsetPursuit      = 0x10000
        };
        
    private:
        
        Vehicle*                _vehicle;
        Vector2                 _steeringForce;
        
        Vehicle*                _targetEntity1;
        Vehicle*                _targetEntity2;
        
        Vector2                 _target;
        
        Vector2 _seek(const Vector2& targetPos);
        Vector2 _flee(const Vector2& targetPos);
        Vector2 _arrive(const Vector2& targetPos, double deceleration);
        
    public:
        
        SteeringBehaviors(Vehicle* owner);
        SteeringBehaviors(const SteeringBehaviors&) = delete;
        SteeringBehaviors& operator=(const SteeringBehaviors&) = delete;
        
        Vector2 calculate();
        
    };
    
}








