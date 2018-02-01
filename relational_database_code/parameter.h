//
//  parameter.hpp
//  lab1.cpp
//
//  Created by Alexandra Greenwood on 9/28/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#pragma once
#include <string>
#include <stdio.h>

class Parameter{
public:
    Parameter(){
        type="";
        value="";
    }
    Parameter(std::string t, std::string v){
        type=t;
        value=v;
    }
    ~Parameter(){}
    std::string getValue();
    std::string getType();
    std::string toString();
    std::string type;
    std::string value;
    
};
