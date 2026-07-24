#pragma once
#include <boost\asio.hpp>
#include <boost\beast.hpp>
#include <random>
#include <memory>


#include "IMarketPriceGenerator.h"
#include "IMarketDataService.h"

class MarketPriceGenerator:public IMarketPriceGenerator,
    public std::enable_shared_from_this<MarketPriceGenerator>{
    boost::asio::steady_timer m_timer;
    IMarketDataService& m_dataService;
    std::mt19937 m_rng;
    std::uniform_real_distribution<double> m_delta;
    std::atomic_bool m_runnnig{false};
    void Schedule();
    void OnTimer(const boost::system::error_code& ec);
    void GeneratePrice();
public:
    MarketPriceGenerator(boost::asio::io_context& ioc,IMarketDataService& dataService);
    void Start()override;
    void End()override;
};