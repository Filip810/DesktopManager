#include "../../include/FileCleaner.h"
#include <iostream>

void FileCleaner::setCurrentLocation(const std::string &dir)
{
    currentLocation = dir;
}

std::filesystem::path FileCleaner::getCurrentLocation() const
{
    return currentLocation;
}

void FileCleaner::removeFiles()
{

    std::ofstream logFile("../log/log.txt", std::ios::app);
    if (!logFile)
    {
        std::cerr << "Error opening log file" << std::endl;
        return;
    }
    for (const auto &file : filesToRemove)
    {
        try
        {
            if (std::filesystem::is_regular_file(file))
            {
                std::filesystem::remove(file);
                logFile << file << " deleted successfully" << std::endl;
            }
            else
            {
                logFile << "Skipping directory: " << file << std::endl;
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Error removing file " << file << ": " << e.what() << std::endl;
        }
    }
    logFile.close();
}