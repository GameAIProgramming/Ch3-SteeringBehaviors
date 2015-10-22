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
    
    
    
    //
    // Rect
    //
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
    
    float randFloat(float min, float max)
    {
        std::mt19937 re((unsigned int)time(nullptr));
        std::uniform_real_distribution<float> urd(min, max);
        return urd(re);
    }
    
    
    
    
    //
    // Circle
    //
    Circle::Circle()
    {
        setCircle(0.0, 0.0, 0.0);
    }
    
    Circle::Circle(double x, double y, double r)
    {
        setCircle(x, y, r);
    }
    
    Circle::Circle(const Vector2& center, double r)
    {
        setCircle(origin.x, origin.y, r);
    }
    
    Circle::Circle(const Circle& copy)
    {
        setCircle(copy.origin.x, copy.origin.y, copy.radius);
    }
    
    Circle& Circle::operator=(const Circle& rhs)
    {
        if(this == &rhs)
            return *this;
        setCircle(rhs.origin.x, rhs.origin.y, rhs.radius);
        return *this;
    }
    
    void Circle::setCircle(double x, double y, double r)
    {
        this->origin.x = x;
        this->origin.y = y;
        this->radius = r;
    }
    
    Circle Circle::getTranslatedCircle(const Vector2& dir, double distance)
    {
        return Circle(origin.x + dir.x * distance, origin.y + dir.y * distance, radius);
    }
    
    bool Circle::containPoint(const Vector2& point) const
    {
        return (origin.getDistanceSq(point) <= radius * radius);
    }
    
    
    
    
    //
    // Segment
    //
    Segment::Segment()
    {
        setSegment(0.0, 0.0, 0.0, 0.0);
    }
    
    Segment::Segment(double sx, double sy, double ex, double ey)
    {
        setSegment(sx, sy, ex, ey);
    }
    
    Segment::Segment(const Segment& copy)
    {
        setSegment(copy.start.x, copy.start.y, copy.end.x, copy.end.y);
    }
    
    Segment& Segment::operator=(const Segment& rhs)
    {
        if(this == &rhs)
            return *this;
        setSegment(rhs.start.x, rhs.start.y, rhs.end.x, rhs.end.y);
        return *this;
    }
    
    void Segment::setSegment(double sx, double sy, double ex, double ey)
    {
        this->start.x = sx;
        this->start.y = sy;
        this->end.x = ex;
        this->end.y = ey;
    }
    
    Vector2 Segment::getDirection() const
    {
        return (end - start).getNormalized();
    }
    
    double Segment::getDistance() const
    {
        return start.getDistance(end);
    }
    
    double Segment::getDistanceSq() const
    {
        return start.getDistanceSq(end);
    }
    
    // TODO 구현
    bool Segment::containPoint(const Vector2& point) const
    {
        return false;
    }
    
    
    
    
    //
    // Ray
    //
    Ray::Ray()
    {
        setRay(0.0, 0.0, 0.0, 0.0);
    }
    
    Ray::Ray(double sx, double sy, double dirX, double dirY)
    {
        setRay(sx, sy, dirX, dirY);
    }
    
    Ray::Ray(const Ray& copy)
    {
        setRay(copy.start.x, copy.start.x, copy.dir.x, copy.dir.y);
    }
    
    Ray& Ray::operator=(const Ray& rhs)
    {
        if(this == &rhs)
            return *this;
        setRay(rhs.start.x, rhs.start.y, rhs.dir.x, rhs.dir.y);
        return *this;
    }
    
    void Ray::setRay(double sx, double sy, double dirX, double dirY)
    {
        this->start.x = sx;
        this->start.y = sy;
        this->dir.x = dirX;
        this->dir.y = dirY;
    }
    
    // TODO 구현
    bool Ray::containPoint(const Vector2& point) const
    {
        return false;
    }
    
    
    
    
    
    
    //
    // Polygon
    //
    Polygon::Polygon()
    {}
    
    Polygon::Polygon(const std::vector<Segment> segs)
    {
        setPolygon(segs);
    }
    
    Polygon::Polygon(const Polygon& copy)
    {
        setPolygon(copy.segs);
    }
    
    Polygon& Polygon::operator=(const Polygon& rhs)
    {
        if(this == &rhs)
            return *this;
        setPolygon(rhs.segs);
        return *this;
        
    }
    
    void Polygon::setPolygon(const std::vector<Segment> segs)
    {
        this->segs = segs;
    }
    
    // TODO 구현
    bool Polygon::containPoint(const Vector2& point) const
    {
        return false;
    }
    
}















