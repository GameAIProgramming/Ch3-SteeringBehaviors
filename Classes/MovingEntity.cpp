//
//  MovingEntity.cpp
//  Ai002_SteeringBahavior
//
//  Created by 남준현 on 2015. 10. 16..
//
//

#include "MovingEntity.hpp"
#include "ParamLoader.hpp"

namespace realtrick
{

    MovingEntity::MovingEntity(int id) : BaseEntity(id),
        _velocity(Vector2::kZero),
        _heading(Vector2::kUnitY),
        _side(_heading.getPerp()),
        _mass(Prm.getValueAsDouble("Mass")),
        _maxSpeed(Prm.getValueAsDouble("MaxSpeed")),
        _maxForce(Prm.getValueAsDouble("MaxForce")),
        _maxTurnRate(Prm.getValueAsDouble("MaxTurnRate"))
    {}
    
    MovingEntity::MovingEntity(int id, const Vector2& pos, double r) : BaseEntity(id, pos, r),
        _velocity(Vector2::kZero),
        _heading(Vector2::kUnitY),
        _side(_heading.getPerp()),
        _mass(Prm.getValueAsDouble("Mass")),
        _maxSpeed(Prm.getValueAsDouble("MaxSpeed")),
        _maxForce(Prm.getValueAsDouble("MaxForce")),
        _maxTurnRate(Prm.getValueAsDouble("MaxTurnRate"))
    {}

}