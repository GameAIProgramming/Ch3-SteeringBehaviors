//
//  BaseEntity.hpp
//  Ai001_StateMachine
//
//  Created by 남준현 on 2015. 9. 24..
//
//

#pragma once

#include "Vector2.hpp"
#include "cocos2d.h"

namespace realtrick
{
    class Telegram;

    enum class EntityType : int
    {
        kDefault,
        kVehicle,
        kObstacle
    };
    
    class BaseEntity : public cocos2d::Sprite
    {
        
    protected:
    
        float           _BRadius;
        EntityType      _type;
        bool            _flag;
    
    public:
        
        BaseEntity() : _type(EntityType::kDefault), _BRadius(15.0f), _flag(false)
        {}
    
        virtual ~BaseEntity()
        {}
    
        float       getBRadius() const              { return _BRadius; }
        EntityType  getEntType() const              { return _type; }
        bool        isFlagged() const               { return _flag; }
        
        void setBRadius(float r)                    { _BRadius = r; }
        void setEntityType(EntityType type)         { _type = type; }
        void setFlag(bool flag)                     { _flag = flag; }
        
        virtual bool handleMessage(const Telegram& msg) = 0;
        virtual void update(float dt) = 0;
    
    };

}