//
//  Singleton.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 19..
//
//

#pragma once

namespace realtrick
{
    
    template <typename Derived>
    class Singleton
    {
        
    protected:
        
        Singleton() = default;
        ~Singleton() = default;
        
    public:
        
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        
        static Derived& getInstance()
        {
            static Derived instance;
            return instance;
        }
        
    };
    
}