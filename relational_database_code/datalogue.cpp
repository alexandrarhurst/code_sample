//
//  datalogue.cpp
//  lab1.cpp
//
//  Created by Alexandra Greenwood on 9/28/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#include "datalogue.h"
#include <iostream>
#include <sstream>
#include <set>


void Datalogue::addScheme(Predicate p){
    schemes.push_back(p);
}

void Datalogue::addFact(Predicate f){
    addDomain(f.getParams());
    std::stringstream ss;
    ss<<f.iden;
    for(int i=0; i<f.getParams().size(); i++){
        ss<<f.getParams()[i].getValue();
    }
    for(int i=0; i<dupcheck.size(); i++){
        if(ss.str()==dupcheck[i]){
            return;
        }
    }
    //std::cout<<ss.str()<<std::endl;
    dupcheck.push_back(ss.str());
    facts.push_back(f);
}

void Datalogue::addRule(Rule r){
    addDomain(r.getPred().getParams());
    rules.push_back(r);
}

void Datalogue::addQuery(Predicate q){
    queries.push_back(q);
}

std::string Datalogue::schemes_to_string(){
    std::stringstream out;
    out<<"Schemes("<<schemes.size()<<"):\n";
    for(int i=0; i<schemes.size(); i++){
        out<<"  "<<schemes[i].toString()<<"\n";
    }
    return out.str();
}

std::string Datalogue::facts_to_string(){
    std::stringstream out;
    out<<"Facts("<<facts.size()<<"):\n";
    for(int i=0; i<facts.size(); i++){
        out<<"  "<<facts[i].toString()<<".\n";
    }
    return out.str();
}

std::string Datalogue::rules_to_string(){
    std::stringstream out;
    out<<"Rules("<<rules.size()<<"):\n";
    for(int i=0; i<rules.size(); i++){
        out<<"  "<<rules[i].toString()<<"\n";
    }
    return out.str();
}

std::string Datalogue::queries_to_string(){
    std::stringstream out;
    out<<"Queries("<<queries.size()<<"):\n";
    for(int i=0; i<queries.size(); i++){
        out<<"  "<<queries[i].toString()<<"?\n";
    }
    return out.str();
}

std::string Datalogue::domain_to_string(){
    std::stringstream out;
    std::set<std::string>::iterator iters;
    out<<"Domain("<<d.size()<<"):";
    for(iters=d.begin(); iters!=d.end(); iters++){
        out<<"\n  "<<*iters;
    }
    return out.str();
}

std::string Datalogue::toString(){
    std::stringstream out;
    //creat tostrings for everything.
    out<<schemes_to_string();
    out<<facts_to_string();
    out<<rules_to_string();
    out<<queries_to_string();
    out<<domain_to_string();
    return out.str();
}

void Datalogue::addDomain(std::vector<Parameter> l){
    for(int i=0; i<l.size(); i++){
        if(l[i].getType()=="STRING"){
            d.insert(l[i].getValue());
        }
    }
}
