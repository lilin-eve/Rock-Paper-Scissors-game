#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>


bool settingsSuspend = false;

//  declaration for called function clearScreen()
//  
void clearScreen();

//  declaration for called function printBorderLine()
//  
void printBorderLine();

bool deleteFileLine( const std::string& fileName, const size_t& lineTarget );

std::pair<bool, std::vector<std::string>> getFileContent( const std::string& fileName );

bool updateFileLine( const std::string& fileName, const size_t& lineTarget, const std::string& newLineContent );

//  declaration for called function findUserName()
//  
std::tuple<bool,size_t,size_t> searchUserName( const std::string& userName );

void printUserFile( const std::string& fileInput ){

    auto [ gotFile, fileLines ] = getFileContent( fileInput );

    printBorderLine();
    if ( gotFile == true ){
        for ( size_t i = 0; i < fileLines.size(); i++ ){
            std::cout << fileLines[i] << std::endl;
        }
    }
    else {
        std::cout << "Error! File ' sys/" << fileInput << " ' unable to be opened." << std::endl;
    }

    /*
    std::ifstream readUserFile{ fileInput };
    std::string line{};

    clearScreen();
    printBorderLine();
    if ( readUserFile.is_open() ){
        while (getline(readUserFile, line )){
            std::cout << line;
        }
        readUserFile.close();
    }
    else {
        std::cout << "Error! File '" << fileInput << "' unable to be opened." << std::endl;
    }

    printBorderLine();
    for ( int x = 3; x > 0; x-- ){
        std::cout << " .";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    */

    return;

}

bool resetUserStats( const std::string& userName, const size_t& lineTarget ){

    bool verifyResetStats{false};

    if ( updateFileLine( "user-stats.txt", lineTarget, userName + "'s stats: Wins[ 0 ] Losses[ 0 ] Ties[ 0 ] | Rocks thrown[ 0 ] Paper thrown[ 0 ] Scissors thrown[ 0 ]" ) == true ){
        verifyResetStats = true;
    }

    /*
    std::ifstream readUserStats{ "user-stats.txt" };
    std::string line{};
    size_t lineNum{0};
    std::vector<std::string> fileLines{};

    if ( readUserStats.is_open() ){
        while ( getline( readUserStats, line ) ){
            if ( lineNum == lineTarget ){
                fileLines.push_back( userName + "'s stats: Wins[ 0 ] Losses[ 0 ] Ties[ 0 ] | Rocks thrown[ 0 ] Paper thrown[ 0 ] Scissors thrown[ 0 ]" );
            }
            else {
                fileLines.push_back(line);
            }
            lineNum++;
        }
    }
    else {
        std::cout << "Error! File 'user-stats.txt' unable to be opened." << std::endl;
    }

    std::ofstream updateUserStats{ "user-stats.txt" };

    if ( updateUserStats.is_open() ){
        for ( size_t i = 0; i < fileLines.size(); i++ ){
            updateUserStats << fileLines[i] + "\n";
        }
        updateUserStats.close();
    }
    else {
        std::cout << "Error! File 'user-stats.txt' unable to be opened for editing." << std::endl;
    }
    */

    return verifyResetStats;
    
}

bool deleteUser( const size_t& lineTarget ){

    bool verifyDeleteUser{false};
    int checksDeleteUser{0};

    if ( deleteFileLine( "users.txt", lineTarget ) == true ){
        checksDeleteUser++;
    }
    else{
        return verifyDeleteUser;
    }

    if ( deleteFileLine( "user-stats.txt", lineTarget ) == true ){
        checksDeleteUser++;
    }
    else {
        return verifyDeleteUser;
    }

    if ( checksDeleteUser == 2 ){
        verifyDeleteUser = true;
    }


    /*
    std::ifstream readUsers{ "users.txt" };
    std::string line{};
    size_t lineNum{0};
    std::vector<std::string> users{};

    if ( readUsers.is_open() ){
        while ( getline( readUsers, line )){
            if ( lineNum != lineTarget ){
                users.push_back(line);
            }
            lineNum++;
        }
        readUsers.close();
    }
    else {
        std::cout << "Error! File 'users.txt' unable to be opened." << std::endl;
    }

    std::ifstream readUserStats{ "user-stats.txt" };
    lineNum = 0;
    std::vector<std::string> userStats{};

    if ( readUserStats.is_open() ){
        while ( getline( readUserStats, line )){
            if ( lineNum != lineTarget ){
                userStats.push_back(line);
            }
            lineNum++;
        }
        readUserStats.close();
    }
    else {
        std::cout << "Error! File 'user-stats.txt' unable to be opened." << std::endl;
    }

    std::ofstream updateUsers{ "users.txt" };

    if ( updateUsers.is_open() ){
        for ( size_t i = 0; i < users.size(); i++ ){
            updateUsers << users[i] + "\n";
        }
        updateUsers.close();
    }
    else {
        std::cout << "Error! File 'users.txt' unable to be opened for editing." << std::endl;
    }

    std::ofstream updateUserStats{ "user-stats.txt" };

    if ( updateUserStats.is_open() ){
        for ( size_t i = 0; i < userStats.size(); i++ ){
            updateUserStats << userStats[i] + "\n";
        }
        updateUserStats.close();
    }
    else {
        std::cout << "Error! File 'user-stats.txt' unable to be opened for editing." << std::endl;
    }
    */

    return verifyDeleteUser;

}

std::string getUser(){
    std::string userName{};
    clearScreen();
    printBorderLine();
    std::cout << "Enter User-name: ";
    std::cin >> userName;

    return userName;

}

int menuSettings(){
    int menuInput{};

    do {
        printBorderLine();
        std::cout << "User Settings: " << std::endl;
        std::cout << " [1] Print users." << std::endl;
        std::cout << " [2] Print user stats." << std::endl;
        std::cout << " [3] Delete user." << std::endl;
        std::cout << " [4] Reset user stats." << std::endl;
        std::cout << " [5] Go back." << std::endl;
        printBorderLine();
        std::cout << ">";
        std::cin >> menuInput;
        if ( menuInput != 1 && menuInput != 2 && menuInput != 3 && menuInput != 4 && menuInput != 5 ){
            clearScreen();
            printBorderLine();
            std::cout << "Invalid input!" << std::endl;
            std::cout << "Input must be '1', '2', '3', '4', or '5'." << std::endl;
        }
    } while ( menuInput != 1 && menuInput != 2 && menuInput != 3 && menuInput != 4 && menuInput != 5 );

    return menuInput;

}

void userSettings(){

    settingsSuspend = false;

    clearScreen();
    while (!settingsSuspend){

        int menuInput{ menuSettings() };

        if ( menuInput == 1 ) {
            printUserFile( "users.txt" );
        }
        else if ( menuInput == 2 ) {
            printUserFile( "user-stats.txt" );
        }
        else if ( menuInput == 3 || menuInput == 4 ){
            std::string userName{ getUser() };
            auto [ foundUserName, lineTotal, lineTarget ] = searchUserName( userName );
            if ( foundUserName == true ){
                if ( menuInput == 3 ){
                    deleteUser( lineTarget );
                }
                else if ( menuInput == 4 ){
                    resetUserStats( userName, lineTarget );
                }
            }
            else {
                clearScreen();
                printBorderLine();
                std::cout << "User [ " << userName << " ] not found in 'users.txt'." << std::endl;
            }

        }
        else if ( menuInput == 5 ){
            settingsSuspend = true;
        }

    }

    return;

}
