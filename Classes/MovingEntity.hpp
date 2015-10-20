//
//  MovingEntity.hpp
//  Ai002_SteeringBahavior
//
//  Created by 남준현 on 2015. 10. 16..
//
//

#pragma once

#include "BaseEntity.hpp"

namespace realtrick
{
    
    class Telegram;

    class MovingEntity : public BaseEntity
    {
    
    private:
        
        MovingEntity() = delete;
        MovingEntity(const MovingEntity&) = delete;
        MovingEntity& operator=(const MovingEntity&) = delete;
        
    protected:
    
        Vector2             _velocity;
        Vector2             _heading;
        Vector2             _side;
    
        double              _mass;
        double              _maxSpeed;
        double              _maxForce;
        double              _maxTurnRate;
    
    public:
    
        MovingEntity(int id);
        MovingEntity(int id, const Vector2& pos, double r);
    
        virtual ~MovingEntity()
        {}
    
        Vector2 getVelocity() const                         { return _velocity; }
        void setVelocity(const Vector2& velocity)           { _velocity = velocity; }

        Vector2 getHeading() const                          { return _heading; }
        inline void setHeading(const Vector2& heading);
        
        Vector2 getSide() const                             { return _side; }
        
        double getMass() const                              { return _mass; }
        void setMass(double mass)                           { _mass = mass; }
        
        double getMaxSpeed() const                          { return _maxSpeed; }
        void setMaxSpeed(double maxSpeed)                   { _maxSpeed = maxSpeed; }
        
        double getMaxForce() const                          { return _maxForce; }
        void setMaxForce(double maxForce)                   { _maxForce = maxForce; }
        
        double getMaxTurnRate() const                       { return _maxTurnRate; }
        void setMaxTurnRate(double maxTurnRate)             { _maxTurnRate = maxTurnRate; }
        
        virtual bool handleMessage(const Telegram& msg) override { return false; }
        virtual void update(float dt) override {}
    
    };
    
    inline void MovingEntity::setHeading(const Vector2& heading)
    {
        // TODO: try and catch exception.
        if(heading.getLengthSq() < kMathEpsilon) return ;
        
        _heading = heading;
        _heading.normalize();
        _side = _heading.getPerp();
    }

}







