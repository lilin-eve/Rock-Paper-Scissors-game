#include <iostream>
#include <fstream>
#include <tuple>
#include <string>
#include <thread>
#include <chrono>


bool gotUserName = false;

//  declaration for called funcation clearScreen()
//  
void clearScreen();

//  declaration for called function printBorderLine()
//  
void printBorderLine();

//  declaration for called function gameRockPaperScissors()
//  
void gameRockPaperScissors( const std::string& userName, const size_t& userLine );

bool updateFileLine( const std::string& fileName, const size_t& lineTarget, const std::string& newLineContent );

//  definition for called function findUserName()
//  function is tuple, returns 1 bool & 2 int values to caller function
//  
std::tuple<bool, size_t, size_t> searchUserName( const std::string& userName ){

    bool foundUserName{ false };

    std::ifstream readUsersFile{ "sys/users.txt" };
    std::string line{};
    size_t lineTotal{0};
    size_t lineTarget{};
    if ( readUsersFile.is_open() ){
        while(getline( readUsersFile, line )){
            if ( line.find( userName ) != std::string::npos ){
                foundUserName = true;
                lineTarget = lineTotal;
            }
            lineTotal++;
        }
        readUsersFile.close();
    }

    return {foundUserName, lineTotal, lineTarget};

}

std::string inputUserName(){

    std::string userName{};

    printBorderLine();
    std::cout << "What is your name ? : ";
    std::cin >> userName;

    return userName;

}

//  definition for called function getUserName()
//  function is void, returns no value to caller
//  function prompts user for if they've played before
//  if user has, user is prompted for name which is searched for in 'users.txt' in local directory
//  if user hasn't, user is prompted for name which will be stored in 'users.txt' in local directory, if 'users.txt' does not already exist it will be created
//  both results lead to the user-input name 'promptName' being passed to function gameRockPaperScissors()
//  
void getUserName( std::string promptFirst ){

    //  std::string fileNameUsers{ "users.txt" };

    gotUserName = false;
    //  std::string promptFirst{};

    while (!gotUserName){

        std::string promptName{ inputUserName() };
        
        clearScreen();
        printBorderLine();
        if ( promptFirst == "y" || promptFirst == "Y" ){
            auto [ foundUserName, lineTotal, lineTarget ] = searchUserName( promptName );
            if ( foundUserName == true ){
                std::cout << "User [ " << promptName << " ] found on line " << lineTarget + 1 << " of 'users.txt'." << std::endl;
                std::cout << "Welcome, " << promptName << "." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(3));
                gameRockPaperScissors( promptName, lineTarget );
                gotUserName = true;
            }
            else {
                if ( updateFileLine( "users.txt", lineTotal, promptName ) == true ){
                    std::cout << "User [ " << promptName << " ] not found in ' sys/users.txt ' . " << std::endl;
                    std::cout << "Adding user instead. " << std::endl;
                    gameRockPaperScissors( promptName, lineTotal );
                    gotUserName = true;
                }
            }
        }
        else if ( promptFirst == "n" || promptFirst == "N" ){
            auto [ foundUserName, lineTotal, lineTarget ] = searchUserName( promptName );
            if ( foundUserName == false ){
                if ( updateFileLine( "users.txt", lineTotal, promptName ) == true ){
                    std::cout << "User [ " << promptName << " ] successfully added to line " << lineTotal + 1 << " of ' sys/users.txt ' . " << std::endl;
                    std::cout << "Welcome, " << promptName << ". :)" << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    gameRockPaperScissors( promptName, lineTotal );
                    gotUserName = true;
                }
                else {
                    std::cout << "Error! User unable to be added to file ' sys/users.txt '. " << std::endl;
                }
            }
            else {
                std::string choice{};
                do {
                    std::cout << "A user with this name was already found." << std::endl;
                    std::cout << "Are you user [ " << promptName << " ] found on line " << lineTarget + 1 << " of 'users.txt'? ( Y / N ): ";
                    std::cin >> choice;
                    if ( choice != "y" && choice != "Y" && choice != "n" && choice != "N" ){
                        clearScreen();
                        printBorderLine();
                        std::cout << "Invalid input!\n";
                        std::cout << "Try again.\n"; 
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                    }
                } while ( choice != "y" && choice != "Y" && choice != "n" && choice != "N" );
                clearScreen();
                printBorderLine();
                if ( choice == "y" || choice == "Y" ) {
                    std::cout << "bruh.. don't even remember playing my rock, paper, scissors game. smdh :{" << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    gameRockPaperScissors( promptName, lineTarget );
                    gotUserName = true;
                }
                else if ( choice == "n" || choice == "N" ){
                    std::cout << "Input differentiating name." << std::endl;
                    gotUserName = false;
                }

            }

       }

    }

}
