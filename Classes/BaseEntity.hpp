//
//  BaseEntity.hpp
//  Ai001_StateMachine
//
//  Created by 남준현 on 2015. 9. 24..
//
//

#pragma once

#include "Vector2.hpp"

namespace realtrick
{
    class Telegram;

    enum class EntityType
    {
        kDefault,
        kVehicle
    };
    
    class BaseEntity
    {
     
    private:
    
        BaseEntity() = delete;
        BaseEntity(const BaseEntity&) = delete;
        BaseEntity& operator=(const BaseEntity&) = delete;
        
    protected:
    
        int             _id;
        Vector2         _pos;
        Vector2         _scale;
        double          _BRadius;
        EntityType      _type;
    
    public:
        
        BaseEntity(int id) : _type(EntityType::kDefault), _id(id), _pos(Vector2::kZero), _scale(Vector2::kOne), _BRadius(15.0)
        {}
    
        BaseEntity(int id, const Vector2& pos, double r) : _type(EntityType::kDefault), _id(id), _pos(pos), _BRadius(r)
        {}
    
        virtual ~BaseEntity()
        {}
    
        int getID() const						{ return _id; }
        Vector2 getPos() const                  { return _pos; }
        Vector2 getScale() const                { return _scale; }
        double getBRadius() const               { return _BRadius; }
        EntityType getEntType() const           { return _type; }
        
        void setPos(const Vector2& pos)         { _pos = pos; }
        void setScale(const Vector2& scale)     { _scale = scale; }
        void setBRadius(double r)               { _BRadius = r; }
        
        virtual bool handleMessage(const Telegram& msg) = 0;
        virtual void update(float dt) = 0;
    
    };

}