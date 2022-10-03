 
#include <fstream> 
#include "Logger.h"
#include <iostream>

    Logger::Logger()
    {
        
    }
    void Logger::printSales(OrderBookEntry& order, std::string type)
    {
        std::ofstream sales_log;
        sales_log.open ("succesfulSales.txt", std::fstream::app);
        sales_log << " ================" << std::endl;
        sales_log << " Type of Sale: " << type << std::endl;
        sales_log << " TimeStamp: " << order.timestamp << std::endl;
        sales_log << " Products Text: " << order.product << std::endl;
        sales_log << " Price: " << order.price << std::endl;
        sales_log << " Amount: " << order.amount << std::endl;
        sales_log << " ================" << std::endl;
        sales_log.close();

    }

    void Logger::printOffers(OrderBookEntry& order, std::string type)
    {
        
        std::ofstream offers_log;
        offers_log.open ("offersMade.txt", std::fstream::app);
        offers_log << " ================" << std::endl;
        offers_log << " Type of Sale: " << type << std::endl;
        offers_log << " TimeStamp: " << order.timestamp << std::endl;
        offers_log << " Products Text: " << order.product << std::endl;
        offers_log << " Price: " << order.price << std::endl;
        offers_log << " Amount: " << order.amount << std::endl;
        offers_log << " ================" << std::endl;
        offers_log.close();
    }

    void Logger::printAssets(std::string walletContent)
    {
        std::ofstream assets;
        assets.open ("assets.txt", std::fstream::app);
        assets << " ================" << std::endl;
        assets << " " << walletContent << std::endl;
        assets << " ================" << std::endl;
        assets.close();
    }

    void Logger::clearLogsAndAssets()
    {
        std::ofstream offers_log;
        offers_log.open("offersMade.txt", std::ofstream::out | std::ofstream::trunc);
        offers_log.close();

        std::ofstream assets_log;
        assets_log.open("assets.txt", std::ofstream::out | std::ofstream::trunc);
        assets_log.close();

        std::ofstream sales_log;
        sales_log.open("succesfulSales.txt", std::ofstream::out | std::ofstream::trunc);
        sales_log.close();
    }

