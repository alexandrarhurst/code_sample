//
//  rule.cpp
//  lab1.cpp
//
//  Created by Alexandra Greenwood on 9/28/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#include "rule.h"

void Rule::addPredicate(Predicate p){
    predicateList.push_back(p);
}

std::string Rule::toString(){
    std::stringstream out;
    out<<predicate.toString()<<" :- ";
    out<<predicateList[0].toString();
    for(int i=1; i<predicateList.size(); i++){
        out<<","<<predicateList[i].toString();
    }
    out<<".";
    return out.str();
}

Predicate Rule::getPred(){
    return predicate;
}
