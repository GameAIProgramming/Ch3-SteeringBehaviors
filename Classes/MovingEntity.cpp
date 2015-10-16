//
//  MovingEntity.cpp
//  Ai002_SteeringBahavior
//
//  Created by 남준현 on 2015. 10. 16..
//
//

#include "MovingEntity.hpp"

namespace realtrick
{

    MovingEntity::MovingEntity(int id) : BaseEntity(id),
        _velocity(Vector2::kZero),
        _heading(Vector2::kUnitY),
        _side(_heading.getPerp()),
        _mass(1.0),
        _maxSpeed(100.0),
        _maxForce(100.0),
        _maxTurnRate(30.0)
    {}
    
    MovingEntity::MovingEntity(int id, const Vector2& pos, double r) : BaseEntity(id, pos, r),
        _velocity(Vector2::kZero),
        _heading(Vector2::kUnitY),
        _side(_heading.getPerp()),
        _mass(1.0),
        _maxSpeed(100.0),
        _maxForce(100.0),
        _maxTurnRate(30.0)
    {}

}