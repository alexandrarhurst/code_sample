//
//  scheme.cpp
//  lab2
//
//  Created by Alexandra Greenwood on 10/21/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#include "scheme.h"

void Scheme::addParams(std::vector<Parameter> v){
    params=v;
}

void Scheme::addMoreParams(std::vector<Parameter> v){
    for(int i=0; i<v.size(); i++){
        //fill in later
        params.push_back(v[i]);
    }
}

void Scheme::setParams(std::vector<std::string> v){
    for(int i=0; i<v.size(); i++){
        //fill in later
        Parameter newparam("ID",v[i]);
        params.push_back(newparam);
    }
}

void Scheme::renameParams(int p, std::string s){
    Parameter parry("ID",s);
    params.at(p)=parry;
}

void Scheme::print(){
    for(int i=0; i<params.size(); i++){
        std::cout<<params[i].getValue()<<std::endl;
    }
}

std::vector<Parameter> Scheme::getParams(){
    return params;
}

std::string Scheme::ss(){
    std::stringstream forrelation;
    for(int i=0; i<params.size(); i++){
        forrelation<<params[i].getValue()<<std::endl;
    }
    return forrelation.str();
}
