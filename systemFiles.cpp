#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>
#include <tuple>

bool confirmLineContent( const std::string& fileName, const size_t& lineTarget, const std::string& searchTarget ){

    bool verifyLineContent{false};

    std::string line{};
    size_t lineNum{0};

    std::filesystem::path filePath{ "sys/" + fileName };

    std::ifstream readFile{ filePath };

    if ( readFile.is_open() ){
        while (getline(readFile, line)){
            if ( line.find(searchTarget) != std::string::npos && lineNum == lineTarget ){
                verifyLineContent = true;
            }
            lineNum++;
        }
        readFile.close();
    }

    return verifyLineContent;

}

bool updateFile( const std::string& fileName, const std::vector<std::string>& fileLines ){

    bool verifyUpdateFile{false};

    std::filesystem::path filePath { "sys/" + fileName };

    std::ofstream updateFile{ filePath };

    if ( updateFile.is_open() ){
        for ( size_t i = 0; i < fileLines.size(); i++){
            updateFile << fileLines[i] + "\n";
        }
        updateFile.close();
        verifyUpdateFile = true;
    }

    return verifyUpdateFile;

}

std::pair<bool, std::vector<std::string>> getFileContent( const std::string& fileName ){

    bool gotFile{false};

    std::vector<std::string> fileLines{};
    std::string line{};

    std::filesystem::path filePath{ "sys/" + fileName };

    std::ifstream getFile{ filePath };

    if ( getFile.is_open() ){
        while (getline( getFile, line )){
            fileLines.push_back(line);
        }
        getFile.close();
        gotFile = true;
    }
    
    return {gotFile, fileLines};
}

bool deleteFileLine( const std::string& fileName, const size_t& lineTarget ){

    bool verifyDeleteLine{false};

    auto [ gotFile, fileLines ] = getFileContent( fileName );

    std::vector<std::string> newFileLines{};

    if ( gotFile == true ){
        for ( size_t i = 0; i < fileLines.size(); i++ ){
            if ( i != lineTarget ){
                newFileLines.push_back(fileLines[i]);
            }
        }
    }

    if ( updateFile( fileName, newFileLines ) == true ){
        verifyDeleteLine = true;
    }

    return verifyDeleteLine;

}

bool updateFileLine( const std::string& fileName, const size_t& lineTarget, const std::string& newLineContent ){

    bool verifyFileLine{false};

    std::filesystem::path filePath{ "sys/" + fileName };

    auto [ gotFile, fileLines ] = getFileContent( fileName );

    std::vector<std::string> newFileLines{};

    if ( gotFile == true ){
        for ( size_t i = 0; i < fileLines.size(); i++ ){
            newFileLines.push_back(fileLines[i]);
        }
    }
    else {
        return verifyFileLine;
    }

    if ( lineTarget < newFileLines.size() ){
        newFileLines[lineTarget] = newLineContent;
    }
    else if ( lineTarget == newFileLines.size() ){
        newFileLines.push_back(newLineContent);
    }

    if ( updateFile( fileName, newFileLines ) == true ){
        if ( confirmLineContent( fileName, lineTarget, newLineContent ) == true ){
            verifyFileLine = true;
        }
        else {
            return verifyFileLine;
        }
    }
    else {
        return verifyFileLine;
    }

    return verifyFileLine;

}

bool updateUserStats( const std::string& userName, const size_t& lineTarget, const std::vector<int>& gameEndStats, const std::vector<int>& gameItemStats ){

    bool verifyUserStats{false};

    std::ifstream readUserStats{ "sys/user-stats.txt" };

    std::string line{};
    size_t lineNum{0};
    std::vector<int> userEndStatsTemp{ 0, 0, 0 };
    std::vector<int> userItemStatsTemp{ 0, 0, 0 };
    //  std::vector<std::string> fileLines{};

    if ( readUserStats.is_open() ){
        while (getline( readUserStats, line)){
            //  lineNum++;
            if ( lineNum == lineTarget ){
                if ( !line.empty() ){
                    std::istringstream stream(line);
                    //  userStats[0] is user total win-count, userStats[1] is total lose, userStats[2] is total ties
                    std::string word{};
                    size_t stat{0};
                    while ( stream >> word ){
                        if ( isdigit( word[0] )){
                            int tempScore = std::stoi(word);
                            if ( stat < 3 ){
                                userEndStatsTemp[stat] = tempScore;
                            }
                            else {
                                userItemStatsTemp[stat - 3] = tempScore;
                            }
                            stat++;
                        }
                    }
                } 
            }
            lineNum++;
            //  fileLines.push_back(line);
        }
        readUserStats.close();
    } 
    else {
        return verifyUserStats;
    }

    for ( int x = 2; x > 0; x-- ){
        for ( size_t i = 0; i < 3; i++ ){
            if ( x == 2 ){
                userEndStatsTemp[i] += gameEndStats[i];
            }
            else {
                userItemStatsTemp[i] += gameItemStats[i];
            }
        }
    }

    std::vector<std::string> userEndStats{};

    for ( size_t i = 0; i < userEndStatsTemp.size(); i++ ){
        userEndStats.push_back(std::to_string(userEndStatsTemp[i]));
    }

    std::vector<std::string> userItemStats{};

    for ( size_t i = 0; i < userItemStatsTemp.size(); i++ ){
        userItemStats.push_back(std::to_string(userItemStatsTemp[i]));
    }

    std::string lineReplace{ userName + "'s stats: Wins[ " + userEndStats[0] + " ] Losses[ " + userEndStats[1] + " ] Ties[ " + userEndStats[2] + " ] | Rocks thrown[ " + userItemStats[0] + " ] Paper thrown[ " + userItemStats[1] + " ] Scissors thrown[ " + userItemStats[2] + " ]" };

    if ( updateFileLine( "user-stats.txt", lineTarget, lineReplace) == true ){
        verifyUserStats = true;
    }

    /*
    if ( lineTarget < fileLines.size() ){
        fileLines[ lineTarget ] = lineReplace;
    }
    else if ( lineTarget == fileLines.size() ){
        fileLines.push_back( lineReplace );
    }

    if ( updateFile( "user-stats.txt", fileLines ) == true ){
        if ( confirmLineContent( ))
    }
    */

    return verifyUserStats;

}

bool initSystemFiles(){
    bool verifySystemFiles{false};
    int checksSystemFiles{0};

    std::filesystem::path sysDir{ "sys" };

    if ( !std::filesystem::create_directory( sysDir ) ){
        if ( std::filesystem::exists( sysDir ) ){
            checksSystemFiles++;
        }
        else {
            checksSystemFiles = 0;
            return verifySystemFiles;
        }
    }
    else {
        checksSystemFiles++;
    }

    std::ofstream createUsersFile{ "sys/users.txt", std::ios::app };

    if ( createUsersFile.is_open() ){
        checksSystemFiles++;
        createUsersFile.close();
    }
    else {
        checksSystemFiles = 0;
        return verifySystemFiles;
    }

    std::ofstream createUserStatsFile{ "sys/user-stats.txt", std::ios::app };

    if ( createUserStatsFile.is_open() ){
        checksSystemFiles++;
        createUserStatsFile.close();
    }
    else {
        checksSystemFiles = 0;
        return verifySystemFiles;
    }

    if ( checksSystemFiles == 3 ){
        verifySystemFiles = true;
    }
    
    return verifySystemFiles;

}
