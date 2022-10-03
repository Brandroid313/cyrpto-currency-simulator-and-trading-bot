#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include <string>
#include <fstream>
#include <iostream>

class Logger
{
    public:

        Logger();

        /** R4C: Record of succesful bids and asks made */
        static void printSales(OrderBookEntry& order, std::string type);

        /** R4A: Record of the assets and their changes */
        static void printAssets(std::string walletContent);

        /** R4B: Record of all Bids and asks Made */
        static void printOffers(OrderBookEntry& order, std::string type);

        /** clears the logs at the beging of every new start of the bot */
        static void clearLogsAndAssets();
 
};