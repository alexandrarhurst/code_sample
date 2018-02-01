//
//  rule.hpp
//  lab1.cpp
//
//  Created by Alexandra Greenwood on 9/28/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#pragma once
#include "predicate.h"
#include <stdio.h>
#include <sstream>

class Rule{
public:
    Rule(){
        predicate=Predicate();
    };
    Rule(Predicate p){
        predicate=p;
    };
    ~Rule(){}
    void addPredicate(Predicate p);
    Predicate getPred();
    std::string toString();
    Predicate predicate;
    std::vector<Predicate> predicateList;
};
