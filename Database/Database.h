#pragma once
#include <iostream>
#include <string>

class Database{
public:
    Database(){
        std::cout<<"Database creted\n";
    }
    ~Database(){
        std::cout<<"Database destroyed\n";
    }
    std::string ExecuteQuery(const std::string& sql){
        std::cout<<"Executing SQL: "
            <<sql<<"\n";
        return "Success";
    }
};