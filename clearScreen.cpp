#include <iostream>

void clearScreen(){
    
    std::cout << "\033[2J" << std::endl;
    
    return;

}
