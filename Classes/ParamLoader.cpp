//
//  ParamLoader.cpp
//  Ai002_SteeringBehavior
//
//  Created by 남준현 on 2015. 10. 20..
//
//

#include "ParamLoader.hpp"

namespace realtrick
{
    
    //
    // Constructor
    //
    ParamLoader::ParamLoader()
    {
        _fileName = "params.ini";
        parse();
    }
    
    
    
    //
    // RemoveCommentFromLine
    //
    void ParamLoader::_removeCommentFromLine(std::string& line)
    {
        std::string::size_type idx = line.find("//");
        if(idx != std::string::npos)
        {
            line = line.substr(0, idx);
        }
    }
    
    
    //
    // Parse (private)
    //
    void ParamLoader::_parse()
    {
        while(!_file.eof())
        {
            std::string line;
            std::getline(_file, line);
            _removeCommentFromLine(line);
            
            if(line == "\r" || line.empty()) continue;
            
            std::string::size_type begIdx;
            std::string::size_type endIdx;
            
            const std::string delims(" \\;=,");
            begIdx = line.find_first_not_of(delims);
            
            if(begIdx != std::string::npos)
            {
                endIdx = line.find_first_of(delims, begIdx);
                if( endIdx == std::string::npos)
                {
                    endIdx = line.size();
                }
            }
            
            std::string key = line.substr(begIdx, endIdx);
            
            begIdx = line.find_first_not_of(delims, endIdx);
            if(begIdx != std::string::npos)
            {
                endIdx = line.find_first_of(delims, begIdx);
                if(endIdx == std::string::npos)
                {
                    endIdx = line.size();
                }
            }
            
            std::string value = line.substr(begIdx, endIdx);
            _container.insert(std::make_pair(key, value));
            int i =0;
            i++;
        }
    }
    
    
    //
    // Parse (public)
    //
    void ParamLoader::parse()
    {
        _container.clear();
        std::string fullPathFile = cocos2d::FileUtils::getInstance()->fullPathForFilename(_fileName);
        _file.open(fullPathFile);
        if(_file.is_open())
        {
            _parse();
        }
        else
        {
            cocos2d::log("[%s] is not founded.", _fileName.c_str());
        }
        
        _file.close();
    }

}














