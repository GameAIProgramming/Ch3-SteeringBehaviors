//
//  Mat3.cpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 18..
//
//

#include "Mat3.hpp"

namespace realtrick
{
    
    void Mat3::_copy(const Mat3& copy)
    {
        _11 = copy._11;         _12 = copy._12;         _13 = copy._13;
        _21 = copy._21;         _22 = copy._22;         _23 = copy._23;
        _31 = copy._31;         _32 = copy._32;         _33 = copy._33;
    }
    
    void Mat3::_multiply(const Mat3& rhs)
    {
        Mat3 temp(*this);
        _11 = (temp._11 * rhs._11) + (temp._12 * rhs._21) + (temp._13 * rhs._31);
        _12 = (temp._11 * rhs._12) + (temp._12 * rhs._22) + (temp._13 * rhs._32);
        _13 = (temp._11 * rhs._13) + (temp._12 * rhs._23) + (temp._13 * rhs._33);
        
        _21 = (temp._21 * rhs._11) + (temp._22 * rhs._21) + (temp._23 * rhs._31);
        _22 = (temp._21 * rhs._12) + (temp._22 * rhs._22) + (temp._23 * rhs._32);
        _23 = (temp._21 * rhs._13) + (temp._22 * rhs._23) + (temp._23 * rhs._33);

        _31 = (temp._31 * rhs._11) + (temp._32 * rhs._21) + (temp._33 * rhs._31);
        _32 = (temp._31 * rhs._12) + (temp._32 * rhs._22) + (temp._33 * rhs._32);
        _33 = (temp._31 * rhs._13) + (temp._32 * rhs._23) + (temp._33 * rhs._33);
    }
    
    Mat3::Mat3()
    {
        identity();
    }
    
    Mat3::Mat3(const Mat3& copy)
    {
        _copy(copy);
    }
    
    Mat3& Mat3::operator=(const Mat3& rhs)
    {
        if(this == &rhs)
            return *this;
        _copy(rhs);
        return *this;
    }
    
    void Mat3::identity()
    {
        _11 = 1.0;  _12 = 0.0;  _13 = 0.0;
        _21 = 0.0;  _22 = 1.0;  _23 = 0.0;
        _31 = 0.0;  _32 = 0.0;  _33 = 1.0;
    }
    
    void Mat3::scale(float scale)
    {
        Mat3 scaleMat;
        scaleMat._11 = scaleMat._22  = scale;
        _multiply(scaleMat);
    }
    
    void Mat3::scale(float xScale, float yScale)
    {
        Mat3 scaleMat;
        scaleMat._11 = xScale;
        scaleMat._22 = yScale;
        _multiply(scaleMat);
    }
    
    void Mat3::scale(const Vector2& scale)
    {
        Mat3 scaleMat;
        scaleMat._11 = scale.x;
        scaleMat._22 = scale.y;
        _multiply(scaleMat);
    }
    
    
    void Mat3::rotate(double sheta)
    {
        Mat3 rotateMat;
        rotateMat._11 = cos(sheta); rotateMat._12 = sin(sheta);
        rotateMat._21 = -sin(sheta); rotateMat._22 = cos(sheta);
        _multiply(rotateMat);
    }
    
    void Mat3::rotate(const Vector2& heading, const Vector2& side)
    {
        Mat3 rotateMat;
        rotateMat._11 = heading.x;      rotateMat._12 = heading.y;      rotateMat._13 = 0.0;
        rotateMat._21 = side.x;         rotateMat._22 = side.y;         rotateMat._23 = 0.0;
        rotateMat._31 = 0.0;            rotateMat._32 = 0.0;            rotateMat._33 = 1.0;
        _multiply(rotateMat);
    }
    
    void Mat3::translate(const Vector2& trans)
    {
        Mat3 transMat;
        transMat._31 = trans.x;
        transMat._32 = trans.y;
        _multiply(transMat);
    }
    
    Vector2 Mat3::getTransformedVector(const Vector2& v)
    {
        Vector2 ret;
        ret.x = (v.x * _11) + (v.y * _21) + _31;
        ret.y = (v.x * _12) + (v.y * _22) + _32;
        return ret;
    }

}








