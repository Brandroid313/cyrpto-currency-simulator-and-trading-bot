//  R1A: Retrieve the live order book from the Merklerex exchange simulation


//R1B: Generate predictions of likely future market exchange rates using defined
// algorithms, for example, linear regression.

#pragma once
//#include "Logger.h"
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

/*For Grader - For your convenience functions that directly 
  relate to the requirements are 
  commented with the requirement number above them
  example : R1A, R2C etc. 
  R2D & R3D and Challenge requirement part 2 can be found in
  OrderBook.h under clearOrders and Challenge requirment part 3
  can be found in Orderbook.cpp getKnownProducts and getOrders
 */  
class Bot
{
    public:
        Bot();
        /** Call this to start the Bot sim */
        void init();

    private:   
         
        // Get the current average price works with predictPrice
        double getAverage(std::vector<OrderBookEntry>& orders);

        // Stores current time 
        std::string currentTime;

        // Stores the previous time
        std::string previousTime;

        // Stores the latest time
        std::string lastTime;

        // Instance of the wallet
        Wallet wallet;

        /* The vecotrs of OrderBookEntries we will need,
        To optimize */
        // std::vector<OrderBookEntry> sales;
        std::vector<OrderBookEntry> asks;
        std::vector<OrderBookEntry> prev_asks;
        std::vector<OrderBookEntry> bids;
        std::vector<OrderBookEntry> prev_bids;

        /** Challenge requirement part1: The main funtion
         * Iterates over getKnownProducts once
         * to save time */ 
        void BotMain();

        /**R1A: Retrieve the live order book 
         * When bot is initialized, create orderbook 
         * for bot to have access to
         */
        OrderBook orderBook{"20200601.csv"};
     // OrderBook orderBook{"20200317.csv"};
        
        //R1B :Generates predictions of likely future market prices based on current and previous averages
        double predictPrice(double current_average, double prev_average) ;

        //R2A, R2B & R3C:  Makes Bids based predict price function
        void makeBid(std::string product);

        /** R2C & R3C:
         * Steps through time taking
         *  bid and asks sales and processing them
         */
        void receiveAndProcessSales(std::string product);

        /** R3A & R3B Makes asks based on the predict price 
         * function in hopes of profit */
        void makeAsk(std::string product);

};
