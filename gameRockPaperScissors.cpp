#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <thread>
#include <chrono>


//  declaration for called function clearScreen()
//  function is void, returns no value to caller
//  
void clearScreen();

//  declaration for called function printBorderLine()
//  function is void, returns no value to caller
//  
void printBorderLine();

//  declaration for called function updateUserStats()
//  function is void, returns no value to caller
//  
void updateUserStats( const std::string& userName, const size_t& lineTarget, const std::vector<int>& gameEndStats, const std::vector<int>& gameItemStats );

//  definition for global bool value 'gameOff'
//  when 'gameOff' is false, gameRockPaperScissors() loops
//  when 'gameOff' is true, gameRockPaperScissors() ends loop
//  
bool gameOff = false;

//  global vector 'gameEndStats' containing int values representing current game wins, losses, & ties
//  
std::vector<int> gameEndStats{ 0, 0, 0 };
//  int countGameWin{0};
//  int countGameLose{0};
//  int countGameTie{0};

//  global vector 'gameItemStats' containing int values representing total for each item thrown during game
//  
std::vector<int> gameItemStats{ 0, 0, 0 };

//  definition for called function gameStart()
//  function is void returns no value to caller
//  function receives int value & string value from caller, locally named 'userInput' & 'userName'
//  function starts & creates vector 'gameItems' containing 3 string values, 'Rock', 'Paper', & 'Scissors'
//  function creates pseudorandom number generator 'seed' & an int value distribution 'range' that extends from 0 to 2
//  function creates int value 'comNum' that is sourced from 'seed' with 'range' imposed on it
//  function creates unsigned long int values 'comPlay' & 'userPlay' static-casted from 'comNum' & 'userInput'
//  
//  
void gameStart( const int& userInput, const std::string& userName ){

    //  vector containing string values
    //  element 0 = 'Rock' | element 1 = 'Paper' | element 2 = 'Scissors'
    const std::vector<std::string> gameItems{ "Rock", "Paper", "Scissors" };

    //  seeding pseudorandom number generator 'seed' with a number from a random device
    std::mt19937 seed( std::random_device{}() );
    //  defining an int distribution 'range' that extends from 0 to 2
    std::uniform_int_distribution<int> range(0, 2);

    //  'comNum' & 'userInput' are int values 
    //  int 'comNum' is created and assigned a value  
    const int comNum = range( seed );

    // unsigned long int values 'comPlay' & 'userPlay' created and are equal to values in 'comNum' & 'userInput', needed for proper indexing of vector 'gameItems'
    const unsigned long comPlay = static_cast<unsigned long>( comNum );
    const unsigned long userPlay = static_cast<unsigned long>( userInput );

    printBorderLine();
    std::cout << userName << " plays: " << gameItems[ userPlay ] << std::endl;

    for ( size_t i = 0; i < gameItems.size(); i++ ){
        std::this_thread::sleep_for( std::chrono::seconds(1) );        
        std::cout << gameItems[i] << std::endl;
    }

    std::this_thread::sleep_for( std::chrono::seconds(1) );

    std::cout << "Shoot!\n";

    printBorderLine();
    std::cout << "Computer plays: " << gameItems[ comPlay ] << std::endl;
    printBorderLine();

    //  if 'userInput' & computer-input('comNum') are the same(i.e. 'Rock' & 'Rock'(gameItems[0] = gameItems[0]) )then game is tie
    if ( userInput == comNum ){
        gameEndStats[2]++;
        std::cout << "Game Tie.\n";
        std::cout << gameItems[ userPlay ] << " & " << gameItems[ comPlay ] << " are the same. :/ \n"; 
    }
    //  if 'userInput' is 1 less than 'comNum', then that must be a lose, because any value or item that has an item above it can be beat by that item(i.e. 'Paper' beats 'Rock'(gameItems[1] > gameItems[0]), 'Scissors' beats 'Paper'(gameItems[2] > gameItems[1]), 'Scissors' has no value above it.)
    //  or if 'userInput' is 2 more than 'comNum', then that must also be a lose, because the last value 'Scissors'(gameItem[2]) can only be beat by the first value 'Rock'(gameItem[0]), which is 2 less than 'Scissors' in the vector index
    else if ( userInput == comNum - 1 || userInput == comNum + 2 ){
        gameEndStats[1]++;
        std::cout << "Computer wins! :'O\n";
        std::cout << gameItems[ comPlay ] << " beats " << gameItems[ userPlay ] << "!" << std::endl;
    }
    //  if 'comNum' is 1 less than 'userInput' or if 'comNum' is 2 more than 'userInput', then the player wins:)
    else if ( comNum == userInput - 1 || comNum == userInput + 2 ){
        gameEndStats[0]++;
        std::cout << userName << " wins! :D\n";
        std::cout << gameItems[ userPlay ] << " beats " << gameItems[ comPlay ] << "!" << std::endl;
    }

    std::string menuInput{};

    do {
        printBorderLine();
        std::cout << "Hi " << userName << ", would you like to play again? ( Y / N ): ";
        std::cin >> menuInput;
        if ( menuInput != "y" && menuInput != "Y" && menuInput != "n" && menuInput != "N" ){
            printBorderLine();
            std::cout << "Invalid input!\n";
            std::cout << "Try again.\n";
        }
    } while ( menuInput != "y" && menuInput != "Y" && menuInput != "n" && menuInput != "N" );

    if ( menuInput == "y" || menuInput == "Y" ){
        //  gameRockPaperScissors();
        clearScreen();
        printBorderLine();
        return;
    }
    else if ( menuInput == "n" || menuInput == "N" ){
        gameOff = true;
    }

}

//  definition for called & caller function userPlayInput()
//  function is type int, returns int value to caller
//  function calls functions clearScreen() & printBorderLine()
//  function creates int value 'menuInput' & enters do-while loop, loops while 'menuInput' is not '1', '2', or '3'
//  function prompts user for input into 'menuInput', function prints error message if not '1', '2', or '3' & loops
//  function exits do-while loop upon proper input into 'menuInput'
//  function ends & returns 'menuInput' as return value
//  
int userPlayInput( const std::string& userName ){

    int menuInput{};

    clearScreen();
    printBorderLine();

    do {
        std::cout << userName << " vs. Computer" << std::endl; 
        std::cout << "[1] Rock, [2] Paper, or [3] Scissors: ";
        std::cin >> menuInput;
        if ( menuInput != 1 && menuInput != 2 && menuInput != 3 ){
            clearScreen();
            printBorderLine();
            std::cout << "Invalid input!\n";
            std::cout << "Input must only be number(integer) for item. '1' for Rock, '2' for Paper, or '3' for Scissors.\n";
            printBorderLine();
        }
    } while ( menuInput != 1 && menuInput != 2 && menuInput != 3 );

    return menuInput;

}

//  definition for called & caller function gameRockPaperScissors()
//  function is void, returns no value to caller
//  function sets global bool 'gameOff' to false
//  function enters while loops, loops while 'gameOff' is false
//  function creates int value 'userInput' & refers to function userPlayInput() for its value, string 'userName' is also passed to function userPlayInput()
//  after return, function calls function gameStart() & passes int 'userInput' minus 1 & string 'userName'
//  function loops until user sets 'gameOff' to true
//  
void gameRockPaperScissors( const std::string& userName, const size_t& userLine ){

    gameOff = false;

    while (!gameOff){
    //  int value 'userInput' is created & function userPlayInput() is referred to for its value
    int userInput{ userPlayInput( userName ) };

    if ( userInput == 1 ){
        gameItemStats[0]++;
    }
    else if ( userInput == 2 ){
        gameItemStats[1]++;
    }
    else if ( userInput == 3 ){
        gameItemStats[2]++;
    }
    // 'userInput' has 1 subtracted from it because items in vectors are 0-indexed and 'userInput' needs to correspond to that index value 
    gameStart( userInput - 1, userName );
    }

    if ( gameOff == true ){
        updateUserStats( userName, userLine, gameEndStats, gameItemStats );
        for ( int x = 2; x > 0; x-- ){
            for ( size_t i = 0; i < 3; i++){
                if ( x == 2 ){
                    gameEndStats[i] = 0;
                }
                else {
                    gameItemStats[i] = 0;
                }
            }
        }
    }
     
    return;

}
