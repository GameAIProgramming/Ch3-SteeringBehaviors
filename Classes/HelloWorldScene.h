#pragma once

#include "cocos2d.h"

class HelloWorldScene : public cocos2d::Layer
{
    
private:
    
    static int                              _nextValidID;
    cocos2d::Sprite*                        _spriteManager;
    
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(HelloWorldScene);
    int getNextValidID()    { return _nextValidID++; }
    
    void initEntites();
    
};
