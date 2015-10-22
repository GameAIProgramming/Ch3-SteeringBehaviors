//
//  Vector2.inl
//  Ai002_SteeringBahavior
//
//  Created by 남준현 on 2015. 10. 15..
//
//

#include "Vector2.hpp"

namespace realtrick
{
    
    inline void Vector2::set(double xx, double yy)
    {
        x = xx;
        y = yy;
    }
    
    inline bool Vector2::isZero() const
    {
        return (x == 0.0 && y == 0.0);
    }
    
    inline bool Vector2::isOne() const
    {
        return (x == 1.0 && y == 1.0);
    }
    
    inline double Vector2::getDistanceSq(const Vector2& v) const
    {
        double dx = v.x - x;
        double dy = v.y - y;
        return (dx * dx + dy * dy);
    }
    
    inline double Vector2::dot(const Vector2& v) const
    {
        return (x * v.x + y * v.y);
    }
    
    inline double Vector2::getLengthSq() const
    {
        return (x * x + y * y);
    }
    
    inline void Vector2::negate()
    {
        x = -x;
        y = -y;
    }
    
    inline void Vector2::setZero()
    {
        x = y = 0.0;
    }
    
    inline const Vector2 Vector2::operator+(const Vector2& v) const
    {
        return Vector2(x + v.x, y + v.y);
    }
    
    
    inline Vector2& Vector2::operator+=(const Vector2& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
    
    inline const Vector2 Vector2::operator-(const Vector2& v) const
    {
        return Vector2(x - v.x, y - v.y);
    }
    
    inline Vector2& Vector2::operator-=(const Vector2& v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    
    inline const Vector2 Vector2::operator-() const
    {
        return Vector2(-x, -y);
    }
    
    inline const Vector2 Vector2::operator*(float s) const
    {
        return Vector2(x * s, y * s);
    }
    
    inline Vector2& Vector2::operator*=(float s)
    {
        x *= s;
        y *= s;
        return *this;
    }
    
    inline const Vector2 Vector2::operator/(float s) const
    {
        return Vector2(x / s, y / s);
    }
    
    inline bool Vector2::operator<(const Vector2& v) const
    {
        return (x < v.x && y < v.y);
    }
    
    inline bool Vector2::operator>(const Vector2& v) const
    {
        return (x > v.x && y > v.y);
    }
    
    inline bool Vector2::operator==(const Vector2& v) const
    {
        return (x == v.x && y == v.y);
    }
    
    inline bool Vector2::operator!=(const Vector2& v) const
    {
        return (x != v.x || y != v.y);
    }
    
}





