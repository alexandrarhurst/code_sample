//
//  Node.hpp
//  lab2
//
//  Created by Alexandra Greenwood on 12/3/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <set>

class Node {
public:
    Node(){
        visited = false;
        postOrder = 1000000;
        other_visited = false;
    };
    ~Node(){};
    
    std::set<std::string> adjacent;
    bool visited;
    bool other_visited;
    int postOrder;
    
};
