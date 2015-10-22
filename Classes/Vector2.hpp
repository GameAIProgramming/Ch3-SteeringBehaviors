//
//  Vector2.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 20..
//
//

#pragma once

#include "MathBase.hpp"

namespace realtrick
{
    
    class Vector2
    {
        
    public:
        
        double x, y;
        
        Vector2() : x(0.0), y(0.0)
        {}
        
        Vector2(double x, double y) : x(x), y(y)
        {}
        
        Vector2(const Vector2& rhs) : x(rhs.x), y(rhs.y)
        {}
        
        ~Vector2()
        {}
        
        Vector2& operator=(const Vector2& rhs)
        {
            if(&rhs == this)
                return *this;
            x = rhs.x;
            y = rhs.y;
            return *this;
        }
        
        inline bool isZero() const;
        
        inline bool isOne() const;
        
        inline void set(double xx, double yy);
        
        void clamp(const Vector2& min, const Vector2& max);
        
        void truncate(double max);
        
        double getDistance(const Vector2& v) const;
        
        inline double getDistanceSq(const Vector2& v) const;
        
        inline double dot(const Vector2& v) const;
        
        static double dot(const Vector2& v1, const Vector2& v2);
        
        double getLength() const;
        
        inline double getLengthSq() const;
        
        inline void negate();
        
        void normalize();
        
        Vector2 getNormalized() const;
        
        void rotate(const Vector2& pivot, float radian);
        
        inline void setZero();
        
        inline const Vector2 operator+(const Vector2& v) const;
        
        inline Vector2& operator+=(const Vector2& v);
        
        inline const Vector2 operator-(const Vector2& v) const;
        
        inline Vector2& operator-=(const Vector2& v);
        
        inline const Vector2 operator-() const;
        
        inline const Vector2 operator*(float s) const;
        
        inline Vector2& operator*=(float s);
        
        inline const Vector2 operator/(float s) const;
        
        inline bool operator<(const Vector2& v) const;
        
        inline bool operator>(const Vector2& v) const;
        
        inline bool operator==(const Vector2& v) const;
        
        inline bool operator!=(const Vector2& v) const;
        
        inline float getAngle() const { return atan2(y, x); }
        
        double getAngle(const Vector2& other) const;
        
        inline double cross(const Vector2& other) const { return x * other.y - y * other.x; }
        
        // rotated 90 degrees counter-clockwise
        inline Vector2 getPerp() const { return Vector2(-y, x); }
        
        // rotated 90 degrees clockwise
        inline Vector2 getRPerp() const { return Vector2(y, -x); }
        
        inline Vector2 getMidPoint(const Vector2& other) const { return Vector2((x + other.x) / 2.0, (y + other.y) / 2.0); }
        
        inline Vector2 project(const Vector2& other) const { return other * (dot(other) / other.dot(other)); }
        
        inline Vector2 lerp(const Vector2& other, float t) { return *this * (1.0f - t) + other * t; }
        
        static bool isLineIntersect(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D, double *T1 = nullptr, double *T2 = nullptr);
        static bool isLineOverlap(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D);
        static bool isLineParallel(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D);
        
        static bool isSegmentIntersect(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D, Vector2 *S = nullptr, Vector2 *E = nullptr);
        static bool isSegmentOverlap(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D);
        
        static Vector2 getIntersectPoint(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D);
        
        static const Vector2 kZero;
        static const Vector2 kOne;
        static const Vector2 kUnitX;
        static const Vector2 kUnitY;
        
    };
    
    
    
}


#include "Vector2.inl"





