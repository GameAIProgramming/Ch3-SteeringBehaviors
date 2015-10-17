//
//  Vector2.cpp
//  Ai002_SteeringBahavior
//
//  Created by 남준현 on 2015. 10. 15..
//
//

#include "Vector2.hpp"

namespace realtrick
{
    
    // returns true if segment A-B intersects with segment C-D. S->E is the ovderlap part
    bool isOneDimensionSegmentOverlap(double A, double B, double C, double D, double *S, double * E)
    {
        double ABmin = std::min(A, B);
        double ABmax = std::max(A, B);
        double CDmin = std::min(C, D);
        double CDmax = std::max(C, D);
        
        if (ABmax < CDmin || CDmax < ABmin)
        {
            // ABmin->ABmax->CDmin->CDmax or CDmin->CDmax->ABmin->ABmax
            return false;
        }
        else
        {
            if (ABmin >= CDmin && ABmin <= CDmax)
            {
                // CDmin->ABmin->CDmax->ABmax or CDmin->ABmin->ABmax->CDmax
                if (S != nullptr) *S = ABmin;
                if (E != nullptr) *E = CDmax < ABmax ? CDmax : ABmax;
            }
            else if (ABmax >= CDmin && ABmax <= CDmax)
            {
                // ABmin->CDmin->ABmax->CDmax
                if (S != nullptr) *S = CDmin;
                if (E != nullptr) *E = ABmax;
            }
            else
            {
                // ABmin->CDmin->CDmax->ABmax
                if (S != nullptr) *S = CDmin;
                if (E != nullptr) *E = CDmax;
            }
            return true;
        }
    }
    
    // cross product of 2 vector. A->B X C->D
    double crossProduct2Vector(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D)
    {
        // a b : B - A
        // c d : D - C
        // -> a * d - b * c
        return (B.x - A.x) * (D.y - C.y) - (B.y - A.y) * (D.x - C.x);
    }
    
    void Vector2::clamp(const Vector2& min, const Vector2& max)
    {
        if(x < min.x)
            x = min.x;
        if(x > max.x)
            x = max.x;
        
        if(y < min.y)
            y = min.y;
        if(y > max.y)
            y = max.y;
    }
    
    void Vector2::truncate(double max)
    {
        if(getLength() > max)
        {
            normalize();
            *this *= max;
        }
    }
    
    double Vector2::getDistance(const Vector2& v) const
    {
        double dx = v.x - x;
        double dy = v.y - y;
        return sqrt(dx * dx + dy * dy);
    }
    
    double Vector2::dot(const Vector2& v1, const Vector2& v2)
    {
        return (v1.x * v2.x + v1.y * v2.y);
    }
    
    double Vector2::getLength() const
    {
        return sqrt(x * x + y * y);
    }
    
    void Vector2::normalize()
    {
        double len = x * x + y * y;
        if(len == 1.0)
            return ;
        
        len = sqrt(len);
        // too close to zero.
        if(len < kMathTolerance)
            return ;
        
        len = 1.0 / len;
        x *= len;
        y *= len;
    }
    
    Vector2 Vector2::getNormalized() const
    {
        Vector2 v(*this);
        v.normalize();
        return v;
    }
    
    // TODO: "else { ... } 부분" 이해 필요
    void Vector2::rotate(const Vector2& pivot, float radian)
    {
        float sinAngle = sin(radian);
        float cosAngle = cos(radian);
        
        if( pivot.isZero())
        {
            double tempX = x;
            double tempY = y;
            
            x = tempX * cosAngle - tempY * sinAngle;
            y = tempX * sinAngle + tempY * cosAngle;
        }
        else
        {
            double tempX = x - pivot.x;
            double tempY = y - pivot.y;
            
            x = tempX * cosAngle - tempY * sinAngle + pivot.x;
            y = tempX * sinAngle + tempY * cosAngle + pivot.y;
        }
    }
    
    double Vector2::getAngle(const Vector2& other) const
    {
        Vector2 a2 = getNormalized();
        Vector2 b2 = other.getNormalized();
        return 0.0;
    }
    
    // TODO: 'denom 이하' 부터 이해하기.
    bool Vector2::isLineIntersect(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D, double *T1, double *T2)
    {
        if( (A.x == B.x && A.y == B.y) || (C.x == D.x && C.y == D.y))
            return false;
        
        const double denom = crossProduct2Vector(A, B, C, D);
        
        if (denom == 0)
        {
            return false;
        }
        if (T1 != nullptr) *T1 = crossProduct2Vector(C, D, C, A) / denom;
        if (T2 != nullptr) *T2 = crossProduct2Vector(A, B, C, A) / denom;
        
        return true;
    }
    
    bool Vector2::isLineOverlap(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D)
    {
        if( (A.x == B.x && A.y == B.y) || (C.x == D.x && C.y == D.y))
            return false;
        
        if (crossProduct2Vector(A, B, C, D) == 0 && (crossProduct2Vector(C, D, C, A) == 0 || crossProduct2Vector(A, B, C, A) == 0))
            return true;
        
        return false;
    }
    
    bool Vector2::isLineParallel(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D)
    {
        if ( (A.x==B.x && A.y==B.y) || (C.x==D.x && C.y==D.y) )
        {
            return false;
        }
        
        if (crossProduct2Vector(A, B, C, D) == 0)
        {
            // line overlap
            if (crossProduct2Vector(C, D, C, A) == 0 || crossProduct2Vector(A, B, C, A) == 0)
            {
                return false;
            }
            
            return true;
        }
        
        return false;
    }
    
    bool Vector2::isSegmentIntersect(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D, Vector2 *S, Vector2 *E)
    {
        if (isLineOverlap(A, B, C, D))
        {
            return isOneDimensionSegmentOverlap(A.x, B.x, C.x, D.x, &S->x, &E->x) &&
            isOneDimensionSegmentOverlap(A.y, B.y, C.y, D.y, &S->y, &E->y);
        }
        
        return false;
    }
    
    bool Vector2::isSegmentOverlap(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D)
    {
        double S, T;
        
        if (isLineIntersect(A, B, C, D, &S, &T )&&
            (S >= 0.0f && S <= 1.0f && T >= 0.0f && T <= 1.0f))
        {
            return true;
        }
        
        return false;
        
    }
    
    Vector2 Vector2::getIntersectPoint(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D)
    {
        double S, T;
        
        if (isLineIntersect(A, B, C, D, &S, &T))
        {
            // Vector2 of intersection
            Vector2 P;
            P.x = A.x + S * (B.x - A.x);
            P.y = A.y + S * (B.y - A.y);
            return P;
        }
        
        return Vector2::kZero;
    }
    
    
    const Vector2 Vector2::kZero = Vector2(0.0, 0.0);
    const Vector2 Vector2::kOne = Vector2(1.0, 1.0);
    const Vector2 Vector2::kUnitX = Vector2(1.0, 0.0);
    const Vector2 Vector2::kUnitY = Vector2(0.0, 1.0);
    
    
    
}






