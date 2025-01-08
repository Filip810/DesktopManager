#include "../../include/FileSorter.h"
#include <unordered_map>
#include <iostream>

void FileSorter::setCurrentLocation(const std::string &dir)
{
    currentLocation = dir;
}

std::filesystem::path FileSorter::getCurrentLocation() const
{
    return currentLocation;
}

void FileSorter::ProcessFiles()
{
    createDirectories();
    for (const auto &file : listOfFileWithExtension("*"))
    {
        processFile(file);
    }
}

void FileSorter::processFile(const std::string &file)
{
    moveFileToCategory(file);
}

void FileSorter::moveFileToCategory(const std::string &file)
{

    std::ofstream logFile("../log/log.txt", std::ios::app);
    if (!logFile)
    {
        std::cerr << "Error opening log file" << std::endl;
        return;
    }
    std::unordered_map<std::string, std::string> fileCategories = {
        {"txt", "Documents"},
         {"jpg", "Images"}, 
         {"png", "Images"}, 
         {"mp4", "Movies"}, 
         {"pdf", "Documents"}, 
         {"exe", "Applications"}, 
         {"mp3", "Music"}
         
         };

    std::string ext = file.substr(file.find_last_of(".") + 1);
    if (fileCategories.find(ext) != fileCategories.end())
    {
        std::string category = fileCategories[ext];
        std::string filename = file.substr(file.find_last_of("\\") + 1);
        std::filesystem::path destination = currentLocation / category / filename;
        try
        {
            std::filesystem::rename(file, destination);
            logFile << "Moved file: " << file << " to " << destination << std::endl;
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Error moving file " << file << ": " << e.what() << std::endl;
        }
    }

    logFile.close();
}