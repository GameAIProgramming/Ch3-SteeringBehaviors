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
#include "Geometry.hpp"

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
        
        _wanderDistance = 2.0;
        _wanderJitter = 80.0;
        _wanderRadius = 1.2;
        
        
        double theta = kTwoPi * randFloat(0.0f, 1.0f);
    
        _wanderTarget = Vector2(_wanderRadius * cos(theta), _wanderRadius * sin(theta));
        
        //enableBehavior(BehaviorType::kFlee);
        //enableBehavior(BehaviorType::kSeek);
        enableBehavior(BehaviorType::kArrive);
    }
    
    
    
    //
    // Calculate
    //
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
    
    
    
    //
    // Seek
    //
    Vector2 SteeringBehaviors::_seek(const Vector2& targetPos)
    {
        Vector2 desiredVelocity = (targetPos - _vehicle->getPos()).getNormalized() * _vehicle->getMaxSpeed();
        return (desiredVelocity - _vehicle->getVelocity());
    }
    
    
    
    //
    // Flee
    //
    Vector2 SteeringBehaviors::_flee(const Vector2& targetPos)
    {
        Vector2 desiredVelocity = (_vehicle->getPos() - targetPos).getNormalized() * _vehicle->getMaxSpeed();
        return (desiredVelocity - _vehicle->getVelocity());
    }
    
    
    
    //
    // Arrive
    //
    Vector2 SteeringBehaviors::_arrive(const Vector2& targetPos, double deceleration)
    {
        Vector2 toTarget = targetPos - _vehicle->getPos();
        double dist = toTarget.getLength();
        if(dist > 0.0)
        {
            const double decelerationTweaker = 0.3;
            double speed = dist / ((double)deceleration * decelerationTweaker);
            
            speed = std::min(speed, _vehicle->getMaxSpeed());
            Vector2 desiredVelocity = toTarget * speed / dist;
            
            return (desiredVelocity - _vehicle->getVelocity());
        }
        
        return Vector2::kZero;
    }
    
    
    
    //
    // Pursuit
    //
    Vector2 SteeringBehaviors::_pursuit(const Vehicle* evader)
    {
        Vector2 toEvader = evader->getPos() - _vehicle->getPos();
        double relativeHeading = _vehicle->getHeading().dot(evader->getHeading());
        if((toEvader.dot(_vehicle->getHeading()) > 0.0) && relativeHeading < -0.95)
        {
            return _seek(evader->getPos());
        }
        
        double lookAheadTime = toEvader.getLength() / (_vehicle->getMaxSpeed() + evader->getVelocity().getLength());
        return _seek(evader->getPos() + evader->getVelocity() * lookAheadTime);
    }
    
    
    
    //
    // Wander
    //
    Vector2 SteeringBehaviors::_wander()
    {
        double jitterThisTimeSlice = _wanderJitter * _vehicle->getTimeElapsed();
        
        _wanderTarget += Vector2(randFloat(-1.0f, 1.0f) * jitterThisTimeSlice, randFloat(-1.0f, 1.0f) * jitterThisTimeSlice);
        
        _wanderTarget.normalize();
        
        _wanderTarget *= _wanderRadius;
        
        Vector2 target = _wanderTarget + Vector2(_wanderDistance, 0);
    
        // transform local to world.
        
        return Vector2::kZero;
    }
    
    void SteeringBehaviors::_calculateWeightedSum()
    {
        HelloWorldScene* world = (HelloWorldScene*)_vehicle->getGameWorld();
        cocos2d::Sprite* crossHair = world->getCrossHair();
        
        if(isOnBehavior(BehaviorType::kSeek))
        {
            _steeringForce += SteeringBehaviors::_seek(Vector2(crossHair->getPosition().x, crossHair->getPosition().y)) * _weightSeek;
        }
        
        if(isOnBehavior(BehaviorType::kFlee))
        {
            _steeringForce += SteeringBehaviors::_flee(Vector2(crossHair->getPosition().x, crossHair->getPosition().y)) * _weightFlee;
        }
        
        if(isOnBehavior(BehaviorType::kArrive))
        {
            _steeringForce += SteeringBehaviors::_arrive(Vector2(crossHair->getPosition().x, crossHair->getPosition().y), 3.0) * _weightArrive;
        }

        if(isOnBehavior(BehaviorType::kWander))
        {
            _steeringForce += _wander() * _weightWander;
        }
        
    }
    
    void SteeringBehaviors::_calculatePrioritized()
    {
        
    }
    
    void SteeringBehaviors::_calculatedDithered()
    {
        
    }
    
}







