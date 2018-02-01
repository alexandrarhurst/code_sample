//
//  readin.cpp
//  lab1.cpp
//
//  Created by Alexandra Hurst on 9/24/17.
//  Copyright © 2017 Alexandra Hurst. All rights reserved.
//

#include "readin.h"
#include <typeinfo>
#include <fstream>

void Readin::readFile(std::string filename){
    std::ifstream infile(filename);
    std::string content((std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>() ));
    this->input=content;
    //std::cout<<content<<std::endl;
}

std::vector<Token> Readin::analysis(){
    this->total_lines=1;
    char c;
    int i=0;
    //std::cout<<this->input[0]<<std::endl;
    while(i<(this->input).length()){
        c=(this->input)[i];
        //std::cout<<this->input[i]<<i<<std::endl;
        //switch cases
        switch (c){
            case '\n':
                this->total_lines++;
                break;
            case ' ':
                break;
            case '(':
                tokens.push_back(Token("LEFT_PAREN", "(", this->total_lines));
                break;
            case ')':
                tokens.push_back(Token("RIGHT_PAREN", ")", this->total_lines));
                break;
            case '*':
                tokens.push_back(Token("MULTIPLY", "*", this->total_lines));
                break;
            case '+':
                tokens.push_back(Token("ADD", "+", this->total_lines));
                break;
            case '?':
                tokens.push_back(Token("Q_MARK", "?", this->total_lines));
                break;
            case '.':
                tokens.push_back(Token("PERIOD", ".", this->total_lines));
                break;
            case ',':
                tokens.push_back(Token("COMMA", ",", this->total_lines));
                break;
            case ':':
                if((this->input)[i+1]=='-'){
                    i+=1;
                    tokens.push_back(Token("COLON_DASH", ":-", this->total_lines));
                    break;
                }
                tokens.push_back(Token("COLON", ":", this->total_lines));
                break;
            case '#':
                if((this->input)[i+1]=='|'){
                    i+=1;
                    i=this->block_comment(i)+1;
                    break;
                }else{
                    i=this->line_comment(i);
                    break;
                }
            case '\'':
                i=this->alphastring(i+1);
                break;
            default:
                if(isalpha(c)){
                    i=this->alpha(i);
                }else{
                    //std::cout<<std::string(1,c)<<std::endl;
                    tokens.push_back(Token("UNDEFINED", std::string(1,c), this->total_lines));
                }
        }
        i+=1;
    }
    tokens.push_back(Token("EOF", "", this->total_lines));
    return tokens;
}


int Readin::alphastring(int i){
    std::string x="\'";
    int start=this->total_lines;
    while(true){
        if((this->input)[i]=='\n'){
            i+=1;
            x+='\n';
            this->total_lines++;
        }
        if((this->input)[i]=='\''){
            if((this->input)[i+1]=='\''){
                x+=(this->input)[i];
                i+=1;
            }else{
                i+=1;
                break;
            }
        }
        
        if(i>=(this->input).length()){
            tokens.push_back(Token("UNDEFINED",x, start));
            return i;
        }
        x+=(this->input)[i];
        i+=1;
    }
    x+="\'";
    i--;
    tokens.push_back(Token("STRING",x, start));
    return i;
    }

int Readin::alpha(int i){
    std::string x="";
    while(isalnum((this->input)[i])){
        if(!isalnum((this->input)[i+1])){
            x+=(this->input)[i];
            i+=1;
            break;
        }
        if(isspace((this->input)[i])){
            i+=1;
            break;
        }
        x+=(this->input)[i];
        i+=1;
    }
    if(x=="Schemes"){
        tokens.push_back(Token("SCHEMES",x, this->total_lines));
    }else if(x=="Facts"){
        tokens.push_back(Token("FACTS",x, this->total_lines));
    }else if(x=="Rules"){
        tokens.push_back(Token("RULES",x, this->total_lines));
    }else if(x=="Queries"){
        tokens.push_back(Token("QUERIES",x, this->total_lines));
    }else{
        tokens.push_back(Token("ID",x, this->total_lines));}
    i--;
    return i;
}

int Readin::block_comment(int i){
    std::string x="#";
    char c;
    int start=this->total_lines;
    while(true){
        c=(this->input)[i];
        if(i>=(this->input).length()){
            tokens.push_back(Token("UNDEFINED", x, start));
            break;
        }
        if(c=='\n'){
            this->total_lines++;
        }
        if(c=='|' && (this->input)[i+1]=='#'){
            //tokens.push_back(Token("COMMENT", x+="|#", start));
            break;
        }else{
            x+=c;
        }
        i+=1;
    }
    return i;
}

int Readin::line_comment(int i){
    std::string x="#";
    char c;
    while(true){
        i+=1;
        if(i>=(this->input).length()){
            this->total_lines+=1;
            break;
        }
        c=(this->input)[i];
        if(c=='\n'){
            break;
        }else if(this->total_lines>=(this->input).length()){
            break;
        }
        x+=c;
    }
    //tokens.push_back(Token("COMMENT", x, this->total_lines));
    this->total_lines++;
    return i;
}

std::vector<Token> Readin::getTokens(){
    return tokens;
}




