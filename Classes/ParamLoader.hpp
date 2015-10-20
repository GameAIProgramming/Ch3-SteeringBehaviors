//
//  ParamLoader.hpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 20..
//
//

#pragma once

#include <fstream>
#include <map>
#include <string>
#include "cocos2d.h"
#include "Singleton.hpp"

namespace realtrick
{

#define Prm ParamLoader::getInstance()
    
    class ParamLoader : public Singleton<ParamLoader>
    {
        
        friend Singleton<ParamLoader>;
        
    private:
        
        std::ifstream                           _file;
        std::map<std::string, std::string>      _container;
        std::string                             _fileName;
        
    private:
        
        void            _parse();
        void            _removeCommentFromLine(std::string& line);
        ParamLoader();
        
    public:
        
        virtual ~ParamLoader()
        {
            if(_file.is_open())
                _file.close();
            _container.clear();
        }
        
        void parse();
        void setFileName(const std::string& fileName) { _fileName = fileName; }
        
        inline double           getValueAsDouble(const std::string& key) const;
        inline float            getValueAsFloat(const std::string& key) const;
        inline int              getValueAsInt(const std::string& key) const;
        inline std::string      getValueAsString(const std::string& key) const;
        inline bool             getValueAsBool(const std::string& key) const;
        
    };
    
}

#include "ParamLoader.inl"





