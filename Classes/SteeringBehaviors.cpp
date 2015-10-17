//
//  SteeringBehaviors.cpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 17..
//
//

#include "SteeringBehaviors.hpp"
#include "Vehicle.hpp"
#include "HelloWorldScene.h"

namespace realtrick
{
    
    SteeringBehaviors::SteeringBehaviors(Vehicle* owner)
    {
        _vehicle = owner;
        _steeringForce = Vector2::kZero;
        
        _targetEntity1 = nullptr;
        _targetEntity2 = nullptr;
        
        _target = Vector2::kZero;
        _summingMethod = SummingMethod::kWeightedAverage;
        
        _flag = 0;
        
        enableBehavior(BehaviorType::kSeek);

    }
    
    Vector2 SteeringBehaviors::calculate()
    {
        _steeringForce.setZero();
        
        switch (_summingMethod)
        {
            case SummingMethod::kWeightedAverage:
            {
                
                _calculateWeightedSum();
                
                break;
            }
            case SummingMethod::kPrioritized:
            {
                
                _calculatePrioritized();
                
                break;
            }
            case SummingMethod::kDithered:
            {
                
                _calculatedDithered();
                
                break;
            }
            default:
            {
                
                _steeringForce = Vector2::kZero;
                
                break;
            }
        }
        
        return _steeringForce;
    }
    
    Vector2 SteeringBehaviors::_seek(const Vector2& targetPos)
    {
        Vector2 desiredVelocity = (targetPos - _vehicle->getPos()).getNormalized() * _vehicle->getMaxSpeed();
        
        return (desiredVelocity - _vehicle->getVelocity());
    }
    
    Vector2 SteeringBehaviors::_flee(const Vector2& targetPos)
    {
        return Vector2::kZero;
    }
    
    Vector2 SteeringBehaviors::_arrive(const Vector2& targetPos, double deceleration)
    {
        return Vector2::kZero;
    }
    
    void SteeringBehaviors::_calculateWeightedSum()
    {
        if(isOnBehavior(BehaviorType::kSeek))
        {
            HelloWorldScene* world = (HelloWorldScene*)_vehicle->getGameWorld();
            cocos2d::Sprite* crossHair = world->getCrossHair();
            _steeringForce += SteeringBehaviors::_seek(Vector2(crossHair->getPosition().x, crossHair->getPosition().y)) * _weightSeek;
        }

    }
    
    void SteeringBehaviors::_calculatePrioritized()
    {
    }
    
    void SteeringBehaviors::_calculatedDithered()
    {
    }
    
}







