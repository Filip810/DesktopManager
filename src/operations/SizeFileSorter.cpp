#include "../../include/SizeFileSorter.h"
#include <iostream>
#include <algorithm>

void SizeFileSorter::ProcessFiles()
{
    createDirectories();

    std::vector<std::pair<std::string, uintmax_t>> filesWithSizes;

    for (const auto &file : listOfFileWithExtension("*"))
    {
        try
        {
            uintmax_t fileSize = std::filesystem::file_size(file);
            filesWithSizes.emplace_back(file, fileSize);
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Error getting size of file " << file << ": " << e.what() << std::endl;
        }
    }

    std::sort(filesWithSizes.begin(), filesWithSizes.end(),
              [](const auto &a, const auto &b)
              { return a.second > b.second; });

    for (const auto &[file, size] : filesWithSizes)
    {
        processFile(file);
    }
}

void SizeFileSorter::processFile(const std::string &file)
{

    std::ofstream logFile("../log/log.txt", std::ios::app);
    if (!logFile)
    {
        std::cerr << "Error opening log file" << std::endl;
        return;
    }
    static int fileCounter = 1;

    std::string ext = std::filesystem::path(file).extension().string().substr(1);

    std::unordered_map<std::string, std::string> fileCategories = {
        {"txt", "Documents"}, {"jpg", "Images"}, {"png", "Images"}, {"mp4", "Movies"}, {"pdf", "Documents"}, {"exe", "Applications"}, {"mp3", "Music"}};

    if (fileCategories.find(ext) != fileCategories.end())
    {
        std::string category = fileCategories[ext];
        std::filesystem::path destinationDir = currentLocation / category;

        try
        {
            std::filesystem::create_directory(destinationDir);

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

    logFile.close();
}