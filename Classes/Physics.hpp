//
//  Physics.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 20..
//
//

#pragma once

#include "Geometry.hpp"

namespace realtrick
{
    
    namespace physics
    {
        
        bool intersect(const Rect& rect1, const Rect& rect2);
        bool intersect(const Rect& rect, const Circle& circle);
        bool intersect(const Rect& rect, const Segment& segment);
        bool intersect(const Rect& rect, const Ray& ray);
        bool intersect(const Rect& rect, const Polygon& polygon);
        
        bool intersect(const Circle& circle, const Rect& rect);
        bool intersect(const Circle& circle1, const Circle& circle2);
        bool intersect(const Circle& circle, const Segment& segment);
        bool intersect(const Circle& circle, const Ray& ray);
        bool intersect(const Circle& circle, const Polygon& polygon);
        
        bool intersect(const Segment& segment, const Rect& rect);
        bool intersect(const Segment& segment, const Circle& circle);
        bool intersect(const Segment& segment1, const Segment& segment2);
        bool intersect(const Segment& segment, const Ray& ray);
        bool intersect(const Segment& segment, const Polygon& polygon);
        
        bool intersect(const Ray& ray, const Rect& rect);
        bool intersect(const Ray& ray, const Circle& circle);
        bool intersect(const Ray& ray, const Segment& segment);
        bool intersect(const Ray& ray1, const Ray& ray2);
        bool intersect(const Ray& ray, const Polygon& polygon);
        
        bool intersect(const Polygon& polygon, const Rect& rect);
        bool intersect(const Polygon& polygon, const Circle& circle);
        bool intersect(const Polygon& polygon, const Segment& segment);
        bool intersect(const Polygon& polygon, const Ray& ray);
        bool intersect(const Polygon& polygon1, const Polygon& polygon2);
        
    };
    
    
}




