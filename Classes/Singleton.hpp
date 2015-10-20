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
    
    template <class Type>
    class Singleton
    {
    protected:
        
        Singleton() = default;
        Singleton(const Singleton&) = delete;
        Singleton(Singleton&&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton& operator=(Singleton&&) = delete;
        
    public:
        
        static Type& getInstance()
        {
            static Type instance;
            return instance;
        }
        
    };
    
}