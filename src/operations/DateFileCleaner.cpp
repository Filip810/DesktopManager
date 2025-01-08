#include "../../include/DateFileCleaner.h"
#include <chrono>
#include <iostream>

void DateFileCleaner::setFilesToRemove()
{

    std::ofstream logFile("../log/log.txt", std::ios::app);
    if (!logFile)
    {
        std::cerr << "Error opening log file!" << std::endl;
        return;
    }

    int seconds;
    std::cout<<"Provide number of seconds"<<std::endl;
    std::cin>>seconds;
    if (seconds > 0){
        std::cout<<seconds;
        auto now = std::chrono::system_clock::now();
        auto cutoffTime = now - std::chrono::seconds(seconds);

        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::time_t cutoffTime_time = std::chrono::system_clock::to_time_t(cutoffTime);


        logFile<< "Current time: " << std::ctime(&now_time);
        logFile<< "Cutoff time: " << std::ctime(&cutoffTime_time);


        for (const auto &entry : std::filesystem::directory_iterator(getCurrentLocation()))
        {
            try
            {
                if (std::filesystem::is_regular_file(entry.path()))
                {
                    auto lastWriteTime = std::chrono::file_clock::to_sys(std::filesystem::last_write_time(entry));

                    std::time_t lastWriteTimeTime = std::chrono::system_clock::to_time_t(lastWriteTime);

                    logFile << "Last write time: " << std::ctime(&lastWriteTimeTime);

                    if (lastWriteTime > cutoffTime)
                    {
                        filesToRemove.push_back(entry.path().string());
                    }
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error processing file: " << entry.path() << " - " << e.what() << std::endl;
            }
        }
    }
    else{
        std::cout<<"You have to provide a positive number"<<std::endl;
    }

    logFile.close();
}

std::vector<std::string> DateFileCleaner::getFilesToRemove() const
{
    return filesToRemove;
}