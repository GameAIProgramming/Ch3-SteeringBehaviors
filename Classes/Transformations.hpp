//
//  Transformations.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 18..
//
//

#pragma once

#include <vector>

#include "Vector2.hpp"
#include "Mat3.hpp"

namespace realtrick
{
    
    inline std::vector<Vector2> getWorldTransformedVectors(const std::vector<Vector2>& points, const Vector2& pos, const Vector2& heading, const Vector2& side, const Vector2& scale)
    {
        Mat3 transMat;
        
        if(scale.x != 1.0 || scale.y != 1.0)
        {
            transMat.scale(scale);
        }
        transMat.rotate(heading, side);
        transMat.translate(pos);
        
        return transMat.getTransformedVector(points);
    }
    
    inline std::vector<Vector2> getWorldTransformedVectors(const std::vector<Vector2>& points, const Vector2& pos, const Vector2& heading, const Vector2& side)
    {
        Mat3 transMat;
        
        transMat.rotate(heading, side);
        transMat.translate(pos);
        
        return transMat.getTransformedVector(points);
    }
    
    inline Vector2 getWorldTransformedVector(const Vector2& point, const Vector2& heading, const Vector2& side, const Vector2& pos)
    {
        Mat3 transMat;
        
        transMat.rotate(heading, side);
        transMat.translate(pos);
        
        return transMat.getTransformedVector(point);
    }
    
    inline Vector2 getLocalSpaceVector(const Vector2& point, const Vector2& heading, const Vector2& side, const Vector2& pos)
    {
        Mat3 transMat;
        double x = -pos.dot(heading);
        double y = -pos.dot(side);
        
        transMat._11 = heading.x;       transMat._12 = side.x;
        transMat._21 = heading.y;       transMat._22 = side.y;
        transMat._31 = x;               transMat._32 = y;
        
        return transMat.getTransformedVector(point);
    }
    
}











