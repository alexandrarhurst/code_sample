//
//  tuple.hpp
//  lab2
//
//  Created by Alexandra Greenwood on 10/21/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include "parameter.h"
#include "tokens.h"

class Tuple{
public:
    Tuple(){}
    ~Tuple(){}
    void setName(std::string s);
    std::string getName();
    void setTuples(std::vector<std::string> l);
    void print();
    
    std::vector<std::string> list;
    std::string name;
    
    bool operator< (const Tuple b) const{
        return list< b.list;
    }
};
