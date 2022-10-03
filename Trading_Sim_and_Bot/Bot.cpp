#include "Bot.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"

/** Creates an instance of the bot*/
Bot::Bot()
{

}
/** Initilaizes bot;
 * sets times, clears logs
 */
void Bot::init()
{
    // initialize order book with the data from the first ever timefram
    currentTime = orderBook.getEarliestTime();

    // sets previous time to empty
    previousTime = "";

    // sets last time to know when to stop the simulations
    lastTime = orderBook.getLastestTime();

    Logger::clearLogsAndAssets();

    // Start of with an arbitrary amount of money
    // Wish I could do this in real life....
    wallet.insertCurrency("BTC", 10);
    wallet.insertCurrency("DOGE", 10000);
    wallet.insertCurrency("USDT", 1000);

    

    // Show what my starting wallet is
    std::cout << wallet.toString() << std::endl;
    Logger::printAssets(wallet.toString());
    
    
    while(currentTime != lastTime)
    {
        Bot::BotMain();
    }

    // Show what the ending wallet is
    std::cout << wallet.toString() << std::endl;
    Logger::printAssets(wallet.toString());
}

void Bot::BotMain()
{
    for(std::string product : orderBook.getKnownProducts(currentTime))
    {
        // vector of the current asks
        asks = orderBook.getOrders(OrderBookType::ask, product, currentTime );

        // vector of the last time stamps asks
        prev_asks = orderBook.getOrders(OrderBookType::ask, product, previousTime);

        // vector of the current bids
        bids = orderBook.getOrders(OrderBookType::bid, product, currentTime);

        // vector of the previous timesteps bids
        prev_bids = orderBook.getOrders(OrderBookType::bid, product, previousTime);

        // Make a Bid
        Bot::makeBid(product);

        // Make an Ask
        Bot::makeAsk(product);

        // Process sales, move to next time step
        Bot::receiveAndProcessSales(product);
    }
}
     
void Bot::receiveAndProcessSales(std::string product)
{        
    std::vector<OrderBookEntry> sales =  orderBook.matchAsksToBids(product, currentTime);
    for (OrderBookEntry& sale : sales)
    { 
        if(sale.username == "simuser")
        {
            //process sale
            wallet.processSale(sale);

            std::cout << "Processing" << std::endl;

            // Update our current assets
            Logger::printAssets(wallet.toString());
        }
        
    }      
    // sets previoustime and updates current time 
    previousTime = currentTime;

    currentTime = orderBook.getNextTime(currentTime);

   // deletes entries older than previousTime
   orderBook.clearOrders(previousTime, currentTime);
}

void Bot::makeBid(std::string product)
{   
    // The current average of this time steps asks
    double average = Bot::getAverage(asks);

    // The average of last timesteps asks
    double previousAverage = Bot::getAverage(prev_asks);

    // bids slightly less than predicted price for hopes of profit
    double bid_offer = Bot::predictPrice(average, previousAverage) * 0.97;
    
    // Our order
    OrderBookEntry obe = { bid_offer, 100, currentTime, product, OrderBookType::bid};

    // Let the sim know its us
    obe.username = "simuser";

    if (wallet.canFulfillOrder(obe))
            {
                orderBook.insertOrder(obe);
                std::cout << "making Bid!" << std::endl;
                Logger::printOffers(obe, "bid"); 
            }    
}

void Bot::makeAsk(std::string product)
{
    // The current average of this time steps bids
    double average = Bot::getAverage(bids);

    // The average of last timesteps bids
    double previousAverage = Bot::getAverage(prev_bids);

    // asks for slightly more than predicted price for hopes of profit
    double ask_offer = Bot::predictPrice(average, previousAverage) * 1.02f;

    // Our order
    OrderBookEntry obe = { ask_offer, 20, currentTime, product, OrderBookType::ask};

    // Let the sim know its us
    obe.username = "simuser";

    if (wallet.canFulfillOrder(obe))
            {
                orderBook.insertOrder(obe);
                std::cout << "making Ask!" << std::endl;
                Logger::printOffers(obe, "ask"); 
            }  
}

// get the average price of a vector of orders
double Bot::getAverage(std::vector <OrderBookEntry>& orders)
{
    double sum = 0.0f;
    // The total price of all orders
    for (OrderBookEntry& order : orders)
    {
        sum += order.price;
    }
    // Divide by the number of orders
    double average = sum / orders.size();

    return average;
}

// predcits future price of products based on current timestamp
double Bot::predictPrice(double current_average,double prev_average)
{
    // difference between current and previous averages
    double difference = current_average - prev_average; 

    // the difference as a percentage
    double percent_dif =  (difference / prev_average );

    // the future predicted price , price now plus the percentage difference
    double pricePredict = current_average + current_average * percent_dif;

    return pricePredict;    
};

