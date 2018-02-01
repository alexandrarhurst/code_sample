//
//  graph.hpp
//  lab2
//
//  Created by Alexandra Greenwood on 12/3/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stack>
#include <map>
#include "predicate.h"
#include "rule.h"
#include "Relation.h"
#include "tuple.h"
#include "Node.h"


class Graph{
public:
    Graph(){}
    ~Graph(){}
    void createGraph(std::vector<Predicate> queries, std::vector<Rule> rules);
    void printGraph();
    void printBackward();
    void depthFirst(std::string s);
    void otherDepthFirst(std::string s);
    void reset();
    void printPost();
    void ruleOrder(std::string s, int i);
    void backward();
    void printAll(std::vector<Predicate> queries);
    std::map<std::string, Node> theGraph;
    std::map<std::string, Node> backGraph;
    std::map<std::string, Predicate> queryMap;
    std::map<std::string, Rule> ruleMap;
    std::vector<std::vector<std::string>> SCC();
    int post;
    std::vector<std::string> order;
};
