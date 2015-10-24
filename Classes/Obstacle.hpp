//
//  Obstacle.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 23..
//
//

#pragma once

#include "BaseEntity.hpp"

namespace realtrick
{

    class Obstacle : public BaseEntity
    {
    private:
        
        Obstacle() { _type = EntityType::kObstacle; }
        
    public:
        
        static Obstacle* create();
        
        virtual ~Obstacle() {}
        virtual bool handleMessage(const Telegram& msg) override { return false; }
        virtual void update(float dt) override {}
        
    };

}