//
//  tokens.hpp
//  lab1.cpp
//
//  Created by Alexandra Greenwood on 9/24/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#pragma once
#include <iostream>

class Token{
public:
    Token(){
        line=0;
    }
    Token(std::string t, std::string w, int l){
        type=t;
        word=w;
        line=l;
    }
    ~Token(){}
    std::string toString();
    std::string getType();
    std::string getValue();
    int getLine();
    
private:
    int line;
    std::string type;
    std::string word;
    
};
