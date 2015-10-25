//
//  Wall2D.cpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 25..
//
//

#include "Wall2D.hpp"

namespace realtrick
{
    
    Wall2D::Wall2D(const Segment& seg)
    {
        setSegment(seg);
        _node = cocos2d::DrawNode::create();
        _node->drawSegment(seg.start, seg.end, 0.5f, cocos2d::Color4F::BLUE);
        addChild(_node);
    }
    
    Wall2D* Wall2D::create(const Segment& seg)
    {
        Wall2D *pRet = new(std::nothrow) Wall2D(seg);
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
    
    void Wall2D::setSegment(const Segment& seg)
    {
        _seg.setSegment(seg.start.x, seg.start.y, seg.end.x, seg.end.y);
        _calculateNormal();
    }
    
    void Wall2D::_calculateNormal()
    {
        cocos2d::Vec2 temp = (_seg.end - _seg.start).getNormalized();
        _normal = temp.getPerp();
    }
    
}