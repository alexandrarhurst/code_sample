//
//  main.cpp
//  lab2.cpp
//
//  Created by Alexandra Greenwood on 9/24/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <array>
#include "readin.h"
#include "tokens.h"
#include "parser.h"
#include "predicate.h"
#include "parameter.h"
#include "rule.h"
#include "datalogue.h"
#include "scheme.h"
#include "tuple.h"
#include "Relation.h"
#include "Database.h"
#include "graph.h"


int main(int argc, char* argv[]) {

    std::string filename=argv[1];
        Readin parsing=Readin(filename);
        parsing.analysis();
        std::stringstream output;
        std::vector<Token> tokenvect= parsing.getTokens();
        
        try{
            Parser p=Parser(tokenvect);
            Datalogue d= p.getData();
            Database data;
            //Graph g;
            //std::cout<<"LOADING"<<std::endl;
            data.load(d.schemes, d.facts, d.queries, d.rules);
            //g.createGraph(d.queries, d.rules);
            //data.optimizedQuery();
            data.runQuery();
            
        }catch(std::string s){
            std::cout<<"FAILURE"<<std::endl;
        }
    
    return 0;
}
