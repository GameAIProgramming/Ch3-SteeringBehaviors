//
//  EntityManager.cpp
//  Ai001_StateMachine
//
//  Created by 남준현 on 2015. 9. 24..
//  Copyright © 2015년 남준현. All rights reserved.
//

#include "EntityManager.hpp"
#include "BaseEntity.hpp"

namespace realtrick
{

    void EntityManager::updateEntities(float dt)
    {
        for(auto &d : _entityMap)
        {
            d.second->update(dt);
        }
    }

    EntityManager::EntityManager()
    {
    }

    EntityManager& EntityManager::getInstance()
    {
        static EntityManager instance;
        return instance;
    }

    BaseEntity* EntityManager::getEntityFromID(int id)
    {
        auto iter = _entityMap.find(id);
    
        if(iter != _entityMap.end())
            return iter->second;
        else
            return nullptr;
    }

    bool EntityManager::registEntity(BaseEntity* newEntity)
    {
        auto iter = _entityMap.find(newEntity->getID());
        if(iter == _entityMap.end())
        {
            _entityMap.insert(std::make_pair(newEntity->getID(), newEntity));
            return true;
        }
        else
        {
            return false;
        }
    }

    bool EntityManager::removeEntity(BaseEntity* delEntity)
    {
        auto iter = _entityMap.find(delEntity->getID());
        
        if(iter != _entityMap.end())
        {
            _entityMap.erase(iter);
            return true;
        }
        else
        {
            return false;
        }
    }

}





