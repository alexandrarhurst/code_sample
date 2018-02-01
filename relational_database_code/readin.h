//
//  readin.hpp
//  lab1.cpp
//
//  Created by Alexandra Greenwood on 9/24/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#pragma once
#include <vector>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "tokens.h"

class Readin{
public:
    Readin(std::string filename){
        readFile(filename);
    };
    ~Readin(){};
    void readFile(std::string filename);
    void readToken(std::string token);
    std::vector<Token> analysis();
    int alpha(int i);
    int alphastring(int i);
    int block_comment(int i);
    int line_comment(int i);
    std::vector<Token> getTokens();
    
private:
    std::string input;
    int total_lines;
    std::vector<Token> tokens;
};
