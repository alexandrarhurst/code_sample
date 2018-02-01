//
//  datalogue.hpp
//  lab1.cpp
//
//  Created by Alexandra Greenwood on 9/28/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include "tokens.h"
#include "predicate.h"
#include "rule.h"

class Datalogue{
public:
    Datalogue(){}
    ~Datalogue(){}
    void addScheme(Predicate p);
    void addFact(Predicate f);
    void addRule(Rule r);
    void addQuery(Predicate q);
    void addDomain(std::vector<Parameter> l);
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Rule> rules;
    std::vector<Predicate> queries;
    std::string toString();
    std::string schemes_to_string();
    std::string facts_to_string();
    std::string rules_to_string();
    std::string queries_to_string();
    std::string domain_to_string();
    std::set<std::string> d;    
    std::vector<std::string> dupcheck;
};
