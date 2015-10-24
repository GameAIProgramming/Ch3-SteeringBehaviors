#pragma once

#include "cocos2d.h"

#include "Vehicle.hpp"
#include "Obstacle.hpp"

enum class DetailViewMode : short
{
    kSeek,
    kFlee,
    kPursuit,
    kAvoidanceObstacle
};

class HelloWorldScene : public cocos2d::LayerColor
{
    
private:
    
    cocos2d::Size                           _winSize;
    
    static int                              _nextValidID;
    cocos2d::Sprite*                        _uiLayer;
    cocos2d::Sprite*                        _crossHair;
    
    cocos2d::Sprite*                        _gameView;
    cocos2d::Sprite*                        _detailView;
    cocos2d::Sprite*                        _avoidanceObstacleView;
    
    cocos2d::Vector<realtrick::Vehicle*>    _vehicles;
    cocos2d::Vector<realtrick::Obstacle*>   _obstacles;
    
    cocos2d::Vector<realtrick::Vehicle*>    _detailViewVehicles;
    cocos2d::Vector<realtrick::Obstacle*>   _detailViewObstacles;
    
    realtrick::Vehicle*                     _selectedVehicleDetail;
    realtrick::Vehicle*                     _selectedVehicleWorld;
    
    cocos2d::DrawNode*                      _worldNode;
    cocos2d::DrawNode*                      _detailNode;
    
    DetailViewMode                          _detailViewMode = DetailViewMode::kSeek;
    
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(HelloWorldScene);
    virtual void update(float dt) override;
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) override;
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) override;
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) override;
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) override;
    
    int                                     getNextValidID()                    { return _nextValidID++; }
    cocos2d::Sprite*                        getCrossHair() const                { return _crossHair; }
    cocos2d::Vector<realtrick::Obstacle*>   getObstacles() const                { return _obstacles; }
    cocos2d::Vector<realtrick::Vehicle*>    getVehicles() const                 { return _vehicles; }
    cocos2d::DrawNode*                      getWorldNode() const                { return _worldNode; }
    cocos2d::DrawNode*                      getDetailNode() const               { return _detailNode; }
    realtrick::Vehicle*                     getSelectedVehicle() const          { return _selectedVehicleWorld; }
    
    void initEntites();
    void initUI();
    float calAngle(const cocos2d::Vec2& v);
    void tagVehiclesWithinViewRange(realtrick::BaseEntity* entity, float range);
    void tagObstaclesWithinViewRange(realtrick::BaseEntity* entity, float range);
    
};
