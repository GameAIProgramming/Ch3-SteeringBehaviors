//
//  Geometry.cpp
//  Ai002_SteeringBahavior
//
//  Created by 남준현 on 2015. 10. 16..
//
//

#include "Geometry.hpp"

namespace realtrick
{
    
    Rect::Rect()
    {
        setRect(0.0, 0.0, 0.0, 0.0);
    }
    
    Rect::Rect(double x, double y, double width, double height)
    {
        setRect(x, y, width, height);
    }
    
    Rect::Rect(const Vector2& pos, double width, double height)
    {
        setRect(pos.x, pos.y, width, height);
    }
    
    Rect::Rect(const Rect& copy)
    {
        setRect(copy.origin.x, copy.origin.y, copy.width, copy.height);
    }
    
    Rect& Rect::operator=(const Rect& rhs)
    {
        if(&rhs == this)
            return *this;
        setRect(rhs.origin.x, rhs.origin.y, rhs.width, rhs.height);
        return *this;
    }
    
    void Rect::setRect(double x, double y, double width, double height)
    {
        origin.x = x;
        origin.y = y;
        this->width = width;
        this->height = height;
    }
    
    double Rect::getMinX() const
    {
        return origin.x;
    }
    
    double Rect::getMidX() const
    {
        return origin.x + width / 2.0;
    }
    
    double Rect::getMaxX() const
    {
        return origin.x + width;
    }
    
    double Rect::getMinY() const
    {
        return origin.y;
    }
    
    double Rect::getMidY() const
    {
        return origin.y + height / 2.0;
    }
    
    double Rect::getMaxY() const
    {
        return origin.y + height;
    }
    
    bool Rect::equals(const Rect& rect) const
    {
        return (origin == rect.origin && width == rect.width && height == rect.height);
    }
    
    bool Rect::containPoint(const Vector2& point) const
    {
        return (point.x >= getMinX() && point.x <= getMaxX() && point.y >= getMinY() && point.y <= getMaxY());
    }
    
    bool Rect::intersectsRect(const Rect& rect) const
    {
        return !(getMaxX() < rect.getMinX() || rect.getMaxX() < getMinX() || getMaxY() < rect.getMinY() || rect.getMaxY() < getMinY());
    }
    
    bool Rect::intersectsCircle(const Vector2& center, double radius) const
    {
        Vector2 rectangleCenter((origin.x + width / 2),
                                (origin.y + height / 2));
        
        float w = width / 2;
        float h = height / 2;
        
        float dx = fabs(center.x - rectangleCenter.x);
        float dy = fabs(center.y - rectangleCenter.y);
        
        if (dx > (radius + w) || dy > (radius + h))
        {
            return false;
        }
        
        Vector2 circleDistance(fabs(center.x - origin.x - w),
                               fabs(center.y - origin.y - h));
        
        if (circleDistance.x <= (w))
        {
            return true;
        }
        
        if (circleDistance.y <= (h))
        {
            return true;
        }
        
        float cornerDistanceSq = powf(circleDistance.x - w, 2) + powf(circleDistance.y - h, 2);
        
        return (cornerDistanceSq <= (powf(radius, 2)));
    }
    
    Rect Rect::getMergedRect(const Rect& rect) const
    {
        double minX = std::min(getMinX(), rect.getMinX());
        double minY = std::min(getMinY(), rect.getMinY());
        double maxX = std::max(getMaxX(), rect.getMaxX());
        double maxY = std::max(getMaxY(), rect.getMaxY());
        
        return Rect(Vector2(minX, minY), maxX - minX, maxY - minY);
    }
    
    void Rect::merge(const Rect& rect)
    {
        double minX = std::min(getMinX(), rect.getMinX());
        double minY = std::min(getMinY(), rect.getMinY());
        double maxX = std::max(getMaxX(), rect.getMaxX());
        double maxY = std::max(getMaxY(), rect.getMaxY());
        
        setRect(minX, minY, maxX - minX, maxY - minY);
    }
    
    const Rect Rect::kZero = Rect(0.0, 0.0, 0.0, 0.0);
    
}








