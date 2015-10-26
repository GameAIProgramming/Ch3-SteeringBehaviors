#include "HelloWorldScene.hpp"
#include "Vehicle.hpp"
#include "Obstacle.hpp"
#include "ParamLoader.hpp"
#include "Geometry.hpp"
#include "EntityTemplateFunctions.hpp"
#include "Transformations.hpp"

USING_NS_CC;
using namespace realtrick;

int HelloWorldScene::_nextValidID = 0;

Scene* HelloWorldScene::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorldScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool HelloWorldScene::init()
{
    if ( !LayerColor::initWithColor(Color4B::GRAY) )
    {
        return false;
    }
    
    this->scheduleUpdate();
    _winSize = Director::getInstance()->getVisibleSize();
    
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = CC_CALLBACK_2(HelloWorldScene::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(HelloWorldScene::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(HelloWorldScene::onTouchesEnded, this);
    touchListener->onTouchesCancelled = CC_CALLBACK_2(HelloWorldScene::onTouchesCancelled, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    initUI();
    initEntites();
    
    return true;
}

void HelloWorldScene::initEntites()
{
    // Create Vehicles
    int numOfVehicles = Prm.getValueAsInt("NumOfVehicles");
    for(int i = 0 ; i < numOfVehicles ; ++ i)
    {
        Vehicle* vehicle = Vehicle::create("Vehicle.png");
        vehicle->setGameWorld(this);
        vehicle->setBRadius(15.0f);
        vehicle->setPosition(Vec2(random(0.0f, 600.0f), random(0.0f, 600.0f)));
        vehicle->setTag(getNextValidID());
        this->setBehaviorAsNormalVehicle(vehicle);
        _gameView->addChild(vehicle);
        _vehicles.pushBack(vehicle);
        
        // for DetailView Vehicle
        Vehicle* detailViewVehicle = Vehicle::create("Vehicle.png");
        _detailView->addChild(detailViewVehicle);
        _detailViewVehicles.pushBack(detailViewVehicle);
    }
    
    _pursuer = Vehicle::create("pursuer.png");
    _pursuer->setGameWorld(this);
    _pursuer->setBRadius(15.0f);
    _pursuer->setMaxSpeed(100.0f);
    _pursuer->setPosition(Vec2(random(0.0f, 600.0f), random(0.0f, 600.0f)));
    _pursuer->setTag(getNextValidID());
    _pursuer->getSteering()->enableBehavior(BehaviorType::kWander);
    _pursuer->getSteering()->enableBehavior(BehaviorType::kPursuit);
    _pursuer->getSteering()->enableBehavior(BehaviorType::kObstacleAvoidance);
    _gameView->addChild(_pursuer);
    _vehicles.pushBack(_pursuer);
    
    Vehicle* detailViewPursuer = Vehicle::create("pursuer.png");
    _detailView->addChild(detailViewPursuer);
    _detailViewVehicles.pushBack(detailViewPursuer);
    
    
    // initialize selected detailView vehicle and worldView vehicle.
    _selectedVehicleDetail = Vehicle::create("Vehicle.png");
    _selectedVehicleDetail->setVisible(false);
    _detailView->addChild(_selectedVehicleDetail);
    
    this->setBehaviorAsSelectedVehicle(_vehicles.at(0));
    
    // Create Obstacles;
    int numOfObstacles = Prm.getValueAsInt("NumOfObstacles");
    for(int i = 0 ; i < numOfObstacles ; ++ i)
    {
        int numOfAllowableTrys = 2000;
        while(numOfAllowableTrys--)
        {
            double radius = random(Prm.getValueAsFloat("MinObstacleRadius"), Prm.getValueAsFloat("MaxObstacleRadius"));
            const int border = 10;
            
            float x = random(radius + border, 600.0f - radius - border);
            float y = random(radius + border, 600.0f - radius - border);
            
            Obstacle* ob = Obstacle::create();
            ob->setPosition(Vec2(x, y));
            ob->setBRadius(radius);
            
            const int minGapBetweenObstacles = 20;
            if(!overlapped(ob, _obstacles, minGapBetweenObstacles))
            {
                DrawNode* node = DrawNode::create();
                node->drawCircle(Vec2::ZERO, ob->getBRadius(), 360.0f, 100, false, 1.0f, 1.0f, Color4F::BLUE);
                ob->addChild(node);
                
                _obstacles.pushBack(ob);
                ob->setTag(getNextValidID());
                _gameView->addChild(ob);
                
                // for DetailView Obstacles
                Obstacle* detailViewOb = Obstacle::create();
                detailViewOb->setPosition(Vec2(x, y));
                detailViewOb->setBRadius(radius);
                
                DrawNode* avoidanceNode = DrawNode::create();
                avoidanceNode->drawCircle(Vec2::ZERO, detailViewOb->getBRadius(), 360.0f, 100, false, 1.0f, 1.0f, Color4F::BLUE);
                detailViewOb->addChild(avoidanceNode);
                
                _detailViewObstacles.pushBack(detailViewOb);
                _detailView->addChild(detailViewOb);
                
                break;
            }
        }
    }
    
    // Create Walls
    
    const int numOfVertex = Prm.getValueAsInt("NumOfWallVertice");
    std::vector<Vec2> walls
    {
        cocos2d::Vec2(20,20),
        cocos2d::Vec2(580,20),
        cocos2d::Vec2(580,580),
        cocos2d::Vec2(20,580)
    };
    
    for(int i = 0 ; i < numOfVertex - 1; ++ i)
    {
        Wall2D* wall = Wall2D::create(Segment(Vec2(walls.at(i)), Vec2(walls.at(i+1))));
        _gameView->addChild(wall);
        _walls.pushBack(wall);
    }
    
    Wall2D* wall = Wall2D::create(Segment(Vec2(walls.at(numOfVertex - 1)), Vec2(walls.at(0))));
    _gameView->addChild(wall);
    _walls.pushBack(wall);
    
}

void HelloWorldScene::update(float dt)
{
    _worldNode->clear();
    _detailNode->clear();
    
    for(auto &d : _vehicles)
    {
        d->update(dt);
        d->setRotation(calAngle(d->getHeading()));
    }
    
    // copy detailVehicle from selectedWorldVehicle.
    _selectedVehicleDetail->setPosition(_selectedVehicleWorld->getPosition());
    _selectedVehicleDetail->setHeading(_selectedVehicleWorld->getHeading());
    _selectedVehicleDetail->setRotation(_selectedVehicleWorld->getRotation());
    
    for(int i = 0 ; i < _obstacles.size(); ++i)
    {
        _detailViewObstacles.at(i)->setVisible(false);
        Vec2 localPos = getLocalSpaceVector(_obstacles.at(i)->getPosition(),
                                            _selectedVehicleDetail->getHeading(),
                                            _selectedVehicleDetail->getSide(),
                                            _selectedVehicleDetail->getPosition());
        
        cocos2d::Rect localViewRect(0.0f, 0.0f, 476.0f, 600.0f);
        if(localViewRect.containsPoint(localPos + Vec2(238.0f, 300.0f)))
        {
            _detailViewObstacles.at(i)->setVisible(true);
            _detailViewObstacles.at(i)->setPosition(Vec2(238, 300) + localPos);
        }
    }
    
    for(int i = 0 ; i < _vehicles.size(); ++i)
    {
        _detailViewVehicles.at(i)->setVisible(false);
        Vec2 localPos = getLocalSpaceVector(_vehicles.at(i)->getPosition(),
                                            _selectedVehicleDetail->getHeading(),
                                            _selectedVehicleDetail->getSide(),
                                            _selectedVehicleDetail->getPosition());
        
        cocos2d::Rect localViewRect(0.0f, 0.0f, 476.0f, 600.0f);
        if(localViewRect.containsPoint(localPos + Vec2(238.0f, 300.0f)))
        {
            _detailViewVehicles.at(i)->setVisible(true);
            _detailViewVehicles.at(i)->setPosition(Vec2(238, 300) + localPos);
            Vec2 localHeading = getLocalSpaceVector(_vehicles.at(i)->getHeading(),
                                                    _selectedVehicleDetail->getHeading(),
                                                    _selectedVehicleDetail->getSide());
            
            _detailViewVehicles.at(i)->setRotation(calAngle(localHeading));
        }
    }
}

void HelloWorldScene::initUI()
{
    
    _gameView = Sprite::create();
    _gameView->setPosition(Vec2(20.0f, 20.0f));
    //    DrawNode* gameViewNode = DrawNode::create();
    //    gameViewNode->drawSegment(Vec2::ZERO, Vec2(600.0f, 0.0f), 1.0f, Color4F::RED);
    //    gameViewNode->drawSegment(Vec2(600.0f, 0.0f), Vec2(600.0f, 600.0f), 1.0f, Color4F::RED);
    //    gameViewNode->drawSegment(Vec2(600.0f, 600.0f), Vec2(0.0f, 600.0f), 1.0f, Color4F::RED);
    //    gameViewNode->drawSegment(Vec2(0.0f, 600.0f), Vec2::ZERO, 1.0f, Color4F::RED);
    //_gameView->addChild(gameViewNode);
    addChild(_gameView, 0);
    
    
    _detailView = Sprite::create();
    _detailView->setPosition(Vec2(640.0f, 20.0f));
    //DrawNode* optionViewNode = DrawNode::create();
    //optionViewNode->drawSegment(Vec2::ZERO, Vec2(476.0f, 0.0f), 1.0f, Color4F::RED);
    //optionViewNode->drawSegment(Vec2(476.0f, 0.0f), Vec2(476.0f, 600.0f), 1.0f, Color4F::RED);
    //optionViewNode->drawSegment(Vec2(476.0f, 600.0f), Vec2(0.0f, 600.0f), 1.0f, Color4F::RED);
    //optionViewNode->drawSegment(Vec2(0.0f, 600.0f), Vec2::ZERO, 1.0f, Color4F::RED);
    //_optionView->addChild(optionViewNode);
    addChild(_detailView, 0);
    
    _uiLayer = Sprite::create();
    addChild(_uiLayer, 1);
    
    DrawNode* bgNode = DrawNode::create();
    bgNode->drawSolidRect(Vec2::ZERO, Vec2(1136.0f, 20.0f), Color4F::BLACK);
    bgNode->drawSolidRect(Vec2::ZERO, Vec2(20.0f, 640.0f), Color4F::BLACK);
    bgNode->drawSolidRect(Vec2(620.0f, 0.0f), Vec2(640.0f, 640.0f), Color4F::BLACK);
    bgNode->drawSolidRect(Vec2(1116.0f, 0.0f), Vec2(1136.0f, 640.0f), Color4F::BLACK);
    bgNode->drawSolidRect(Vec2(0.0f, 620.0f), Vec2(1136.0f, 640.0f), Color4F::BLACK);
    addChild(bgNode,2);
    
    _crossHair = Sprite::create();
    
    DrawNode* node = DrawNode::create();
    node->drawSegment(Vec2(-7.0f, -7.0f), Vec2(-3.0f, -3.0f), 1.0f, Color4F::MAGENTA);
    node->drawSegment(Vec2(7.0f, -7.0f), Vec2(3.0f, -3.0f), 1.0f, Color4F::MAGENTA);
    node->drawSegment(Vec2(7.0f, 7.0f), Vec2(3.0f, 3.0f), 1.0f, Color4F::MAGENTA);
    node->drawSegment(Vec2(-7.0f, 7.0f), Vec2(-3.0f, 3.0f), 1.0f, Color4F::MAGENTA);
    _crossHair->addChild(node);
    _crossHair->setPosition(_winSize / 2);
    _crossHair->runAction(RepeatForever::create(RotateBy::create(1.0f, 90.0f)));
    _uiLayer->addChild(_crossHair);
    
    _worldNode = DrawNode::create();
    _gameView->addChild(_worldNode);
    
    _detailNode = DrawNode::create();
    _detailView->addChild(_detailNode, 2);
    
}


void HelloWorldScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    for(auto &d : touches)
    {
        Vec2 touchPos = d->getLocation();
        
        if(touchPos.x > 620.0f) touchPos.x = 620.0f;
        else if(touchPos.x < 20.0f) touchPos.x = 20.0f;
        
        if(touchPos.y > 620.0f) touchPos.y = 620.0f;
        else if(touchPos.y < 20.0f) touchPos.y = 20.0f;
        
        // select vehicle in world.
        for(auto &d : _vehicles)
        {
            if(physics::intersect(Circle(d->getPosition(), d->getBRadius()),
                                  Circle(Vec2(touchPos.x - 20.0f, touchPos.y - 20.0f), 15.0f)))
            {
                if(d != _pursuer)
                {
                    setBehaviorAsNormalVehicle(_selectedVehicleWorld);
                    setBehaviorAsSelectedVehicle(d);
                    break;
                }
            }
        }
        
        _crossHair->setPosition(touchPos);
    }
}

void HelloWorldScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    for(auto &d : touches)
    {
        Vec2 touchPos = d->getLocation();
        
        if(touchPos.x > 620.0f) touchPos.x = 620.0f;
        else if(touchPos.x < 20.0f) touchPos.x = 20.0f;
        
        if(touchPos.y > 620.0f) touchPos.y = 620.0f;
        else if(touchPos.y < 20.0f) touchPos.y = 20.0f;
        
        _crossHair->setPosition(touchPos);
    }
}

void HelloWorldScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    for(auto &d : touches)
    {
        Vec2 touchPos = d->getLocation();
        
        if(touchPos.x > 620.0f) touchPos.x = 620.0f;
        else if(touchPos.x < 20.0f) touchPos.x = 20.0f;
        
        if(touchPos.y > 620.0f) touchPos.y = 620.0f;
        else if(touchPos.y < 20.0f) touchPos.y = 20.0f;
        
        _crossHair->setPosition(touchPos);
    }
}

void HelloWorldScene::onTouchesCancelled(const std::vector<Touch*>& touches, Event *unused_event)
{
    for(auto &d : touches)
    {
        Vec2 touchPos = d->getLocation();
        
        if(touchPos.x > 620.0f) touchPos.x = 620.0f;
        else if(touchPos.x < 20.0f) touchPos.x = 20.0f;
        
        if(touchPos.y > 620.0f) touchPos.y = 620.0f;
        else if(touchPos.y < 20.0f) touchPos.y = 20.0f;
        
        _crossHair->setPosition(touchPos);
    }
}


float HelloWorldScene::calAngle(const Vec2& v)
{
    Vec2 axis(0.0f, 1.0f);
    Vec2 rotated90 = axis.getRPerp();
    
    float angle = MathRadianToDegree(acos((rotated90.x * v.x + rotated90.y * v.y) /
                                          (sqrt(rotated90.x * rotated90.x + rotated90.y * rotated90.y) * sqrt(v.x * v.x + v.y * v.y))));
    if (angle > 90.0f)
    {
        return 360.0f - MathRadianToDegree(acos((axis.x * v.x + axis.y * v.y) /
                                                (sqrt(axis.x * axis.x + axis.y * axis.y) * sqrt(v.x * v.x + v.y * v.y))));
    }
    
    return MathRadianToDegree(acos((axis.x * v.x + axis.y * v.y) / (sqrt(axis.x * axis.x + axis.y * axis.y) * sqrt(v.x * v.x + v.y * v.y))));
}

void HelloWorldScene::tagVehiclesWithinViewRange(realtrick::BaseEntity* entity, float range)
{
    TagNeighbors(entity, _vehicles, range);
}

void HelloWorldScene::tagObstaclesWithinViewRange(realtrick::BaseEntity* entity, float range)
{
    TagNeighbors(entity, _obstacles, range);
}

void HelloWorldScene::setBehaviorAsNormalVehicle(realtrick::Vehicle* vehicle)
{
    vehicle->stopAllActions();
    vehicle->setMaxSpeed(Prm.getValueAsFloat("MaxSpeed"));
    vehicle->getSteering()->disableAllBehavior();
    vehicle->getSteering()->enableBehavior(BehaviorType::kWander);
    vehicle->getSteering()->enableBehavior(BehaviorType::kHide);
    //vehicle->getSteering()->enableBehavior(BehaviorType::kOffsetPursuit);
    vehicle->getSteering()->enableBehavior(BehaviorType::kWallAvoidance);
    vehicle->getSteering()->enableBehavior(BehaviorType::kObstacleAvoidance);
    vehicle->setTexture(Director::getInstance()->getTextureCache()->addImage("Vehicle.png"));
    vehicle->setScale(1.0f, 1.0f);
    
}

void HelloWorldScene::setBehaviorAsSelectedVehicle(realtrick::Vehicle* vehicle)
{
    _selectedVehicleWorld = vehicle;
    vehicle->setMaxSpeed(Prm.getValueAsFloat("MaxSpeed") * 2.0f);
    vehicle->getSteering()->disableAllBehavior();
    vehicle->getSteering()->enableBehavior(BehaviorType::kArrive);
    vehicle->getSteering()->enableBehavior(BehaviorType::kObstacleAvoidance);
    vehicle->getSteering()->enableBehavior(BehaviorType::kWallAvoidance);
    vehicle->setTexture(Director::getInstance()->getTextureCache()->addImage("Vehicle_s.png"));
    vehicle->runAction(RepeatForever::create(Sequence::create(
                                                              ScaleTo::create(0.25f, 2.0f),
                                                              ScaleTo::create(0.5f, 0.2f),
                                                              ScaleTo::create(0.25f, 2.0f),
                                                              ScaleTo::create(0.5f, 0.2f),
                                                              nullptr)));
}






