//
//  SteeringBehaviors.cpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 17..
//
//

#include "SteeringBehaviors.hpp"
#include "Vehicle.hpp"
#include "HelloWorldScene.hpp"
#include "Geometry.hpp"
#include "Transformations.hpp"
#include "ParamLoader.hpp"

namespace realtrick
{
    
    //
    // Constructor
    //
    SteeringBehaviors::SteeringBehaviors(Vehicle* owner)
    {
        _vehicle = owner;
        _steeringForce = cocos2d::Vec2::ZERO;
        
        _targetEntity1 = nullptr;
        _targetEntity2 = nullptr;
        
        _target = cocos2d::Vec2::ZERO;
        _summingMethod = SummingMethod::kWeightedAverage;
        
        _flag = 0;
        
        _wanderDistance = Prm.getValueAsDouble("WanderDistance");
        _wanderJitter = Prm.getValueAsDouble("WanderJitter");
        _wanderRadius = Prm.getValueAsDouble("WanderRadius");
        
        _detectionBoxLength = Prm.getValueAsDouble("MinDetectionBoxLength");
        
        _weightSeek = Prm.getValueAsDouble("WeightSeek");
        _weightFlee = Prm.getValueAsDouble("WeightFlee");
        _weightArrive = Prm.getValueAsDouble("WeightArrive");
        _weightPursuit = Prm.getValueAsDouble("WeightPursuit");
        _weightWander = Prm.getValueAsDouble("WeightWander");
        _weightObstacleAvoidance = Prm.getValueAsDouble("WeightObstacleAvoidance");
        
        double theta = kTwoPi * randFloat(0.0f, 1.0f);
        _wanderTarget = cocos2d::Vec2(_wanderRadius * cos(theta), _wanderRadius * sin(theta));
        
        enableBehavior(BehaviorType::kFlee);
        //enableBehavior(BehaviorType::kSeek);
        //enableBehavior(BehaviorType::kArrive);
        enableBehavior(BehaviorType::kWander);
    }
    
    
    
    
    //
    // Calculate
    //
    cocos2d::Vec2 SteeringBehaviors::calculate()
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
                
                _steeringForce = cocos2d::Vec2::ZERO;
                
                break;
            }
        }
        
        return _steeringForce;
    }
    
    
    
    
    //
    // Seek
    //
    cocos2d::Vec2 SteeringBehaviors::_seek(const cocos2d::Vec2& targetPos)
    {
        cocos2d::Vec2 desiredVelocity = (targetPos - _vehicle->getPosition()).getNormalized() * _vehicle->getMaxSpeed();
        return (desiredVelocity - _vehicle->getVelocity());
    }
    
    
    
    
    //
    // Flee
    //
    cocos2d::Vec2 SteeringBehaviors::_flee(const cocos2d::Vec2& targetPos)
    {
        if((targetPos - _vehicle->getPosition()).getLengthSq() < 200.0f * 200.0f)
        {
            cocos2d::Vec2 desiredVelocity = (_vehicle->getPosition() - targetPos).getNormalized() * _vehicle->getMaxSpeed();
            return (desiredVelocity - _vehicle->getVelocity());
        }
        
        return cocos2d::Vec2::ZERO;
    }
    
    
    
    
    //
    // Arrive
    //
    cocos2d::Vec2 SteeringBehaviors::_arrive(const cocos2d::Vec2& targetPos, double deceleration)
    {
        cocos2d::Vec2 toTarget = targetPos - _vehicle->getPosition();
        double dist = toTarget.getLength();
        if(dist > 0.0)
        {
            const double decelerationTweaker = 0.3;
            double speed = dist / ((double)deceleration * decelerationTweaker);
            
            speed = std::min(speed, _vehicle->getMaxSpeed());
            cocos2d::Vec2 desiredVelocity = toTarget * speed / dist;
            
            return (desiredVelocity - _vehicle->getVelocity());
        }
        
        return cocos2d::Vec2::ZERO;
    }
    
    
    
    
    //
    // Pursuit
    //
    cocos2d::Vec2 SteeringBehaviors::_pursuit(const Vehicle* evader)
    {
        cocos2d::Vec2 toEvader = evader->getPosition() - _vehicle->getPosition();
        double relativeHeading = _vehicle->getHeading().dot(evader->getHeading());
        if((toEvader.dot(_vehicle->getHeading()) > 0.0) && relativeHeading < -0.95)
        {
            return _seek(evader->getPosition());
        }
        
        double lookAheadTime = toEvader.getLength() / (_vehicle->getMaxSpeed() + evader->getVelocity().getLength());
        return _seek(evader->getPosition() + evader->getVelocity() * lookAheadTime);
    }
    
    
    
    
    //
    // Wander
    //
    cocos2d::Vec2 SteeringBehaviors::_wander()
    {
        double jitterThisTimeSlice = _wanderJitter * _vehicle->getTimeElapsed();
        
        float r = randFloat(-1.0f, 1.0f);
        _wanderTarget += cocos2d::Vec2(r * jitterThisTimeSlice, r * jitterThisTimeSlice);
        _wanderTarget.normalize();
        _wanderTarget *= _wanderRadius;
        
        cocos2d::Vec2 targetLocal = _wanderTarget + cocos2d::Vec2(_wanderDistance, 0);
        cocos2d::Vec2 targetWorld = getWorldTransformedVector(targetLocal, _vehicle->getHeading(), _vehicle->getSide(), _vehicle->getPosition());
        
        return targetWorld - _vehicle->getPosition();
    }
    
    
    
    
    //
    // ObstacleAvoidance
    //
    cocos2d::Vec2 SteeringBehaviors::_obstacleAvoidance(const std::vector<BaseEntity*> obstacles)
    {
        _detectionBoxLength += (_vehicle->getSpeed()/ _vehicle->getMaxSpeed()) * _detectionBoxLength;
        return cocos2d::Vec2::ZERO;
    }
    
    
    
    
    
    
    //
    // CalculateWeightedSum
    //
    void SteeringBehaviors::_calculateWeightedSum()
    {
        HelloWorldScene* world = (HelloWorldScene*)_vehicle->getGameWorld();
        cocos2d::Sprite* crossHair = world->getCrossHair();
        cocos2d::Vec2 targetPos = cocos2d::Vec2(crossHair->getPosition().x, crossHair->getPosition().y);
        targetPos.x -= 20.0f;
        targetPos.y -= 20.0f;
        
        
        if(isOnBehavior(BehaviorType::kSeek))
        {
            _steeringForce += SteeringBehaviors::_seek(targetPos) * _weightSeek;
        }
        
        if(isOnBehavior(BehaviorType::kFlee))
        {
            _steeringForce += SteeringBehaviors::_flee(targetPos) * _weightFlee;
        }
        
        if(isOnBehavior(BehaviorType::kArrive))
        {
            _steeringForce += SteeringBehaviors::_arrive(targetPos, 3.0) * _weightArrive;
        }

        if(isOnBehavior(BehaviorType::kWander))
        {
            _steeringForce += _wander() * _weightWander;
            int d = 0;
            d++;
        }
    
    }
    
    
    
    
    //
    // CalculatePrioritized
    //
    void SteeringBehaviors::_calculatePrioritized()
    {
        
    }
    
    
    
    
    
    //
    // CalculatedDithered
    //
    void SteeringBehaviors::_calculatedDithered()
    {
        
    }
    
}







