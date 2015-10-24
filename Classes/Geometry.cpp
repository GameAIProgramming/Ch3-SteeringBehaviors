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
    
    Rect::Rect(const cocos2d::Vec2& pos, double width, double height)
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
    
    bool Rect::containPoint(const cocos2d::Vec2& point) const
    {
        return (point.x >= getMinX() && point.x <= getMaxX() && point.y >= getMinY() && point.y <= getMaxY());
    }
    
    const Rect Rect::kZero = Rect(0.0, 0.0, 0.0, 0.0);
    
    
    
    
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
    
    Circle::Circle(const cocos2d::Vec2& center, double r)
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
    
    Circle Circle::getTranslatedCircle(const cocos2d::Vec2& dir, double distance)
    {
        return Circle(origin.x + dir.x * distance, origin.y + dir.y * distance, radius);
    }
    
    bool Circle::containPoint(const cocos2d::Vec2& point) const
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
    
    Segment::Segment(const cocos2d::Vec2& start, const cocos2d::Vec2& end)
    {
        setSegment(start.x, start.y, end.x, end.y);
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
    
    cocos2d::Vec2 Segment::getDirection() const
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
    bool Segment::containPoint(const cocos2d::Vec2& point) const
    {
        return false;
    }
    
    
    
    //
    // Polygon
    //
    Polygon::Polygon()
    {}
    
    Polygon::Polygon(const std::vector<cocos2d::Vec2>& segs)
    {
        setPolygon(segs);
    }
    
    Polygon::Polygon(const Polygon& copy)
    {
        setPolygon(copy.vertices);
    }
    
    Polygon& Polygon::operator=(const Polygon& rhs)
    {
        if(this == &rhs)
            return *this;
        setPolygon(rhs.vertices);
        return *this;
        
    }
    
    void Polygon::setPolygon(const std::vector<cocos2d::Vec2>& segs)
    {
        this->vertices.clear();
        
        for(std::vector<cocos2d::Vec2>::size_type i = 0 ; i < segs.size() ; ++ i)
        {
            this->vertices.push_back(segs.at(i));
        }
    }
    
    void Polygon::pushVertex(const cocos2d::Vec2 point)
    {
        this->vertices.push_back(point);
    }
    
    // TODO 구현
    bool Polygon::containPoint(const cocos2d::Vec2& point) const
    {
        return false;
    }
    
}















