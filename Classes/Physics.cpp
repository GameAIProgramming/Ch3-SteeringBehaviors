//
//  Physics.cpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 20..
//
//

#include "Physics.hpp"

using std::pair;
using std::vector;

namespace realtrick
{
    
    namespace physics
    {
        //
        // Rect
        //
        bool intersect(const Rect& a, const Rect& b)
        {
            return (a.getMinX() <= b.getMaxX() && a.getMaxX() >= b.getMinX() &&
                    a.getMinY() <= b.getMaxY() && a.getMaxY() >= b.getMinY());
        }
        
        bool intersect(const Rect& rect, const Circle& circle)
        {
            bool ret;
            return ret;
        }
        
        bool intersect(const Rect& rect, const Segment& segment)
        {
            bool ret;
            return ret;
        }
        
        bool intersect(const Rect& rect, const Ray& ray)
        {
            bool ret;
            return ret;
        }
        
        bool intersect(const Rect& rect, const Polygon& polygon)
        {
            bool ret;
            return ret;
        }
        
        
        
        
        //
        // Circle
        //
        bool intersect(const Circle& circle1, const Circle& circle2)
        {
            bool ret;
            return ret;
        }
        
        bool intersect(const Circle& circle, const Segment& segment)
        {
            bool ret;
            return ret;
        }
        
        bool intersect(const Circle& circle, const Ray& ray)
        {
            bool ret;
            return ret;
        }
        
        bool intersect(const Circle& circle, const Polygon& polygon)
        {
            bool ret;
            return ret;
        }
        
        
        //
        // Segment
        //
        bool intersect(const Segment& segment, const Circle& circle)
        {
            bool ret;
            return ret;
        }
        
        bool intersect(const Segment& segment1, const Segment& segment2)
        {
            bool ret;
            return ret;
        }
        
        bool intersect(const Segment& segment, const Ray& ray)
        {
            bool ret;
            return ret;
        }
        
        bool intersect(const Segment& segment, const Polygon& polygon)
        {
            bool ret;
            return ret;
        }
        
        
        //
        // Ray
        //
        bool intersect(const Ray& ray, const Circle& circle)
        {
            bool ret;
            return ret;
        }
        
        bool intersect(const Ray& ray, const Segment& segment)
        {
            bool ret;
            return ret;
        }
        
        bool intersect(const Ray& ray1, const Ray& ray2)
        {
            bool ret;
            return ret;
        }
        
        bool intersect(const Ray& ray, const Polygon& polygon)
        {
            bool ret;
            return ret;
        }
        
        
        //
        // Polygon
        //
        bool intersect(const Polygon& polygon, const Circle& circle)
        {
            bool ret;
            return ret;
        }
        
        bool intersect(const Polygon& polygon, const Segment& segment)
        {
            bool ret;
            return ret;
        }
        
        bool intersect(const Polygon& polygon, const Ray& ray)
        {
            bool ret;
            return ret;
        }
        
        bool intersect(const Polygon& polygon1, const Polygon& polygon2)
        {
            bool ret;
            return ret;
        }
    }
}










