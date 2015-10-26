//
//  Path.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 26..
//
//

#pragma once

#include <list>
#include "cocos2d.h"

class Path
{
    
private:
    
    std::list<cocos2d::Vec2>            _wayPoints;
    std::list<cocos2d::Vec2>::iterator  _curWaypoint;
    bool                                _isLoop;
    
public:
    
    explicit Path(bool isLoop) : _isLoop(isLoop)
    {
        _curWaypoint = _wayPoints.begin();
    }
    
    cocos2d::Vec2   getCurrentWaypoint() const                      { return *_curWaypoint; }
    bool            isFinished() const                              { return (_curWaypoint == _wayPoints.end()); }
    
    inline void     setNextWaypoint();
    void            setLoop(bool flag)                              { _isLoop = flag; }
    
    void            addWaypoint(const cocos2d::Vec2& newPoint)      { _wayPoints.push_back(newPoint); }
    
    void            set(const std::list<cocos2d::Vec2>& newPath)    { _wayPoints = newPath; _curWaypoint = _wayPoints.begin(); }
    void            set(const Path& path) { _wayPoints = path.getPath(); _curWaypoint = _wayPoints.begin(); }
    void            clear() { _wayPoints.clear(); }
    
    std::list<cocos2d::Vec2> getPath() const                        { return _wayPoints; }
    
};


inline void Path::setNextWaypoint()
{
    if(_wayPoints.size() == 0)
        return ;
    
    if( ++_curWaypoint == _wayPoints.end() && _isLoop)
    {
        _curWaypoint = _wayPoints.end();
    }
}