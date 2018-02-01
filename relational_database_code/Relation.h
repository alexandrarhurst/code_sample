//
//  Relation.hpp
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
#include <utility>
#include <set>
#include <sstream>
#include "predicate.h"
#include "scheme.h"
#include "tuple.h"

class Relation{
public:
    Relation(){}
    ~Relation(){}
    std::string getName();
    void setName(std::string s);
    void addTuple(Tuple t);
    Scheme getScheme();
    void setScheme(Scheme s);
    Relation select(int i, std::string s);
    Relation select(int i, int j);
    Relation project(std::vector<int> p);
    Relation rename(std::vector<std::string> input);
    int countTuples(std::vector<int> pos, std::vector<std::string> ids);
    void printTuples(std::vector<int> pos, std::vector<std::string> ids, int num);
    void printRelation();
    std::string ssRelation();
    void printAllTuples();
    Relation naturalJoin(Relation r1, Relation r2);
    bool canJoin(Scheme s1, Scheme s2, Tuple t1, Tuple t2);
    Tuple join(Scheme s1, Scheme s2, Tuple t1, Tuple t2);
    Relation relational_union(Relation r2);
    
    std::string name;
    std::set<Tuple> data;
    Scheme scheme2;
};
