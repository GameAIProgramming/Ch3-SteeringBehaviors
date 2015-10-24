//
//  EntityTemplateFunctions.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 23..
//
//

#pragma once
#include "Physics.hpp"

namespace realtrick
{
    
    template <class T, class conT>
    bool overlapped(const T* ob, const conT& conOb, double minDistBetweenObstacles = 40.0)
    {
        typename conT::const_iterator iter;
        for(iter = conOb.begin() ; iter != conOb.end(); ++iter)
        {
            if(physics::intersect(Circle(ob->getPosition(), ob->getBRadius() + minDistBetweenObstacles),
                                  Circle((*iter)->getPosition(), (*iter)->getBRadius())))
            {
                return true;
            }
        }
        
        return false;
    }
    
    template <class T, class conT>
    void TagNeighbors(const T& entity, const conT& containerOfEntities, double radius)
    {
        for(auto iter = containerOfEntities.begin(); iter != containerOfEntities.end() ; ++iter)
        {
            entity->setFlag(false);
        }
    }
    
}




