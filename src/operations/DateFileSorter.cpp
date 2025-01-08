#include "../../include/DateFileSorter.h"
#include <algorithm>
#include <iostream>

void DateFileSorter::ProcessFiles()
{


    createDirectories();

    std::vector<std::pair<std::string, std::filesystem::file_time_type>> filesWithDates;

    for (const auto &file : listOfFileWithExtension("*"))
    {
        try
        {
            std::filesystem::file_time_type ftime = std::filesystem::last_write_time(file);
            filesWithDates.emplace_back(file, ftime);
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Error getting last write time of file " << file << ": " << e.what() << std::endl;
        }
    }

    std::sort(filesWithDates.begin(), filesWithDates.end(),
              [](const auto &a, const auto &b)
              { return a.second > b.second; });

    for (const auto &[file, date] : filesWithDates)
    {
        processFile(file);
    }
}

void DateFileSorter::processFile(const std::string &file)
{

    std::ofstream logFile("../../log/log.txt", std::ios::app);
    if (!logFile)
    {
        std::cerr << "Error opening log file!" << std::endl;
        return;
    }
    static int fileCounter = 1;



    if (std::filesystem::is_regular_file(file)){

    std::string ext = std::filesystem::path(file).extension().string();

        if (!ext.empty() && ext[0] == '.')
        {
            ext = ext.substr(1);
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

        if (fileCategories.find(ext) != fileCategories.end())
        {
            std::string category = fileCategories[ext];
            std::filesystem::path destinationDir = currentLocation / category;

            try
            {
                std::filesystem::create_directories(destinationDir);

                std::string newFileName = std::to_string(fileCounter++) + "_" + std::filesystem::path(file).filename().string();
                std::filesystem::path destinationFile = destinationDir / newFileName;

                std::filesystem::copy(file, destinationFile);
                std::filesystem::remove(file);

                logFile << "Moved file " << file << " to " << destinationFile << std::endl;
            }
            catch (const std::filesystem::filesystem_error &e)
            {
                std::cerr << "Error processing file " << file << ": " << e.what() << std::endl;
            }
        }
        else
        {
            logFile << "No category for file: " << file << std::endl;
        }
    }
    else
    {
        logFile << "Skipping non-regular file: " << file << std::endl;
    }

    logFile.close();
}