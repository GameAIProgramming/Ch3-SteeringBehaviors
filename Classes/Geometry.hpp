//
//  Geometry.hpp
//  Ai002_SteeringBahavior
//
//  Created by 남준현 on 2015. 10. 16..
//
//

#pragma once

#include <vector>
#include <chrono>

#include "Mat3.hpp"

namespace realtrick
{
    class Rect
    {
    
    public:
    
        cocos2d::Vec2           origin;
        double                  width;
        double                  height;
    
        Rect();
        Rect(double x, double y, double width, double height);
        Rect(const cocos2d::Vec2& pos, double width, double height);
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
        bool containPoint(const cocos2d::Vec2& point) const;
        static const Rect kZero;
    
        virtual ~Rect() {}
        
    };

    class Circle
    {
      
    public:
        
        cocos2d::Vec2           origin;
        double                  radius;
        
        Circle();
        Circle(double x, double y, double r);
        Circle(const cocos2d::Vec2& origin, double r);
        Circle(const Circle& copy);
        Circle& operator=(const Circle& rhs);
        void setCircle(double x, double y, double r);
        Circle getTranslatedCircle(const cocos2d::Vec2& dir, double distance);
        bool containPoint(const cocos2d::Vec2& point) const;
        
        virtual ~Circle() {}
        
    };
    
    
    
    class Segment
    {
        
    public:
        
        cocos2d::Vec2         start;
        cocos2d::Vec2         end;
        
        Segment();
        Segment(double sx, double sy, double ex, double ey);
        Segment(const cocos2d::Vec2& start, const cocos2d::Vec2& end);
        Segment(const Segment& copy);
        Segment& operator=(const Segment& rhs);
        void setSegment(double sx, double sy, double ex, double dy);
        cocos2d::Vec2 getDirection() const;
        double getDistance() const;
        double getDistanceSq() const;
        bool containPoint(const cocos2d::Vec2& point) const;
        
        virtual ~Segment() {}
    };

    class Polygon
    {
        
    public:
        
        std::vector<cocos2d::Vec2> vertices;
        
        Polygon();
        Polygon(const std::vector<cocos2d::Vec2>& segs);
        Polygon(const Polygon& copy);
        Polygon& operator=(const Polygon& rhs);
        void setPolygon(const std::vector<cocos2d::Vec2>& segs);
        void pushVertex(const cocos2d::Vec2 point);
        bool containPoint(const cocos2d::Vec2& point) const;
        
        virtual ~Polygon() { vertices.clear(); }
        
    };
    
//    
//    inline float randFloat(float min, float max)
//    {
//        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
//        std::mt19937 engine((unsigned int)seed);
//        std::uniform_real_distribution<float> distribution(min, max);
//        auto generator = bind(distribution, engine);
//        return generator();
//    }
//    
//    inline int randInt(int min, int max)
//    {
//        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
//        std::mt19937 engine((unsigned int)seed);
//        std::uniform_int_distribution<int> distribution(min, max);
//        auto generator = bind(distribution, engine);
//        return generator();
//    }
    
}



