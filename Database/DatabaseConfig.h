#pragma once
#include <boost/di.hpp>
#include <string>

struct  host{};
struct  port{}; //{5432};
struct  database{};//{"riskdb"};
struct  user{};//{"postgres"};
struct  password{};//{"1Qazwsxedc@"};
struct  POOLSIZE{};
struct ServerPort{};

    

class DataBaseConfig{
public:
    std::string m_host;
    std::uint16_t m_port{}; //{5432};
    std::string m_database;//{"riskdb"};
    std::string m_user;//{"postgres"};
    std::string m_password;//{"1Qazwsxedc@"};
    std::size_t m_poolsize;//{"1Qazwsxedc@"};
    unsigned short m_hport{};
    
        BOOST_DI_INJECT(DataBaseConfig,(named=ServerPort{})unsigned short sport  ,(named = host{}) std::string host,
        (named = port{}) std::uint16_t port,(named = database{}) std::string database,(named = user{}) std::string user, (named = password{})std::string password,
            (named = POOLSIZE{})std::size_t poolsize):m_hport(sport),m_host(std::move(host)),m_port(port),m_database(database),m_user(user),
            m_password(password),m_poolsize(poolsize){}        
};

// CREATE DATABASE riskdb template postgres;