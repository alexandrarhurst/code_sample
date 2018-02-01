//
//  scheme.hpp
//  lab2
//
//  Created by Alexandra Greenwood on 10/21/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <vector>
#include <iostream>
#include <sstream>
#include "parameter.h"

class Scheme{
public:
    Scheme(){}
    ~Scheme(){}
    void addParams(std::vector<Parameter> v);
    void addMoreParams(std::vector<Parameter> v);
    void setParams(std::vector<std::string> v);
    void renameParams(int p, std::string s);
    void print();
    std::string ss();
    std::vector<Parameter> getParams();
    
    std::vector<Parameter> params;
};
