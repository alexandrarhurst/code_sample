//
//  predicate.cpp
//  lab1.cpp
//
//  Created by Alexandra Greenwood on 9/28/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#include "predicate.h"
#include <sstream>

std::string Predicate::getID(){
    return iden;
}

std::vector<Parameter> Predicate::getParams(){
    return l;
}

void Predicate::addParam(Parameter p){
    l.push_back(p);
}

std::string Predicate::toString(){
    std::stringstream out;
    out<<iden<<"(";
    out<<l[0].getValue();
    for(int i=1; i<l.size(); i++){
        out<<","<<l[i].getValue();
    }
    out<<")";
    return out.str();
}
