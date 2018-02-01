//
//  parser.hpp
//  lab1.cpp
//
//  Created by Alexandra Greenwood on 9/29/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <vector>
#include <exception>
#include "datalogue.h"
#include "rule.h"

class Parser{
public:
    Parser(){
        index=0;
    }
    Parser(std::vector<Token> temp){
        tokens=temp;
        index=0;
        t=tokens[0];
        parseDatalog();
    }
    ~Parser(){}
    void parseDatalog();
    void parseScheme();
    void parseSchemeList();
    void parseFact();
    void parseFactList();
    void parseRule();
    void parseRuleList();
    void parseQuery();
    void parseQueryList();
    void parseStringList();
    void parseParameter();
    void parseParameterList();
    void parseIDList();
    void parseHeadPredicate();
    void parsePredicate();
    void parsePredicateList();
    void parseExpression();
    std::string parseOperator();
    bool match(std::string thing);
    Datalogue getData();
    
    
    int index;
    std::vector<Token> tokens;
    Token t;
    Datalogue d;
    Predicate p;
    Rule r;
    
};
