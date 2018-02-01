//
//  Database.cpp
//  lab2
//
//  Created by Alexandra Greenwood on 10/21/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#include "Database.h"


void Database::addRelation(Relation r){
    //std::cout<<r.getName()<<std::endl;
    m.insert(std::pair<std::string, Relation>(r.getName(), r));
}

void Database::load(std::vector<Predicate> i, std::vector<Predicate> j, std::vector<Predicate> k, std::vector<Rule> r){
    //std::cout<<"LOADING"<<std::endl;
    schemes=i;
    facts=j;
    queries=k;
    rules=r;
    
    for(int u=0; u<schemes.size(); u++){
        Relation w;
        std::string temp=i[u].getID();
        std::vector<Parameter> othertemp=i[u].getParams();
        Scheme brexlyn;
        brexlyn.addParams(othertemp);
        w.setName(temp);
        w.setScheme(brexlyn);
        addRelation(w);
        
    }
    //std::cout<<"UNO"<<std::endl;
    for(int u=0; u<j.size(); u++){
        //std::cout<<u<<" "<<j.size()<<std::endl;
        //these variables shall be named after bad utah names
        Tuple tee;
        std::string fingname=j[u].getID();
        std::vector<Parameter> fingparams=j[u].getParams();
        std::vector<std::string> fingstrings;
        for(int v=0; v<fingparams.size(); v++){
            std::string ainzlee=fingparams[v].getValue();
            //std::cout<<ainzlee<<std::endl;
            fingstrings.push_back(ainzlee);
        }
        tee.list=fingstrings;
        tee.setName(fingname);
        addToRelation(tee);
    }
    g.createGraph(queries, rules);
    g.printGraph();
    g.backward();
    //g.printBackward();
    int w=0;
    for(std::map<std::string, Node>::iterator it= g.theGraph.begin(); it!=g.theGraph.end(); it++){
        std::string temp = it->first;
        if(g.backGraph[temp].visited==false){
            w=0;
            g.depthFirst(temp);
            g.ruleOrder(temp,w);
            g.reset();
        }
        
        w++;
        g.post=0;
        //reset();
    }
    //g.printPost();
    int iter  = 0;
    std::vector<std::vector<std::string>> components = g.SCC();
    std::cout<<"Rule Evaluation"<<std::endl;
    for(int i=0; i<components.size(); i++){
        std::stringstream ss;
        iter = 1;
        std::set<std::string> comp(components[i].begin(), components[i].end());
        if(components[i].size()==1 && !g.theGraph[components[i][0]].adjacent.count(components[i][0])){
            run_rule(g.ruleMap[components[i][0]]);
            std::cout<<1<<" passes: "<<components[i][0]<<std::endl;
            continue;
        }else{
            int rounds = fixed(comp);
            int temp=0;
            std::cout<<rounds<<" passes: ";
            for(std::set<std::string>::iterator it=comp.begin(); it!=comp.end(); it++){
                std::cout<<*it;
                if(temp!=comp.size()-1){
                    std::cout<<",";
                }
                temp++;
            }
            std::cout<<"\n";
        }
    }
    std::cout<<"\n";
}

int Database::totalTups(){
    int tups = 0;
    for(std::map<std::string, Relation>::iterator it=m.begin(); it!=m.end(); it++){
        tups += it->second.data.size();
    }
    //std::cout<<tups<<" "<<relations.size()<<std::endl;
    return tups;
}

int Database::fixed(std::set<std::string> r){
    int tups = totalTups();
    int last = -1;
    int iters = 0;
    while(tups!=last){
        for(std::set<std::string>::iterator it=r.begin(); it!=r.end(); it++){
            run_rule(g.ruleMap[*it]);
        }
        last = tups;
        tups = totalTups();
        iters++;
    }
    return iters;
}

bool Database::run_rule(Rule r){
    Predicate head = r.getPred();
    std::vector<Predicate> predlist=r.predicateList;
    Relation join_result;
    for(int i=0; i<predlist.size(); i++){
        std::string name = predlist[i].iden;
        Relation op = m[name];
        Relation query_result = relationQuery(predlist[i]);
        //query_result.printRelation();
        if(i==0){
            join_result=query_result;
        }else{
            join_result = join_result.naturalJoin(join_result, query_result);
            //join_result.printRelation();
        }
    }
    //join_result.printRelation();
    std::string paramlist = head.getID();
    std::vector<Parameter> p = head.getParams();
    for(int i=0; i<p.size(); i++){
        if(p[i].getType()=="ID"){
            ids.push_back(p[i].getValue());
        }
    }
    for(int i=0; i<ids.size(); i++){
        for(int j=0; j<join_result.scheme2.getParams().size(); j++){
            if(ids[i]==join_result.scheme2.getParams()[j].getValue()){
                pos.push_back(j);
            }
        }
    }
    //std::cout<<"Rule proj"<<std::endl;
    Relation proj_result = join_result.project(pos);
    //proj_result.printRelation();
    std::string origin_name = head.iden;
    //std::cout<<origin_name<<std::endl;
    Relation origin = m[origin_name];
    Relation rename = proj_result.rename(ids);
    int before = origin.data.size();
    Relation un_res = origin.relational_union(rename);
    //std::cout<<"AAAAAAH"<<std::endl;
    //un_res.printRelation();
    std::map<std::string,Relation>::iterator it = m.find(origin_name);
    if(it != m.end())
    {
        //it->second.printRelation();
        m[it->first].data = un_res.data;
    }
    else{
        //std::cout<<"ERROR"<<std::endl;
        m.at(origin_name)=un_res;
    }
    //std::cout<<"AAA"<<std::endl;
    //m[origin_name].printRelation();
    ids.clear();
    pos.clear();
    if (un_res.data.size() !=before){
        return true;
    }
    
    return false;
}


void Database::addToRelation(Tuple t){
    std::string currentname=t.getName();
    //std::cout<<"B"<<t.getName()<<std::endl;
    Relation current = m.find(currentname)->second;
    current.addTuple(t);
    m.at(currentname)=current;
}

std::string Database::toString(){
    //do I need a "to print" array?
    return "";
}

Relation Database::relationQuery(Predicate q){
    std::string param_list=q.getID();
    std::vector<Parameter> p=q.getParams();
    Relation tempy=m[param_list];
    for(int j=0; j<p.size(); j++){
        //std::cout<<j<<" "<<p[j].getType()<<std::endl;
        bool dups=false;
        int possy=0;
        if(p[j].getType()=="STRING"){
            //std::cout<<p[j].getValue()<<std::endl;
            tempy=tempy.select(j,p[j].getValue());
        }else if(p[j].getType()=="ID"){
            //std::cout<<"W "<<p[j].getValue()<<" "<<ids.size()<<std::endl;
            for(int k=0; k<ids.size(); k++){
                //std::cout<<"A"<<p[j].getValue()<<" "<<ids[k]<<std::endl;
                if(ids[k]==p[j].getValue()){
                    //std::cout<<"HI"<<std::endl;
                    dups=true;
                    possy=k;
                }
            }
            
            if(dups==true){
                //std::cout<<"HI"<<possy<<" "<<j<<std::endl;
                tempy=tempy.select(possy, j);
            }else{
                //std::cout<<p[j].getValue()<<std::endl;
                ids.push_back(p[j].getValue());
                pos.push_back(j);
            }
        }
    }
    
    //this is my leave off point from saturday.
    tempy=tempy.project(pos);
    tempy=tempy.rename(ids);
    ids.clear();
    pos.clear();
    return tempy;

}

void Database::optimizedQuery(){
    Graph g;
    g.createGraph(queries, rules);
    g.printGraph();
    g.backward();
    g.reset();
    int i=0;
    for(std::map<std::string, Node>::iterator it= g.backGraph.begin(); it!=g.backGraph.end(); it++){
        std::string temp = it->first;
        if(g.backGraph[temp].visited==false){
            i=0;
            g.depthFirst(temp);
            //std::cout<<temp<<std::endl;
        }
        g.ruleOrder(temp,i);
        i++;
        g.post=0;
        //reset();
    }
    g.reset();
    std::vector<std::vector<std::string>> components = g.SCC();
    for(int i=0; i<queries.size(); i++){
        std::cout<<queries[i].getID()<<"(";
        std::string name = queries[i].getID();
        std::vector<Parameter> p=queries[i].getParams();
        Relation tempy=(m.find(queries[i].getID()))->second;
        for(int j=0; j<p.size(); j++){
            std::cout<<p[j].getValue();
            if(j<p.size()-1){
                std::cout<<", ";
            }
        }
        std::cout<<")? ";
        for(int j=0; j<p.size(); j++){
            //std::cout<<j<<" "<<p[j].getType()<<std::endl;
            bool dups=false;
            int possy=0;
            if(p[j].getType()=="STRING"){
                //std::cout<<p[j].getValue()<<std::endl;
                tempy=tempy.select(j,p[j].getValue());
                if(tempy.name=="ERROR"){
                    std::cout<<"No"<<std::endl;
                    return;}
            }else if(p[j].getType()=="ID"){
                //std::cout<<"W "<<p[j].getValue()<<" "<<ids.size()<<std::endl;
                for(int k=0; k<ids.size(); k++){
                    //std::cout<<"A"<<p[j].getValue()<<" "<<ids[k]<<std::endl;
                    if(ids[k]==p[j].getValue()){
                        //std::cout<<"HI"<<std::endl;
                        dups=true;
                        possy=k;
                    }
                }
                
                if(dups==true){
                    //std::cout<<"HI"<<possy<<" "<<j<<std::endl;
                    tempy=tempy.select(possy, j);
                }else{
                    //std::cout<<p[j].getValue()<<std::endl;
                    ids.push_back(p[j].getValue());
                    pos.push_back(j);
                }
            }
        }
        tempy=tempy.project(pos);
        tempy=tempy.rename(ids);
        int num=tempy.countTuples(pos,ids);
        if(tempy.data.size()>0) {
            std::cout<<"Yes("<<num<<")"<<std::endl;
            tempy.printTuples(pos, ids,num);
        }else{
            std::cout<<"No"<<std::endl;
        }
        
        ids.clear();
        pos.clear();
        
        
        
        std::string cue = "Q"+std::to_string(i);
        g.depthFirst(cue);
        for(std::set<std::string>::iterator it=g.theGraph[cue].adjacent.begin(); it!=g.theGraph[cue].adjacent.end(); it++){
            std::cout<<*it<<std::endl;
        }
    }
}

void Database::runQuery(){
    Relation r;
    std::cout<<"Query Evaluation"<<std::endl;
    //each query
    for(int i=0; i<queries.size(); i++){
        //std::cout<<queries[i].toString()<<std::endl;
        std::string zella=queries[i].getID();
        std::vector<Parameter> p=queries[i].getParams();
        Relation tempy=(m.find(zella))->second;
        r=tempy;
        //number of variables in the scheme.
        std::stringstream ss;
        for(int j=0; j<p.size(); j++){
            ss<<p[j].getValue();
            if(j<(p.size()-1)){
                ss<<",";
            }
            //std::cout<<p[j].getValue()<<std::endl;
        }
        for(int j=0; j<p.size(); j++){
            //std::cout<<j<<" "<<p[j].getType()<<std::endl;
            bool dups=false;
            int possy=0;
            if(p[j].getType()=="STRING"){
                //std::cout<<p[j].getValue()<<std::endl;
                tempy=tempy.select(j,p[j].getValue());
                if(tempy.name=="ERROR"){
                    std::cout<<zella<<"("<<ss.str()<<")? ";
                    std::cout<<"No"<<std::endl;
                    return;}
            }else if(p[j].getType()=="ID"){
                //std::cout<<"W "<<p[j].getValue()<<" "<<ids.size()<<std::endl;
                for(int k=0; k<ids.size(); k++){
                    //std::cout<<"A"<<p[j].getValue()<<" "<<ids[k]<<std::endl;
                    if(ids[k]==p[j].getValue()){
                        //std::cout<<"HI"<<std::endl;
                        dups=true;
                        possy=k;
                    }
                }
                
                if(dups==true){
                    //std::cout<<"HI"<<possy<<" "<<j<<std::endl;
                    tempy=tempy.select(possy, j);
                }else{
                    //std::cout<<p[j].getValue()<<std::endl;
                    ids.push_back(p[j].getValue());
                    pos.push_back(j);
                }
            }
        }
    
        //this is my leave off point from saturday.
        tempy=tempy.project(pos);
        tempy=tempy.rename(ids);
        //std::cout<<"B"<<std::endl;
        
        int num=tempy.countTuples(pos,ids);
        std::cout<<zella<<"("<<ss.str()<<")? ";
        if(tempy.data.size()>0) {
            std::cout<<"Yes("<<num<<")"<<std::endl;
            tempy.printTuples(pos, ids,num);
        }else{
            std::cout<<"No"<<std::endl;
        }
        
        ids.clear();
        pos.clear();
    }
}


