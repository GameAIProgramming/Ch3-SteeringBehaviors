#pragma once

#include "cocos2d.h"

class HelloWorldScene : public cocos2d::LayerColor
{
    
private:
    
    cocos2d::Size                           _winSize;
    
    static int                              _nextValidID;
    cocos2d::Sprite*                        _uiLayer;
    cocos2d::Sprite*                        _crossHair;
    
    cocos2d::Sprite*                        _gameView;
    cocos2d::Sprite*                        _optionView;
    
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(HelloWorldScene);
    virtual void update(float dt) override;
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) override;
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) override;
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) override;
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) override;
    
    int getNextValidID()                            { return _nextValidID++; }
    cocos2d::Sprite* getCrossHair() const           { return _crossHair; }
    void initEntites();
    void initUI();
    float calAngle(const cocos2d::Vec2& v);
    
};
