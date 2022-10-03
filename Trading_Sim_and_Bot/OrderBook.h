#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
    public:
        /** construct, reading a csv data file */
        OrderBook(std::string filename);

        std::vector<std::string> getKnownProducts(std::string currentTime);
        /** return vector of Orders according to the sent filters*/
        std::vector<OrderBookEntry> getOrders(OrderBookType type, 
                                              std::string product, 
                                              std::string timestamp);
        /** returns the earliest time in the orderbook*/
        std::string getEarliestTime();

        /** return the latest time in the orderbook*/
        std::string getLastestTime();

        /** returns the next time after the 
         * sent time in the orderbook  
         * If there is no next timestamp, wraps around to the start
         * */
        std::string getNextTime(std::string timestamp);

        /** gets the last time step  */
        std::string getPreviousTime(std::string timestamp);

        void insertOrder(OrderBookEntry& order);

        /** R2D, R3D & Challenge requirement part 2: erases 
         * old orders after a we have passed two time frames
         * to save on memory and iterations; also 
         * Orders and asks that have been in too long are removed
         */
        void clearOrders(std::string previousTimeStamp, std::string currentTime);

        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);
        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        static double getLowPrice(std::vector<OrderBookEntry>& orders);

        std::vector<OrderBookEntry> orders;

};
