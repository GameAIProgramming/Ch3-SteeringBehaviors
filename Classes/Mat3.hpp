//
//  Mat3.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 18..
//
//

#pragma once

#include <vector>
#include "cocos2d.h"

namespace realtrick
{
    
    class Mat3
    {
        
    private:
        
        void _copy(const Mat3& copy);
        void _multiply(const Mat3& rhs);
        
    public:
        
        float _11, _12, _13;
        float _21, _22, _23;
        float _31, _32, _33;
        
        Mat3();
        Mat3(const Mat3& copy);
        Mat3& operator=(const Mat3& rhs);
        
        void identity();
        void scale(float scale);
        void scale(float xScale, float yScale);
        void scale(const cocos2d::Vec2& scale);
        void rotate(float sheta);
        void rotate(const cocos2d::Vec2& heading, const cocos2d::Vec2& side);
        void translate(const cocos2d::Vec2& trans);
        cocos2d::Vec2 getTransformedVector(const cocos2d::Vec2& v);
        std::vector<cocos2d::Vec2> getTransformedVector(std::vector<cocos2d::Vec2> v);
    };
    
    
}