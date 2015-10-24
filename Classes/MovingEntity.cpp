//
//  MovingEntity.cpp
//  Ai002_SteeringBahavior
//
//  Created by 남준현 on 2015. 10. 16..
//
//

#include "MovingEntity.hpp"
#include "ParamLoader.hpp"
#include "cocos2d.h"

namespace realtrick
{

    MovingEntity::MovingEntity() :
        _velocity(cocos2d::Vec2::ZERO),
        _heading(cocos2d::Vec2::UNIT_Y),
        _side(_heading.getPerp()),
        _mass(Prm.getValueAsDouble("Mass")),
        _maxSpeed(Prm.getValueAsDouble("MaxSpeed")),
        _maxForce(Prm.getValueAsDouble("MaxForce")),
        _maxTurnRate(Prm.getValueAsDouble("MaxTurnRate"))
    {}

}