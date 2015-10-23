//
//  Geometry.hpp
//  Ai002_SteeringBahavior
//
//  Created by 남준현 on 2015. 10. 16..
//
//

#pragma once

#include <vector>

#include "Vector2.hpp"
#include "Mat3.hpp"

namespace realtrick
{
    class Rect
    {
    
    public:
    
        Vector2         origin;
        double          width;
        double          height;
    
        Rect();
        Rect(double x, double y, double width, double height);
        Rect(const Vector2& pos, double width, double height);
        Rect(const Rect& copy);
        Rect& operator=(const Rect& rhs);
        void setRect(double x, double y, double width, double height);
        double getMinX() const;
        double getMidX() const;
        double getMaxX() const;
        double getMinY() const;
        double getMidY() const;
        double getMaxY() const;
        bool equals(const Rect& rect) const;
        bool containPoint(const Vector2& point) const;
        static const Rect kZero;
    
        virtual ~Rect() {}
        
    };

    class Circle
    {
      
    public:
        
        Vector2         origin;
        double          radius;
        
        Circle();
        Circle(double x, double y, double r);
        Circle(const Vector2& origin, double r);
        Circle(const Circle& copy);
        Circle& operator=(const Circle& rhs);
        void setCircle(double x, double y, double r);
        Circle getTranslatedCircle(const Vector2& dir, double distance);
        bool containPoint(const Vector2& point) const;
        
        virtual ~Circle() {}
        
    };
    
    
    
    class Segment
    {
        
    public:
        
        Vector2         start;
        Vector2         end;
        
        Segment();
        Segment(double sx, double sy, double ex, double ey);
        Segment(const Vector2& start, const Vector2& end);
        Segment(const Segment& copy);
        Segment& operator=(const Segment& rhs);
        void setSegment(double sx, double sy, double ex, double dy);
        Vector2 getDirection() const;
        double getDistance() const;
        double getDistanceSq() const;
        bool containPoint(const Vector2& point) const;
        
        virtual ~Segment() {}
    };

    class Polygon
    {
        
    public:
        
        std::vector<Vector2> vertices;
        
        Polygon();
        Polygon(const std::vector<Vector2>& segs);
        Polygon(const Polygon& copy);
        Polygon& operator=(const Polygon& rhs);
        void setPolygon(const std::vector<Vector2>& segs);
        void pushVertex(const Vector2 point);
        bool containPoint(const Vector2& point) const;
        
        virtual ~Polygon() { vertices.clear(); }
        
    };
    

    inline float randFloat(float min, float max)
    {
        std::mt19937 re((unsigned int)time(nullptr));
        std::uniform_real_distribution<float> urd(min, max);
        return urd(re);
    }
    
}



