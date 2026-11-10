#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <filesystem>
#include <fstream>

//  definition for global bool variable 'programTermination'
//  when 'programTermination' is false, main() stays in loop, when 'programTermination' is true, main() exits loop & returns 0
//  
bool programTermination = false;

//  declaration for called function printBorderLine()
//  
void printBorderLine();

//  declaration for called function clearScreen()
//  
void clearScreen();

//  declaration for called functin getUserName()
//  
void getUserName( std::string promptFirst );

//  declaration for called function printUserFile();
//  function is void, returns no value to caller
//  
void printUserFile( const std::string& fileInput );

//  declaration for called function userSettings();
//  
void userSettings();

bool initSystemFiles();

//  definition for function menuMain()
//  function is type string, returns string value to caller function
//  
int menuMain(){
    
    int menuInput{};

    clearScreen();
    do {
        printBorderLine();
        std::cout << "Hello Player, & welcome to Rock, Paper, Scissors! x3 \n";
        printBorderLine();
        std::cout << "Would you like to:" << std::endl;
        std::cout << " [1] Play." << std::endl;
        std::cout << " [2] List registered users." << std::endl;
        std::cout << " [3] Look at user-stats." << std::endl;
        std::cout << " [4] User Settings." << std::endl;
        std::cout << " [5] Quit." << std::endl;
        printBorderLine();
        std::cout << ">";
        std::cin >> menuInput;
        if ( menuInput != 1 && menuInput != 2 && menuInput != 3 && menuInput != 4 && menuInput != 5 ){
            clearScreen();
            printBorderLine();
            std::cout << "Invalid input!" << std::endl;
            std::cout << "Input must be '1', '2', '3', '4', or '5'." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    } while ( menuInput != 1 && menuInput != 2 && menuInput != 3 && menuInput != 4 && menuInput != 5 );

    return menuInput;

}

//  
int main(){

    if ( initSystemFiles() == true ){
        while (!programTermination){
        
            int menuMainInput{ menuMain() };

            if ( menuMainInput == 1 ){
                std::string promptFirst{};
                do {
                    printBorderLine();
                    std::cout << "Have you played before? ( Y / N ): ";
                    std::cin >> promptFirst;
                    if ( promptFirst != "y" && promptFirst != "Y" && promptFirst != "n" && promptFirst != "N" ){
                        clearScreen();
                        printBorderLine();
                        std::cout << "Invalid input!\n";
                        std::cout << "Try again.\n";
                    }
                } while ( promptFirst != "y" && promptFirst != "Y" && promptFirst != "n" && promptFirst != "N" );

                getUserName( promptFirst );

            }
            else if ( menuMainInput == 2 ){
                printUserFile( "users.txt" );
            }
            else if ( menuMainInput == 3 ){
                printUserFile( "user-stats.txt" );
            }
            else if ( menuMainInput == 4 ){
                userSettings();
            }
            else if ( menuMainInput == 5 ){
                printBorderLine();
                std::cout << "Exiting program . . . " << std::endl;
                programTermination = true;
            }
        }
    }
    else {
        printBorderLine();
        std::cout << "Error! System file directory ' sys/ ' or system files ' sys/users.txt ' & ' sys/user-stats.txt ' unable to be properly initialized & verified. " << std::endl;
        std::cout << "Program now shutting down . . . " << std::endl;
    }

    

    return 0;

}
