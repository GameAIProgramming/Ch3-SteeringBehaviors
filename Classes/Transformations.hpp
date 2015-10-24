//
//  Transformations.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 18..
//
//

#pragma once

#include <vector>

#include "Mat3.hpp"

namespace realtrick
{
    
    inline std::vector<cocos2d::Vec2> getWorldTransformedVectors(const std::vector<cocos2d::Vec2>& points, const cocos2d::Vec2& pos, const cocos2d::Vec2& heading, const cocos2d::Vec2& side, const cocos2d::Vec2& scale)
    {
        Mat3 transMat;
        
        if(scale.x != 1.0f || scale.y != 1.0f)
        {
            transMat.scale(scale);
        }
        transMat.rotate(heading, side);
        transMat.translate(pos);
        
        return transMat.getTransformedVector(points);
    }
    
    inline std::vector<cocos2d::Vec2> getWorldTransformedVectors(const std::vector<cocos2d::Vec2>& points, const cocos2d::Vec2& pos, const cocos2d::Vec2& heading, const cocos2d::Vec2& side)
    {
        Mat3 transMat;
        
        transMat.rotate(heading, side);
        transMat.translate(pos);
        
        return transMat.getTransformedVector(points);
    }
    
    inline cocos2d::Vec2 getWorldTransformedVector(const cocos2d::Vec2& point, const cocos2d::Vec2& heading, const cocos2d::Vec2& side, const cocos2d::Vec2& pos)
    {
        Mat3 transMat;
        
        transMat.rotate(heading, side);
        transMat.translate(pos);
        
        return transMat.getTransformedVector(point);
    }
    
    inline cocos2d::Vec2 getWorldTransformedVector(const cocos2d::Vec2& point, const cocos2d::Vec2& heading, const cocos2d::Vec2& side)
    {
        Mat3 transMat;
        
        transMat.rotate(heading, side);
        
        return transMat.getTransformedVector(point);
    }
    
    inline cocos2d::Vec2 getLocalSpaceVector(const cocos2d::Vec2& point, const cocos2d::Vec2& heading, const cocos2d::Vec2& side, const cocos2d::Vec2& pos)
    {
        Mat3 transMat;
        float x = -pos.dot(heading);
        float y = -pos.dot(side);
        
        transMat._11 = heading.x;       transMat._12 = side.x;
        transMat._21 = heading.y;       transMat._22 = side.y;
        transMat._31 = x;               transMat._32 = y;
        
        return transMat.getTransformedVector(point);
    }
    
    inline cocos2d::Vec2 getLocalSpaceVector(const cocos2d::Vec2& point, const cocos2d::Vec2& heading, const cocos2d::Vec2& side)
    {
        Mat3 transMat;
        
        transMat._11 = heading.x;       transMat._12 = side.x;
        transMat._21 = heading.y;       transMat._22 = side.y;
        
        return transMat.getTransformedVector(point);
    }
    
}











