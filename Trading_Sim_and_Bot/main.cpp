#include "Wallet.h"
#include <iostream>
#include "MerkelMain.h"
#include "Bot.h"

int main()
 {   //std::cout << " For Bot press 1, for Manual Press 2" << std::endl;

//     int userOption = 0;
//     std::string line;
//     std::cout << "Type in 1 or 2" << std::endl;
//     std::getline(std::cin, line);
//     try{
//         userOption = std::stoi(line);
//     }catch(const std::exception& e)
//     {
//         // 
//     }
//     std::cout << "You chose: " << userOption << std::endl;

//     if (userOption == 0) // bad input
//     {
//         std::cout << "Invalid choice. Choose 1-6" << std::endl;
//     }
//     if (userOption == 1) 
//     {
//         std::cout << "Now Begining Bot " << std::endl;
//         Bot app{};
//         app.init();
//     }
//     if (userOption == 2) 
//     {
//         std::cout << "Now Begining Manual " << std::endl;
//         MerkelMain app{};
//         app.init();
//     }    

        std::cout << "Now Begining Bot " << std::endl;
        Bot app{};
        app.init();
    
}
