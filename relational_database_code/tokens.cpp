//
//  tokens.cpp
//  lab1.cpp
//
//  Created by Alexandra Greenwood on 9/24/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#include "tokens.h"
#include <sstream>

std::string Token::toString(){
    std::stringstream ss;
    ss << this->line;
    return "("+this->type+",\""+this->word+"\","+std::to_string(this->line)+")";
}

std::string Token::getType(){
    return type;
}

std::string Token::getValue(){
    return word;
}

int Token::getLine(){
    return line;
}
