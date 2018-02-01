//
//  tuple.cpp
//  lab2
//
//  Created by Alexandra Greenwood on 10/21/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#include "tuple.h"

void Tuple::setName(std::string s){
    name=s;
}

std::string Tuple::getName(){
    return name;
}

void Tuple::setTuples(std::vector<std::string> l){
    list=l;
}

void Tuple::print(){
    for(int i=0; i<list.size(); i+=2){
        std::cout<<list[i]<<" "<<list[i+1]<<std::endl;
    }
}
