//
//  graph.cpp
//  lab2
//
//  Created by Alexandra Greenwood on 12/3/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#include "graph.h"

void Graph::createGraph(std::vector<Predicate> queries, std::vector<Rule> rules){
    /*for(int i=0; i<queries.size(); i++){
        std::string currentQ = queries[i].iden;
        std::string x = "Q" + std::to_string(i+1);
        queryMap[x]=queries[i];
        Node temp;
        std::set<std::string> currentSet;
        for(int j=0; j<rules.size(); j++){
            std::string currentR = rules[j].getPred().iden;
            std::string y;
            if(currentQ == currentR){
                y = "R" + std::to_string(j+1);
                currentSet.insert(y);
                ruleMap[y]=rules[j];
            }
        }
        temp.adjacent = currentSet;
        theGraph[x] = temp;
    }*/
    for(int i=0; i<rules.size(); i++){
        std::string currentR = rules[i].getPred().iden;
        Node temp;
        std::string x = "R" + std::to_string(i);
        //std::cout<<rules[i].toString()<<std::endl;
        ruleMap[x] = rules[i];
        std::set<std::string> currentSet;
        for(int j=0; j<rules[i].predicateList.size(); j++){
            std::string currentP = rules[i].predicateList[j].getID();
            std::string y;
            for (int k=0; k<rules.size(); k++) {
                std::string ruleHead = rules[k].getPred().iden;
                if(currentP == ruleHead){
                    y = "R" + std::to_string(k);
                    currentSet.insert(y);
                }
            }
        }
        temp.adjacent = currentSet;
        theGraph[x] = temp;
    }
}

void Graph::printGraph(){
    std::cout<<"Dependency Graph"<<std::endl;
    for(std::map<std::string, Node>::iterator it = theGraph.begin(); it!= theGraph.end(); it++){
        if((it->first[0])=='Q'){
            continue;
        }
        std::cout<<it->first<<":";
        Node temp = it->second;
        std::set<std::string> current = temp.adjacent;
        int j=0;
        for(std::set<std::string>::iterator i = current.begin(); i != current.end(); i++){
            std::string s = *i;
            std::cout<<s;
            if(j<current.size()-1){
                std::cout<<",";
            }
            j++;
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

void Graph::depthFirst(std::string s){
    post=0;
    Node temp = backGraph[s];
    std::set<std::string> currentA = temp.adjacent;
    backGraph[s].visited = true;
    
    if(currentA.empty()){
        backGraph[s].postOrder = post;
        post++;
    }else{
        for(std::set<std::string>::iterator it = currentA.begin(); it != currentA.end(); it++){
            std::string x = *it;
            //std::cout<<x<<std::endl;
            if(x!= "" && backGraph[x].visited == false){
                depthFirst(x);
            }
        }
        backGraph[s].postOrder = post;
        post++;
    }
}

void Graph::reset(){
    for(std::map<std::string,Node>::iterator it = backGraph.begin(); it!= backGraph.end(); it++){
        std::string current = it->first;
        backGraph[current].postOrder = 1000000;
        backGraph[current].visited = false;
    }
    post=0;
}

void Graph::printPost(){
    for(int i=0; i<order.size(); i++){
        Node temp = backGraph[order[i]];
        std::cout<<"PONT("<<order[i]<<") = "<<i<<std::endl;
    }
}

void Graph::ruleOrder(std::string s, int i){
    int end = backGraph[s].postOrder;
    //std::cout<<s<<" "<<end<<std::endl;
    int start = 0;
    while(start<end){
        for(std::map<std::string, Node>::iterator it = backGraph.begin(); it!=backGraph.end(); it++){
            std::string name = it->first;
            //std::cout<<name<<std::endl;
            Node n = it->second;
            bool in_there=false;
            for(int j=0; j<order.size(); j++){
                if(it->first==order[j]){
                    in_there=true;
                }
            }
            if(n.postOrder==start&&in_there==false){
                //std::cout<<name<<" "<<start<<std::endl;
                order.push_back(name);
                start++;
            }else if(n.postOrder==start){
                start++;
            }
        }
        //std::cout<<start<<std::endl;
    }
    bool in_there = false;
    for(int j=0; j<order.size(); j++){
        if(s==order[j]){
            in_there=true;
        }
    }
    if(in_there==false){
        order.push_back(s);
    }
    
    /*for(std::map<std::string,Node>::iterator it=backGraph.begin(); it!=backGraph.end(); it++){
        if(backGraph[it->first].postOrder!=1000000){
            //std::cout<<"  "<<it->first<<" "<<it->second.postOrder<<std::endl;
            bool in_there=false;
            for(int j=0; j<order.size(); j++){
                if(it->first==order[j]){
                    in_there=true;
                }
            }
            if(in_there==false && i==it->second.postOrder){
                order.push_back(it->first);
            }
        }
    }*/
    //std::cout<<s<<std::endl;
    //order.push_back(s);
    //backGraph[s].postOrder=0;
}

void Graph::backward(){
    for(std::map<std::string, Node>::iterator it = theGraph.begin(); it!=theGraph.end(); it++){
        std::string name = it->first;
        //std::cout<<name<<std::endl;
        Node n = it->second;
        for(std::set<std::string>::iterator j=n.adjacent.begin(); j!=n.adjacent.end(); j++){
            backGraph[*j].adjacent.insert(name);
        }
    }
}

void Graph::printBackward(){
    for(std::map<std::string, Node>::iterator it = backGraph.begin(); it!= backGraph.end(); it++){
        std::cout<<it->first<<":";
        Node temp = it->second;
        std::set<std::string> current = temp.adjacent;
        for(std::set<std::string>::iterator i = current.begin(); i != current.end(); i++){
            std::string s = *i;
            std::cout<<" "<<s;
        }
        std::cout<<"\n";
    }
}

void Graph::printAll(std::vector<Predicate> queries){
    //printGraph();
    std::cout<<"Reversal Forest"<<std::endl;
    backward();
    printBackward();
    reset();
    int i=0;
    for(std::map<std::string, Node>::iterator it= backGraph.begin(); it!=backGraph.end(); it++){
        std::string temp = it->first;
        if(backGraph[temp].visited==false){
            i=0;
            depthFirst(temp);
            //std::cout<<temp<<std::endl;
        }
        ruleOrder(temp,i);
        i++;
        post=0;
        //reset();
    }
    std::cout<<"Topological Ordering"<<std::endl;
    printPost();
    std::cout<<"Strongly Connected Components"<<std::endl;
    SCC();
}

void Graph::otherDepthFirst(std::string s){
    Node temp = theGraph[s];
    std::set<std::string> currentA = temp.adjacent;
    theGraph[s].visited = true;
    
    if(currentA.empty()){
        theGraph[s].postOrder = post;
        post++;
    }else{
        for(std::set<std::string>::iterator it = currentA.begin(); it != currentA.end(); it++){
            std::string x = *it;
            //std::cout<<x<<std::endl;
            if(x!= "" && theGraph[x].visited == false){
                otherDepthFirst(x);
            }
        }
        theGraph[s].postOrder = post;
        post++;
    }
}


std::vector<std::vector<std::string>> Graph::SCC(){
    std::vector<std::vector<std::string>> components;
    if(theGraph.size()==1){
        std::vector<std::string> subvec;
        subvec.push_back(theGraph.begin()->first);
        components.push_back(subvec);
        return components;
    }
    std::set<std::string> added;
    for(int i=0; i<order.size(); i++){
        std::string start = order[order.size()-1-i];
        if(theGraph[start].visited==true){
            continue;
        }
        otherDepthFirst(start);
        std::vector<std::string> subvec;
        subvec.push_back(start);
        added.insert(start);
        for(std::map<std::string,Node>::iterator j=theGraph.begin(); j!= theGraph.end(); j++){
            if(!added.count(j->first)){
                if(j->second.postOrder!=1000000){
                subvec.push_back(j->first);
                added.insert(j->first);
                }
            }
        }
        components.push_back(subvec);
    }
    for(int i=0; i<components.size(); i++){
        //std::cout<<"{";
        for(int j=0; j<components[i].size(); j++){
            //std::cout<<components[i][j];
            if(j<components[i].size()-1){
                //std::cout<<", ";
            }
        }
        //std::cout<<"}\n";
    }
    return components;
}






