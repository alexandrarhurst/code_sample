//
//  Database.hpp
//  lab2
//
//  Created by Alexandra Greenwood on 10/21/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <map>
#include <sstream>
#include "Relation.h"
#include "predicate.h"
#include "tuple.h"
#include "rule.h"
#include "graph.h"

class Database{
public:
    Database(){}
    ~Database(){}
    void addRelation(Relation r);
    void load(std::vector<Predicate> i, std::vector<Predicate> j, std::vector<Predicate> k, std::vector<Rule> r);
    void addToRelation(Tuple t);
    std::string toString();
    void runQuery();
    void optimizedQuery();
    Relation relationQuery(Predicate q);
    bool run_rule(Rule r);
    int fixed(std::set<std::string> r);
    int totalTups();
    
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Rule> rules;
    std::vector<Predicate> queries;
    std::vector<std::string> ids;
    std::vector<Relation> relations;
    std::vector<Relation> printing;
    std::map<std::string, Relation> m;
    std::vector<int> pos;
    int num;
    Graph g;
};
