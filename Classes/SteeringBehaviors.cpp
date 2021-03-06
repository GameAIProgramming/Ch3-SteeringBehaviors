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
#include "Obstacle.hpp"
#include "Wall2D.hpp"

#include <numeric>

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
        
        _wanderDistance = Prm.getValueAsFloat("WanderDistance");
        _wanderJitter = Prm.getValueAsFloat("WanderJitter");
        _wanderRadius = Prm.getValueAsFloat("WanderRadius");
        
        _detectionBoxLength = Prm.getValueAsFloat("MinDetectionBoxLength");
        
        _weightSeek = Prm.getValueAsFloat("WeightSeek");
        _weightFlee = Prm.getValueAsFloat("WeightFlee");
        _weightArrive = Prm.getValueAsFloat("WeightArrive");
        _weightPursuit = Prm.getValueAsFloat("WeightPursuit");
        _weightWander = Prm.getValueAsFloat("WeightWander");
        _weightObstacleAvoidance = Prm.getValueAsFloat("WeightObstacleAvoidance");
        _weightWallAvoidance = Prm.getValueAsFloat("WeightWallAvoidance");
        
        float theta = kTwoPi * cocos2d::random(0.0f, 1.0f);
        _wanderTarget = cocos2d::Vec2(_wanderRadius * cos(theta), _wanderRadius * sin(theta));
        
        _feelers.resize(3);
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
        
        cocos2d::Vec2 desiredVelocity =
        (targetPos - _vehicle->getPosition()).getNormalized() * _vehicle->getMaxSpeed();
        
        return (desiredVelocity - _vehicle->getVelocity());
        
        return cocos2d::Vec2::ZERO;
    }
    
    
    
    
    //
    // Flee
    //
    cocos2d::Vec2 SteeringBehaviors::_flee(const cocos2d::Vec2& targetPos)
    {
        if((targetPos - _vehicle->getPosition()).getLengthSq() < 200.0f * 200.0f)
        {
            cocos2d::Vec2 desiredVelocity =
            (_vehicle->getPosition() - targetPos).getNormalized() * _vehicle->getMaxSpeed();
            return (desiredVelocity - _vehicle->getVelocity());
        }
        
        return cocos2d::Vec2::ZERO;
    }
    
    
    
    
    //
    // Arrive
    //
    cocos2d::Vec2 SteeringBehaviors::_arrive(const cocos2d::Vec2& targetPos, float deceleration)
    {
        
        cocos2d::Vec2 toTarget = targetPos - _vehicle->getPosition();
        float dist = toTarget.getLength();
        if(dist > 5.0f)
        {
            float decelerationTweaker = 0.3f;
            float speed = dist / (deceleration * decelerationTweaker);
            speed = std::min(speed, _vehicle->getMaxSpeed());
            
            cocos2d::Vec2 desiredVelocity = toTarget * speed / dist;
            
            return (desiredVelocity - _vehicle->getVelocity());
        }
        
        _vehicle->setVelocity(cocos2d::Vec2::ZERO);
        return cocos2d::Vec2::ZERO;
        
        return cocos2d::Vec2::ZERO;
    }
    
    
    
    
    //
    // Pursuit
    //
    cocos2d::Vec2 SteeringBehaviors::_pursuit(const Vehicle* evader)
    {
        cocos2d::Vec2 toEvader = evader->getPosition() - _vehicle->getPosition();
        float relativeHeading = _vehicle->getHeading().dot(evader->getHeading());
        if((toEvader.dot(_vehicle->getHeading()) > 0.0) && relativeHeading < -0.95)
        {
            return _seek(evader->getPosition());
        }
        
        float lookAheadTime = toEvader.getLength() / ((_vehicle->getMaxSpeed() + evader->getVelocity().getLength()));
        return _seek(evader->getPosition() + evader->getVelocity() * lookAheadTime);
    }
    
    
    
    
    //
    // Wander
    //
    cocos2d::Vec2 SteeringBehaviors::_wander()
    {
        float jitterThisTimeSlice = _wanderJitter * _vehicle->getTimeElapsed();
        
        float r = cocos2d::random(-1.0f, 1.0f);
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
    cocos2d::Vec2 SteeringBehaviors::_obstacleAvoidance(const cocos2d::Vector<Obstacle*> obstacles)
    {
        cocos2d::DrawNode* localNode = _vehicle->getGameWorld()->getDetailNode();
        Vehicle* selectedVehicle = _vehicle->getGameWorld()->getSelectedVehicle();
        
        static const float detectionBoxLength = Prm.getValueAsFloat("MinDetectionBoxLength");
    
        _detectionBoxLength = detectionBoxLength + (_vehicle->getSpeed() / _vehicle->getMaxSpeed()) * detectionBoxLength;
        
        
        // local width   = 476.0f;
        // local height  = 600.0f;
        cocos2d::Vec2 localCenter = cocos2d::Vec2(238.0f, 300.0f);
        localNode->drawSegment(localCenter, localCenter + cocos2d::Vec2(_detectionBoxLength, 0.0f), 0.5f, cocos2d::Color4F::RED);
        
        _vehicle->getGameWorld()->tagObstaclesWithinViewRange(_vehicle, _detectionBoxLength);
        float closestDistance = std::numeric_limits<float>::max();
        Obstacle* closestObstacle = nullptr;
        cocos2d::Vec2 closestLocalPos = cocos2d::Vec2::ZERO;
        for(auto iter = obstacles.begin(); iter != obstacles.end(); ++iter)
        {
            if((*iter)->isFlagged())
            {
                cocos2d::Vec2 localPos = getLocalSpaceVector((*iter)->getPosition(),
                                                             _vehicle->getHeading(),
                                                             _vehicle->getSide(),
                                                             _vehicle->getPosition());
                
                if(localPos.x >= 0)
                {
                    float expandedRadius = (*iter)->getBRadius() + _vehicle->getBRadius();
                    if(expandedRadius > fabsf(localPos.y))
                    {
                        float cx = localPos.x;
                        float cy = localPos.y;
                        
                        // circle, line's intersection(because of local space, equation's y is zero)
                        // 1) (x-cx)^2 + (y-cy)^2 = r^2
                        // 2) input y to 0.
                        // 3) As a result, x is cx - sqrt(r^2 - cy^2) or cx + sqrt(r^2 - cy^2).
                        
                        float sqrtPart = sqrtf(expandedRadius * expandedRadius - cy * cy);
                        
                        float intersectPointX = cx - sqrtPart;
                        if(intersectPointX < 0.0f)
                        {
                            intersectPointX = cx + sqrtPart;
                        }
                        
                        if(closestDistance > intersectPointX)
                        {
                            closestDistance = intersectPointX;
                            closestLocalPos = localPos;
                            closestObstacle = *iter;
                        }
                        
                        if(selectedVehicle == _vehicle)
                        {
                            localNode->drawCircle(localCenter + cocos2d::Vec2(cx, cy),
                                                  (*iter)->getBRadius() + _vehicle->getBRadius(),
                                                  360.0f, 100, false, 1.0f, 1.0f, cocos2d::Color4F::ORANGE);
                        }
                    }
                }
            }
        }
        
        cocos2d::Vec2 steeringForce = cocos2d::Vec2::ZERO;
        
        if(closestObstacle)
        {
            float multiplier = 1.0f + (_detectionBoxLength - closestLocalPos.x) / _detectionBoxLength;
            steeringForce.y = (closestObstacle->getBRadius() - closestLocalPos.y) * multiplier;
            
            const float breakingWeight = 0.2f;
            steeringForce.x = (closestObstacle->getBRadius() - closestLocalPos.x) * breakingWeight;
        }
        
        return getWorldTransformedVector(steeringForce, _vehicle->getHeading(), _vehicle->getSide());
    }
    
    // 벽 피하기
    cocos2d::Vec2 SteeringBehaviors::_wallAvoidance(const cocos2d::Vector<Wall2D*>& walls)
    {
        createFeelers();
//        
//        cocos2d::DrawNode* node = _vehicle->getGameWorld()->getWorldNode();
//        node->drawSegment(_vehicle->getPosition(), _feelers[0], 0.5f, cocos2d::Color4F::RED);
//        node->drawSegment(_vehicle->getPosition(), _feelers[1], 0.5f, cocos2d::Color4F::RED);
//        node->drawSegment(_vehicle->getPosition(), _feelers[2], 0.5f, cocos2d::Color4F::RED);
        
        float distToThisIP = 0.0f;
        float distToClosestIP = std::numeric_limits<float>::max();
        
        int closestWall = -1;
        
        cocos2d::Vec2 steeringForce = cocos2d::Vec2::ZERO;
        cocos2d::Vec2 point = cocos2d::Vec2::ZERO;
        cocos2d::Vec2 closestPoint = cocos2d::Vec2::ZERO;

        for(unsigned int f = 0 ; f < _feelers.size() ; ++ f)
        {
            for(unsigned int w = 0 ; w < walls.size() ; ++ w)
            {
               if(physics::intersectGet(Segment(_vehicle->getPosition(), _feelers.at(f)),
                                        Segment(walls.at(w)->getStart(), walls.at(w)->getEnd()),
                                        distToThisIP,
                                        point))
               {
                   if(distToThisIP < distToClosestIP)
                   {
                       distToClosestIP = distToThisIP;
                       closestWall = w;
                       closestPoint = point;
                   }
               }
            } // next wall
            
            if( closestWall >= 0)
            {
                cocos2d::Vec2 overShoot = _feelers.at(f) - closestPoint;
                steeringForce = walls.at(closestWall)->getNormal() * overShoot.getLength();
            }
            
        } // next feeler
        
        //node->drawDot(closestPoint, 3.0f, cocos2d::Color4F::MAGENTA);
        
        return steeringForce;
    }
    
    
    
    
    //
    // CalculateWeightedSum
    //
    void SteeringBehaviors::_calculateWeightedSum()
    {
        cocos2d::Sprite* crossHair = _vehicle->getGameWorld()->getCrossHair();
        cocos2d::Vec2 targetPos = cocos2d::Vec2(crossHair->getPosition().x, crossHair->getPosition().y);
        targetPos.x -= 20.0f;
        targetPos.y -= 20.0f;
        
        Vehicle* selectedVehicle = _vehicle->getGameWorld()->getSelectedVehicle();
        
        if(isOnBehavior(BehaviorType::kSeek))
        {
            _steeringForce += SteeringBehaviors::_seek(targetPos) * _weightSeek;
        }
        
        if(isOnBehavior(BehaviorType::kFlee))
        {
            _steeringForce += SteeringBehaviors::_flee(selectedVehicle->getPosition()) * _weightFlee;
        }
        
        if(isOnBehavior(BehaviorType::kArrive))
        {
            _steeringForce += SteeringBehaviors::_arrive(targetPos, 3.0) * _weightArrive;
        }

        if(isOnBehavior(BehaviorType::kWander))
        {
            _steeringForce += _wander() * _weightWander;
        }
        
        if(isOnBehavior(BehaviorType::kObstacleAvoidance))
        {
            _steeringForce += _obstacleAvoidance(_vehicle->getGameWorld()->getObstacles()) * _weightObstacleAvoidance;
        }
        
        if(isOnBehavior(BehaviorType::kPursuit))
        {
            _steeringForce += _pursuit(selectedVehicle) * _weightPursuit;
        }
        
        if(isOnBehavior(BehaviorType::kWallAvoidance))
        {
            _steeringForce += _wallAvoidance(_vehicle->getGameWorld()->getWalls()) * _weightWallAvoidance;
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
    
    void SteeringBehaviors::createFeelers()
    {
        _feelers[0] = _vehicle->getPosition() + _detectionBoxLength * _vehicle->getHeading();
        
        Mat3 rotMat;
        rotMat.rotate(MATH_DEG_TO_RAD(-30.0f));
        cocos2d::Vec2 temp = rotMat.getTransformedVector(_vehicle->getHeading());
        _feelers[1] = _vehicle->getPosition() + _detectionBoxLength / 2.0f * temp;
        
        rotMat.identity();
        rotMat.rotate(MATH_DEG_TO_RAD(30.0f));
        temp = rotMat.getTransformedVector(_vehicle->getHeading());
        _feelers[2] = _vehicle->getPosition() + _detectionBoxLength / 2.0f * temp;
    }
    
}







