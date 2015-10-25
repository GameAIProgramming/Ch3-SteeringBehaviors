//
//  Obstacle.cpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 24..
//
//

#include "Obstacle.hpp"

namespace realtrick
{
    
    Obstacle* Obstacle::create()
    {
        Obstacle *pRet = new(std::nothrow) Obstacle();
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
    
}