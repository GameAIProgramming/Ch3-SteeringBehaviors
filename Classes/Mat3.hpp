//
//  Mat3.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 18..
//
//

#pragma once

#include "Vector2.hpp"

namespace realtrick
{
    
    class Mat3
    {
        
    private:
        
        void _copy(const Mat3& copy);
        void _multiply(const Mat3& rhs);
        
    public:
        
        double _11, _12, _13;
        double _21, _22, _23;
        double _31, _32, _33;
        
        Mat3();
        Mat3(const Mat3& copy);
        Mat3& operator=(const Mat3& rhs);
        
        void identity();
        void scale(float scale);
        void scale(float xScale, float yScale);
        void scale(const Vector2& scale);
        void rotate(double sheta);
        void rotate(const Vector2& heading, const Vector2& side);
        void translate(const Vector2& trans);
        Vector2 getTransformedVector(const Vector2& v);
        
    };
    
    
}