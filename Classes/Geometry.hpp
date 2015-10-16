//
//  Geometry.hpp
//  Ai002_SteeringBahavior
//
//  Created by 남준현 on 2015. 10. 16..
//
//

#pragma once

#include "Vector2.hpp"

namespace realtrick
{
    class Rect
    {
    
    public:
    
        Vector2 origin;
        double  width;
        double  height;
    
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
        bool intersectsRect(const Rect& rect) const;
        bool intersectsCircle(const Vector2& center, double radius) const;
        Rect getMergedRect(const Rect& rect) const;
        void merge(const Rect& rect);
        static const Rect kZero;
    
    };

}