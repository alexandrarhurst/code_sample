//
//  parser.cpp
//  lab1.cpp
//
//  Created by Alexandra Greenwood on 9/29/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#include "parser.h"
#include <string>
#include <iostream>


bool Parser::match(std::string thing){
    //std::cout<<thing<<" "<<t.getType()<<" "<<t.getValue()<<std::endl;
    if(thing==t.getType()){
        this->index++;
        t=tokens[index];
        return true;
    }else{
        std::cout<<"Failure!"<<std::endl;
        std::cout<<"  "<<t.toString()<<std::endl;
        throw t.toString();
    }
    return false;
}

void Parser::parseDatalog(){
    match("SCHEMES");
    match("COLON");
    parseScheme();
    parseSchemeList();
    match("FACTS");
    match("COLON");
    parseFact();
    parseFactList();
    match("RULES");
    match("COLON");
    parseRule();
    parseRuleList();
    match("QUERIES");
    match("COLON");
    parseQuery();
    parseQueryList();
}

void Parser::parseScheme(){
    //std::cout<<"Parse scheme"<<std::endl;
    p=Predicate(t.getValue());
    
    //finish later.
    match("ID");
    match("LEFT_PAREN");
    p.addParam(Parameter(t.getType(), t.getValue()));
    match("ID");
    if(t.getType()=="COMMA"){
        parseIDList();
    }
    match("RIGHT_PAREN");
    d.addScheme(p);
}

void Parser::parseSchemeList(){
    if(t.getType()=="ID"){
        parseScheme();
        parseSchemeList();
    }
}

void Parser::parseFact(){
    //std::cout<<"Parse fact"<<std::endl;
    //std::cout<<t.getType()<<std::endl;
    if(t.getType()=="ID"){
    p=Predicate(t.getValue());
    match("ID");
    match("LEFT_PAREN");
    //finish later.
    if(t.getType()=="STRING"){
        p.addParam(Parameter(t.getType(), t.getValue()));
    }
    match("STRING");
    if(t.getType()=="COMMA"){
        parseStringList();
    }
    match("RIGHT_PAREN");
    match("PERIOD");
    d.addFact(p);
    }
}

void Parser::parseFactList(){
    if(t.getType()=="ID"){
        parseFact();
        parseFactList();
    }
}

void Parser::parseRule(){
    //std::cout<<"RULE"<<std::endl;
    if(t.getType()!="QUERIES"){
    parseHeadPredicate();
    r=Rule(p);
    match("COLON_DASH");
    parsePredicate();
    if(t.getType()=="COMMA"){
        parsePredicateList();
    }
    match("PERIOD");
    d.addRule(r);
    }
}

void Parser::parseRuleList(){
    if(t.getType()=="ID"){
        parseRule();
        parseRuleList();
    }
}

void Parser::parseQuery(){
        p=Predicate(t.getValue());
        parsePredicate();
        match("Q_MARK");
        d.addQuery(p);
}

void Parser::parseQueryList(){
    if(t.getType()=="ID"){
        parseQuery();
        parseQueryList();
    }
}

void Parser::parseStringList(){
    //std::cout<<"String List"<<std::endl;
    match("COMMA");
    if(t.getType()=="STRING"){
        p.addParam(Parameter(t.getType(),t.getValue()));
    }
    match("STRING");
    if(t.getType()=="COMMA"){
        parseStringList();
    }
}

void Parser::parseParameter(){
    if(t.getType()=="ID"||t.getType()=="STRING"){
        //also fix this
        //std::cout<<t.getValue()<<std::endl;
        p.addParam(Parameter(t.getType(), t.getValue()));
        match(t.getType());
    }
    if(t.getType()=="LEFT_PAREN"){
        //std::cout<<t.getValue()<<std::endl;
        parseExpression();
    }
}

void Parser::parseParameterList(){
    match("COMMA");
    parseParameter();
    if(t.getType()=="COMMA"){
        parseParameterList();
    }
}

void Parser::parseIDList(){
    //std::cout<<"Parse ID"<<std::endl;
    match("COMMA");
    if(t.getType()=="ID"){
        //fill in later
        //std::cout<<"HELLO"<<std::endl;
        p.addParam(Parameter(t.getType(),t.getValue()));
    }match("ID");
    if(t.getType()=="COMMA"){
        parseIDList();
    }
}

//this is where I need to fix
void Parser::parseHeadPredicate(){
    //std::cout<<"Head Pred"<<std::endl;
    p=Predicate(t.getValue());
    match("ID");
    match("LEFT_PAREN");
    if(t.getType()=="ID"){
        p.addParam(Parameter(t.getType(),t.getValue()));
    }
    match("ID");
    if(t.getType()=="COMMA"){
        parseIDList();
    }
    match("RIGHT_PAREN");
}

void Parser::parsePredicate(){
    //std::cout<<"Parse pred"<<std::endl;
    p=Predicate(t.getValue());
    match("ID");
    match("LEFT_PAREN");
    parseParameter();
    /*if(t.getType()=="ID"){
        p.addParam(Parameter(t.getType(),t.getValue()));
    }
    match("ID");*/
    if(t.getType()=="COMMA"){
        parseParameterList();
    }
    match("RIGHT_PAREN");
    r.addPredicate(p);
}

void Parser::parsePredicateList(){
    match("COMMA");
    parsePredicate();
    if(t.getType()=="COMMA"){
        parsePredicateList();
    }
}

void Parser::parseExpression(){
    //this isn't working
    std::string in="(";
    int paren=1;
    match("LEFT_PAREN");
    while(paren>0){
        //std::cout<<in<<std::endl;
        if(t.getType()=="ID"||t.getType()=="STRING"){
            //std::cout<<t.getValue()<<std::endl;
            in+=t.getValue();
            match(t.getType());
        }
        if(t.getType()=="ADD"||t.getType()=="MULTIPLY"){
            //std::cout<<in<<std::endl;
            in+=parseOperator();
            if(t.getType()=="ADD"||t.getType()=="MULTIPLY"){
                std::cout<<"Failure!"<<std::endl;
                std::cout<<"  "<<t.toString()<<std::endl;
                throw t.toString();
            }
        }
        //std::cout<<in<<std::endl;
        if(t.getType()=="LEFT_PAREN"){
            match("LEFT_PAREN");
            in+="(";
            paren++;
        }else{
            //std::cout<<in<<std::endl;
            if(t.getType()=="RIGHT_PAREN"){
                match("RIGHT_PAREN");
                in+=")";
                paren--;
            }else if(t.getType()=="STRING"||t.getType()=="ID"){
                //std::cout<<t.getValue()<<std::endl;
                in+=t.getValue();
                match(t.getType());
            }
            else{
                in+=parseOperator();
                if(t.getType()=="ADD"||t.getType()=="MULTIPLY"){
                    std::cout<<"Failure!"<<std::endl;
                    std::cout<<"  "<<t.toString()<<std::endl;
                    throw t.toString();
                }
            }
        }
        if(t.getType()=="RIGHT_PAREN"){
            match("RIGHT_PAREN");
            in+=")";
            paren--;
            //std::cout<<in<<" "<<paren<<std::endl;
        }
    }
    p.addParam(Parameter("ID",in));
}

std::string Parser::parseOperator(){
    if(t.getType()=="ADD"){
        match("ADD");
        return "+";
    }else{
        match("MULTIPLY");
        return "*";
    }
}

Datalogue Parser::getData(){
    return d;
}

