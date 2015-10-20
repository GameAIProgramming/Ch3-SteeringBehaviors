//
//  EntityManager.hpp
//  Ai001_StateMachine
//
//  Created by 남준현 on 2015. 9. 24..
//  Copyright © 2015년 남준현. All rights reserved.
//


#pragma once

#include <map>
#include "Singleton.hpp"

namespace realtrick
{

    class BaseEntity;

    #define EntMgr EntityManager::getInstance()

    class EntityManager : public Singleton<EntityManager>
    {
  
        friend Singleton<EntityManager>;
        
    private:
    
        std::map<int, BaseEntity*>          _entityMap;
    
    public:
    
        BaseEntity* getEntityFromID(int id);
        bool registEntity(BaseEntity* newEntity);
        bool removeEntity(BaseEntity* delEntity);
        void updateEntities(float dt);
        std::map<int, BaseEntity*> getEntMap() const    { return _entityMap; };
        
    };

}