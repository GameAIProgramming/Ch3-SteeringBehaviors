//
//  SteeringBehaviors.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 17..
//
//

#pragma once

#include "Vector2.hpp"
#include "Mat3.hpp"

namespace realtrick
{
    
    class Vehicle;
    
    enum class SummingMethod : short
    {
        kWeightedAverage,
        kPrioritized,
        kDithered
    };
    
    class SteeringBehaviors
    {
        
    private:
        
        enum class BehaviorType : int
        {
            kNone               = 0x00001, // 2^0 = 1     (2^0 * 1)
            kSeek               = 0x00002, // 2^1 = 2     (2^0 * 2)
            kFlee               = 0x00004, // 2^2 = 4     (2^0 * 4)
            kArrive             = 0x00008, // 2^3 = 8     (2^0 * 8)
            kWander             = 0x00010, // 2^4 = 16    (2^4 * 1)
            kCohesion           = 0x00020, // 2^5 = 32    (2^4 * 2)
            kSeparation         = 0x00040, // 2^6 = 64    (2^4 * 4)
            kAllignment         = 0x00080, // 2^7 = 128   (2^4 * 8)
            kObstacleAvoidance  = 0x00100, // 2^8 = 256   (2^8 * 1)
            kAallAvoidance      = 0x00200, // 2^9 = 512   (2^8 * 2)
            kFollowPath         = 0x00400, // 2^10 = 1024 (2^8 * 4)
            kPursuit            = 0x00800, // 2^11 = 2048 (2^8 * 8)
            kEvade              = 0x01000, // 2^12 = 4096 (2^12 * 1)
            kInterpose          = 0x02000, // 2^13 = 8192 (2^12 * 2)
            kHide               = 0x04000, // 2^14 = 16384 (2^12 * 4)
            kFlock              = 0x08000, // 2^15 = 32768 (2^12 * 8)
            kOffsetPursuit      = 0x10000  // 2^16 = 65536 (2^16 * 1)
        };
        
    private:
        
        Vehicle*                _vehicle;
        Vector2                 _steeringForce;
        
        Vehicle*                _targetEntity1;
        Vehicle*                _targetEntity2;
        
        Vector2                 _target;
        
        SummingMethod           _summingMethod;
        
        // 여러개의 상태를 비트단위로 나눠서 저장하기 위한 변수.
        int                     _flag;
        
        Vector2                 _wanderTarget;
        double                  _wanderJitter;
        double                  _wanderRadius;
        double                  _wanderDistance;
        
        
        double                  _weightSeek     = 1.0;
        double                  _weightFlee     = 1.0;
        double                  _weightArrive   = 1.0;
        double                  _weightPursuit  = 1.0;
        double                  _weightWander   = 1.0;
        
        
        
    private:
        
        // 찾기
        Vector2 _seek(const Vector2& targetPos);
        
        // 달아나기
        Vector2 _flee(const Vector2& targetPos);
        
        // 도착하기
        Vector2 _arrive(const Vector2& targetPos, double deceleration);
        
        // 추적하기
        Vector2 _pursuit(const Vehicle* evader);
        
        // 배회하기
        Vector2 _wander();
        
        void _calculateWeightedSum();
        void _calculatePrioritized();
        void _calculatedDithered();
        
    public:
        
        SteeringBehaviors(Vehicle* owner);
        SteeringBehaviors(const SteeringBehaviors&) = delete;
        SteeringBehaviors& operator=(const SteeringBehaviors&) = delete;
        
        Vector2 calculate();
        
        // 해당 비트자리가 동일한지 비교. (AND연산)
        bool isOnBehavior(BehaviorType type)        { return (_flag & (int)type) == (int)type; }
        
        // 해당 비트자리를 1로 맞춤. (OR연산)
        void enableBehavior(BehaviorType type)      { _flag |= (int)type; }
        
        // 해당 비트자리이 1이면 0으로 바꿈. (1^1 = 0)
        void disableBehavior(BehaviorType type)     { if(isOnBehavior(type)) _flag ^= (int)type; }

    };
    
}








