//
//  Relation.cpp
//  lab2
//
//  Created by Alexandra Greenwood on 10/21/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#include "Relation.h"

std::string Relation::getName(){
    return name;
}

void Relation::setName(std::string s){
    name=s;
}

void Relation::addTuple(Tuple t){
    data.insert(t);
}

Scheme Relation::getScheme(){
    return scheme2;
}

void Relation::setScheme(Scheme s){
    scheme2=s;
}

Relation Relation::select(int i, std::string s){
    Relation err;
    err.name="ERROR";
    //std::cout<<"SELECT1"<<std::endl;
    Relation rel;
    rel.name=name;
    rel.scheme2=scheme2;
    Tuple tee;
    for(std::set<Tuple>::iterator iter=data.begin(); iter!=data.end(); iter++){
        tee=*iter;
        //std::cout<<"BYE"<<std::endl;
        try{
            if(tee.list[i]==s){
                //std::cout<<"AL"<<std::endl;
                rel.addTuple(tee);
            }
        }catch(...){
            return err;
        }
        
        //std::cout<<"AGAIN"<<std::endl;
        
    }
    return rel;
}

Relation Relation::select(int i, int j){
    //std::cout<<"SELECT2"<<std::endl;
    Relation rel;
    rel.name=name;
    rel.scheme2=scheme2;
    Tuple tee;
    for(std::set<Tuple>::iterator iter=data.begin(); iter!=data.end(); iter++){
        tee= *iter;
        if(tee.list[i]==tee.list[j]){
            rel.addTuple(tee);
        }
    }
    return rel;
}

Relation Relation::project(std::vector<int> p){
    Relation r;
    r.name=name;
    r.scheme2=scheme2;
    Tuple proj;
    int projint;
    
    for(std::set<Tuple>::iterator iter=data.begin(); iter!=data.end(); iter++){
        //std::cout<<"PROJECT"<<std::endl;
        Tuple temp;
        temp= *iter;
        for(int i=0; i<p.size(); i++){
            projint=p[i];
            //std::cout<<temp.list[projint]<<std::endl;
            proj.list.push_back(temp.list[projint]);
        }
        r.data.insert(proj);
        proj.list.clear();
    }
    return r;
}

Relation Relation::rename(std::vector<std::string> input){
    //std::cout<<"RENAME"<<std::endl;
    Relation r;
    r.name=name;
    r.data=data;
    r.scheme2.setParams(input);
    return r;
}

int Relation::countTuples(std::vector<int> pos, std::vector<std::string> ids){
    int count=0;
    for(std::set<Tuple>::iterator iter=data.begin(); iter!=data.end(); iter++){
        Tuple temp= *iter;
        std::stringstream ss;
        for(int i=0; i<temp.list.size(); i++){
            count++;
        }
    }
    if(count>0) {
        return count/ids.size();
    }else{
        return 1;
    }
}

void Relation::printTuples(std::vector<int> pos, std::vector<std::string> ids, int num){
    //std::stringstream ss;
    for(std::set<Tuple>::iterator iter=data.begin(); iter !=data.end(); iter++){
        //int i=ite
        Tuple temp=*iter;
        int s=ids.size();
        //std::cout<<s<<std::endl;
        for(int i=0; i<temp.list.size(); i++){
            if(i%s==0){
                std::cout<<"  ";
            }
            std::cout<<ids[i%pos.size()] <<"="<<temp.list[i];
            if((i+1)%s==0){
                std::cout<<"\n";
            }else{
                std::cout<<", ";
            }
            //std::cout<<ids[(i+1)%pos.size()]<<"="<<temp.list[i+1]<<std::endl;
        }
    }
}

Relation Relation::naturalJoin(Relation r1, Relation r2){
    //std::cout<<"JOIN"<<std::endl;
    Relation temp;
    Scheme s;
    Tuple t;
    bool add;
    temp.scheme2=r1.scheme2;
    for(int i=0; i<r2.scheme2.getParams().size(); i++){
        add=true;
        for(int j=0; j<r1.scheme2.getParams().size(); j++){
            if(r2.scheme2.getParams()[i].getValue()==r1.scheme2.getParams()[j].getValue()){
                add=false;
                break;
            }
        }
        if(add){
            temp.scheme2.params.push_back(r2.scheme2.params[i]);
        }
    }
    for(std::set<Tuple>::iterator i =r1.data.begin(); i !=r1.data.end(); i++){
        Tuple t1 = *i;
        for(std::set<Tuple>::iterator j=r2.data.begin(); j !=r2.data.end(); j++){
            Tuple t2 = *j;
            if(canJoin(r1.scheme2, r2.scheme2, t1, t2)){
                //r1.printRelation();
                t = join(r1.scheme2, r2.scheme2, t1, t2);
                temp.data.insert(t);
            }
        }
    }
    //temp.printRelation();
    return temp;
}

Tuple Relation::join(Scheme s1, Scheme s2, Tuple t1, Tuple t2){
    Tuple t;
    bool add;
    t.setTuples(t1.list);
    for(int i=0; i<t2.list.size(); i++){
        add = true;
        for(int j=0; j<s1.params.size(); j++){
            if(s2.params[i].getValue()==s1.params[j].getValue()){
                add=false;
                break;
            }
        }
        if(add){
            t.list.push_back(t2.list[i]);
        }
    }
    return t;
}

bool Relation::canJoin(Scheme s1, Scheme s2, Tuple t1, Tuple t2){
    std::string n1, n2;
    std::string a, b;
    for(int i=0; i<s1.params.size(); i++){
        n1=s1.params[i].getValue();
        a=t1.list[i];
        for(int j=0; j<s2.params.size(); j++){
            n2 = s2.params[j].getValue();
            b = t2.list[j];
            if(n1==n2 && a != b){
                return false;
            }
        }
    }
    return true;
}

Relation Relation::relational_union(Relation r2){
    //r2.printAllTuples();
    for(std::set<Tuple>::iterator i= data.begin(); i !=data.end(); i++){
        Tuple temp = *i;
        r2.addTuple(temp);
    }
    return r2;
}

void Relation::printRelation(){
    std::cout<<"Relation: "<<std::endl;
    std::cout<<"name: "<<name<<std::endl;
    scheme2.print();
    printAllTuples();
}

void Relation::printAllTuples(){
    for (std::set<Tuple>::iterator i = data.begin(); i != data.end(); i++){
        //cout << "staring set iterator for loop for printTuple()" << endl;
        Tuple tup = *i;
        tup.print();
    }
}

std::string Relation::ssRelation(){
    std::stringstream ss;
    ss<<scheme2.ss()<<std::endl;
    for(std::set<Tuple>::iterator i=data.begin(); i!=data.end(); i++){
        Tuple tup = *i;
        ss<<getName();
    }
    //std::cout<<(ss.str()).length()<<std::endl;
    return ss.str();
}

