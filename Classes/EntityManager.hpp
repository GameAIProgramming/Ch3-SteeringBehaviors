//
//  EntityManager.hpp
//  Ai001_StateMachine
//
//  Created by 남준현 on 2015. 9. 24..
//  Copyright © 2015년 남준현. All rights reserved.
//


#pragma once

#include <map>

namespace realtrick
{

    class BaseEntity;

    #define EntMgr EntityManager::getInstance()

    class EntityManager
    {
  
    private:
    
        std::map<int, BaseEntity*>          _entityMap;
        
        EntityManager();
        EntityManager(const EntityManager& rhs) = delete;
        EntityManager& operator=(const EntityManager& rhs) = delete;
    
    public:
    
        static EntityManager& getInstance();
        BaseEntity* getEntityFromID(int id);
        bool registEntity(BaseEntity* newEntity);
        bool removeEntity(BaseEntity* delEntity);
        void updateEntities(float dt);
        std::map<int, BaseEntity*> getEntMap() const    { return _entityMap; };
        
    };

}