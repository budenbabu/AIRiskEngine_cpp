#pragma once
#include <string>
#include <iostream>

class Portfolio{
    int m_portfolioId{};
    std::string m_owner;
    float m_balance{};
public:
    Portfolio(int portfoliId,std::string owner,float balence):
        m_portfolioId(portfoliId),m_owner(std::move(owner)),m_balance(balence){}
    int PortfolioId()const{ return m_portfolioId;}
    const std::string& Owner() const{ return m_owner;}
    void SetBalance(float balance);
    float Balance()const{ return m_balance;}
};