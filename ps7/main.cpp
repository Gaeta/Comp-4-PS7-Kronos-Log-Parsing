/** 
 * Created By: Donald Gaeta
 * Date: 4/21/25
 * 
 * 
 * Copyright (c) 2025 Donald J Gaeta (Gaeta.me)
 * This software is provided "as is" for educational and grading purposes only by authorized individuals. 
 * Any use, reproduction, distribution, or modification of this software for purposes other than those 
 * mentioned is strictly prohibited. Unauthorized use may result in legal action. All rights reserved. 
 * The author retains perpetual ownership of this software and its associated materials.
 * 
 */

#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>

#define HEAD "=== Device boot ===\n"
#define BOOT_START " Boot Start\n"
#define BOOT_FAIL "**** Incomplete boot ****\n\n"
#define BOOT_SUCCESS " Boot Completed\n"
#define TIMER "\tBootTime:"

std::string getStrTime(std::string line);

int main(int argc, char* argv[]) {
    std::string line;

    std::ofstream outputFile;
    std::ifstream inputFile;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string input = argv[1];
    std::string output = input + ".rpt";

    std::string printedName = "(" + input + "): ";

    inputFile.open(input);
    outputFile.open(output);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening file(s)." << std::endl;
        return 1;
    }

    boost::posix_time::ptime timeStart, timeEnd;
    int compTime;

    std::regex start(
        "(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}): \\(log\\.c\\.166\\) server started ");

    std::regex end(
        "(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}\\.\\d{3}):INFO:oejs\\.AbstractConnector:"
        "Started SelectChannelConnector@0\\.0\\.0\\.0:9080");

    size_t lineNumber = 1;
    bool bootStarted = false;

    int bootStartedCount = 0;
    int bootCompletedCount = 0;

    std::ostringstream buffer;

    while (std::getline(inputFile, line)) {
        if (std::regex_match(line, start) && (bootStarted == true)) {
            timeStart = boost::posix_time::time_from_string(line.substr(0, 19));
            buffer << BOOT_FAIL << HEAD
                   << lineNumber << printedName << getStrTime(line) << BOOT_START;
            bootStartedCount++;

        } else if (std::regex_match(line, start) && (bootStarted == false)) {
            bootStarted = true;
            timeStart = boost::posix_time::time_from_string(line.substr(0, 19));

            buffer << HEAD << lineNumber << printedName << getStrTime(line) << BOOT_START;
            bootStartedCount++;

        } else if (std::regex_match(line, end) && (bootStarted == true)) {
            bootStarted = false;
            timeEnd = boost::posix_time::time_from_string(line.substr(0, 19));
            compTime = (timeEnd - timeStart).total_milliseconds();
            buffer << lineNumber << printedName << getStrTime(line) << BOOT_SUCCESS;
            buffer << TIMER << compTime << "ms " << std::endl << std::endl;
            bootCompletedCount++;

        } else if (std::regex_match(line, end) && (bootStarted == false)) {
            return 1;
        }
        lineNumber++;
    }

    outputFile << "Device Boot Report" << std::endl << std::endl
               << "InTouch log file: " << input << std::endl
               << "Lines Scanned: " << lineNumber - 1 << std::endl << std::endl
               << "Device boot count: initiated = " << bootStartedCount
               << ", completed: " << bootCompletedCount << std::endl << std::endl;

    outputFile << buffer.str();

    outputFile.close();
    inputFile.close();
    return 0;
}

std::string getStrTime(std::string line) {
    std::string time;
    time = line.substr(0, 10);
    time.push_back(' ');
    time.append(line.substr(11, 8));
    return time;
}

