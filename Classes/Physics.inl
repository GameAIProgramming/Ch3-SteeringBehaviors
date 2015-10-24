//
//  Physics.inl
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
        inline bool intersect(const Rect& a, const Rect& b)
        {
            return (a.getMinX() <= b.getMaxX() && a.getMaxX() >= b.getMinX() &&
                    a.getMinY() <= b.getMaxY() && a.getMaxY() >= b.getMinY());
        }
        
        inline bool intersect(const Rect& rect, const Circle& circle)
        {
            double minX = rect.getMinX();
            double minY = rect.getMinY();
            double maxX = rect.getMaxX();
            double maxY = rect.getMaxY();
            
            return (rect.containPoint(circle.origin) ||
                    circle.containPoint(cocos2d::Vec2(minX, minY)) ||
                    circle.containPoint(cocos2d::Vec2(minX, maxY)) ||
                    circle.containPoint(cocos2d::Vec2(maxX, minY)) ||
                    circle.containPoint(cocos2d::Vec2(maxX, maxY)));
        }
        
        inline bool intersect(const Rect& rect, const Segment& segment)
        {
            double minX = rect.getMinX();
            double minY = rect.getMinY();
            double maxX = rect.getMaxX();
            double maxY = rect.getMaxY();
            
            if(intersect(Segment(minX, minY, maxX, minY), segment) ||
               intersect(Segment(maxX, minY, maxX, maxY), segment) ||
               intersect(Segment(maxX, maxY, minX, maxY), segment) ||
               intersect(Segment(minX, maxY, minX, minY), segment))
                return true;
            
            return false;
        }
        
        inline bool intersect(const Rect& rect, const Polygon& polygon)
        {
            double minX = rect.getMinX();
            double minY = rect.getMinY();
            double maxX = rect.getMaxX();
            double maxY = rect.getMaxY();
            
            std::vector<Segment> segs
            {
                Segment(minX, minY, maxX, minY), // left down -> right down
                Segment(maxX, minY, maxX, maxY), // right down -> right up
                Segment(maxX, maxY, minX, maxY), // right up -> left up
                Segment(minX, maxY, minX, minY)  // left up -> left down
            };
            
            for(std::vector<Segment>::size_type i = 0 ; i < segs.size() ; ++ i)
            {
                for(std::vector<cocos2d::Vec2>::size_type j = 0; j < polygon.vertices.size() - 1 ; ++ j)
                {
                    if(intersect(segs[i], Segment(polygon.vertices[j], polygon.vertices[j + 1])))
                        return true;
                }
                if(intersect(segs[i], Segment(polygon.vertices.back(), polygon.vertices.front())))
                    return true;
            }
            
            return false;
        }
        
        
        
        
        //
        // Circle
        //
        inline bool intersect(const Circle& circle, const Rect& rect)
        {
            return intersect(rect, circle);
        }
        
        inline bool intersect(const Circle& circle1, const Circle& circle2)
        {
            return (circle1.origin.getDistanceSq(circle2.origin) >= (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius));
        }
        
        inline bool intersect(const Circle& circle, const Segment& segment)
        {
            cocos2d::Vec2 d = segment.end - segment.start;
            cocos2d::Vec2 f = segment.start - circle.origin;
            
            double a = d.getLengthSq();
            double b = 2 * f.dot(d);
            double c = f.getLengthSq() - (circle.radius * circle.radius);
            
            double discriminant = b * b - 4 * a*c;
            if (discriminant < 0)
            {
                return false;
            }
            else
            {
                discriminant = sqrt(discriminant);
                double t1 = (-b - discriminant) / (2 * a);
                double t2 = (-b + discriminant) / (2 * a);
                
                if (t1 >= 0 && t1 <= 1)
                {
                    return true;
                }
                
                if (t2 >= 0 && t2 <= 1)
                {
                    return true;
                }
            }
            
            return false;
        }
        
        inline bool intersect(const Circle& circle, const Polygon& polygon)
        {
            for(std::vector<cocos2d::Vec2>::size_type j = 0; j < polygon.vertices.size() - 1 ; ++ j)
            {
                if(intersect(circle, Segment(polygon.vertices[j], polygon.vertices[j + 1])))
                    return true;
            }
            if(intersect(circle, Segment(polygon.vertices.back(), polygon.vertices.front())))
                return true;
            
            return false;
        }
        
        
        //
        // Segment
        //
        inline bool intersect(const Segment& segment, const Rect& rect)
        {
            return intersect(rect, segment);
        }
        
        inline bool intersect(const Segment& segment, const Circle& circle)
        {
            return intersect(circle, segment);
        }
        
        inline bool intersect(const Segment& segment1, const Segment& segment2)
        {
            float t, s;
            float under = (segment2.end.y - segment2.start.y) * (segment1.end.x - segment1.start.x) - (segment2.end.x - segment2.start.x) * (segment1.end.y - segment1.start.y);
            
            if (under == 0) return false;
            
            float _t = (segment2.end.x - segment2.start.x) * (segment1.start.y - segment2.start.y) - (segment2.end.y - segment2.start.y) * (segment1.start.x - segment2.start.x);
            float _s = (segment1.end.x - segment1.start.x) * (segment1.start.y - segment2.start.y) - (segment1.end.y - segment1.start.y) * (segment1.start.x - segment2.start.x);
            
            t = _t / under;
            s = _s / under;
            
            if (t < 0.0 || t > 1.0 || s < 0.0 || s > 1.0) return false;
            if (_t == 0 && _s == 0) return false;
            
            return true;
        }
        
        inline bool intersect(const Segment& segment, const Polygon& polygon)
        {
            for(std::vector<cocos2d::Vec2>::size_type j = 0; j < polygon.vertices.size() - 1 ; ++ j)
            {
                if(intersect(segment, Segment(polygon.vertices[j], polygon.vertices[j + 1])))
                    return true;
            }
            if(intersect(segment, Segment(polygon.vertices.back(), polygon.vertices.front())))
                return true;
            
            return false;

        }
        
        //
        // Polygon
        //
        inline bool intersect(const Polygon& polygon, const Rect& rect)
        {
            return intersect(rect, polygon);
        }
        
        inline bool intersect(const Polygon& polygon, const Circle& circle)
        {
            return intersect(circle, polygon);
        }
        
        inline bool intersect(const Polygon& polygon, const Segment& segment)
        {
            return intersect(segment, polygon);
        }
        
        inline bool intersect(const Polygon& polygon1, const Polygon& polygon2)
        {
            
            for(std::vector<cocos2d::Vec2>::size_type i = 0; i < polygon1.vertices.size() - 1 ; ++ i)
            {
                for(std::vector<cocos2d::Vec2>::size_type j = 0; j < polygon2.vertices.size() - 1 ; ++ j)
                {
                    if(intersect(Segment(polygon1.vertices[i], polygon1.vertices[i + 1]), Segment(polygon2.vertices[j], polygon2.vertices[j + 1])))
                        return true;
                }
                
                if(intersect(Segment(polygon1.vertices[i], polygon1.vertices[i + 1]), Segment(polygon2.vertices.back(), polygon2.vertices.front())))
                    return true;
            }
            
            for(std::vector<cocos2d::Vec2>::size_type i = 0; i < polygon2.vertices.size() - 1 ; ++ i)
            {
                if(intersect(Segment(polygon1.vertices.back(), polygon1.vertices.front()), Segment(polygon2.vertices[i], polygon2.vertices[i + 1])))
                    return true;
            }
            
            if(intersect(Segment(polygon1.vertices.back(), polygon1.vertices.front()), Segment(polygon2.vertices.back(), polygon2.vertices.front())))
                return true;

            
            return false;
        }
    }
}










