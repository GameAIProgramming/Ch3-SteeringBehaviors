//
//  Wall2D.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 25..
//
//

#pragma once

#include "BaseEntity.hpp"
#include "Geometry.hpp"

#include "cocos2d.h"


namespace realtrick
{
    
    class Wall2D : public BaseEntity
    {
        
    private:
        
        cocos2d::DrawNode*      _node;
        
    protected:
        
        Segment                 _seg;
        cocos2d::Vec2           _normal;
        
        void _calculateNormal();
        Wall2D(const Segment& seg);
        
    public:
        
        static Wall2D* create(const Segment& seg);
        
        Segment getSegment() const              { return _seg; }
        cocos2d::Vec2 getNormal() const         { return _normal; }
        
        cocos2d::Vec2 getStart() const           { return _seg.start; }
        cocos2d::Vec2 getEnd() const             { return _seg.end; }
        
        void setSegment(const Segment& seg);
        
        virtual void update(float dt) {}
        virtual bool handleMessage(const Telegram& msg) { return false; }
        
    };
    
}