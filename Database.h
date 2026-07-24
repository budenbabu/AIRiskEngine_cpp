#pragma once
#include <iostream>

class IDatabase{
public:
    virtual ~IDatabase()=default;
    virtual void Connect()=0;
};

class PrimaryDatabase: public IDatabase{
public:
    void Connect()override{
        std::cout<<"Primary DB\n";
    }
};

class ReplicaDatabase: public IDatabase{
public:
    void Connect()override{
        std::cout<<"ReplicaDatabase DB\n";
    }
};


class Database{
public:
    Database(){
        std::cout<<"Database created\n";
    }
    void Connect(){
        std::cout<<"Connecte to PostgreSQL\n";
    }
    ~Database(){
        std::cout<<"Database destroyed\n";
    }
};