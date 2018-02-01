//
//  predicate.hpp
//  lab1.cpp
//
//  Created by Alexandra Greenwood on 9/28/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "parameter.h"

class Predicate{
public:
    Predicate(){
        iden="";
    }
    Predicate(std::string i){
        iden=i;
    }
    Predicate(std::string i, std::vector<Parameter> p){
        iden=i;
        l=p;
    }
    std::string getID();
    std::vector<Parameter> getParams();
    void addParam(Parameter p);
    std::string toString();
    ~Predicate(){}
    std::string iden;
    std::vector<Parameter> l;
};
