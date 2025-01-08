#include "../include/FileCleaner.h"
#include "../include/ExtensionFileCleaner.h"
#include "../include/DateFileCleaner.h"
#include "../include/Operations.h"
#include "../include/FileSorter.h"
#include "../include/DateFileSorter.h"
#include "../include/SizeFileSorter.h"



#include <iostream>
#include <unordered_map>

void displayMenu()
{
    std::cout << "\n******************************\n";
    std::cout << "File Operations Menu:\n";
    std::cout << "1. Sort files by extension\n";
    std::cout << "2. Sort files by size\n";
    std::cout << "3. Sort files by date\n";
    std::cout << "4. Delete files by extension\n";
    std::cout << "5. Delete files younger than X seconds\n";
    std::cout << "6. Change Location (e.g., C:\\Users\\Name\\Desktop\\Images)\n";
    std::cout << "7. Exit\n";
    std::cout << "******************************\n";
    std::cout << "Choose an option (1-7): ";
}


int main()
{

    std::ofstream logFile("../log/log.txt", std::ios::trunc);
    if (!logFile)
    {
        std::cerr << "Error opening log file!" << std::endl;
    }


    std::string dir =  getDesktopPath().string();
    std::cout << "Working with the location: " << dir << std::endl;

    bool exitProgram = false;
    FileSorter *fileSorter = nullptr;
    FileCleaner *fileCleaner = nullptr;

    while (!exitProgram)
    {
        displayMenu();
        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            fileSorter = new FileSorter();
            fileSorter->setCurrentLocation(dir);
            fileSorter->ProcessFiles();
            delete fileSorter;
            fileSorter = nullptr;
            break;
        case 2:
            fileSorter = new SizeFileSorter();
            fileSorter->setCurrentLocation(dir);
            fileSorter->ProcessFiles();
            delete fileSorter;
            fileSorter = nullptr;
            break;
        case 3:
            fileSorter = new DateFileSorter();
            fileSorter->setCurrentLocation(dir);
            fileSorter->ProcessFiles();
            delete fileSorter;
            fileSorter = nullptr;
            break;
        case 4:
            fileCleaner = new ExtensionFileCleaner();
            fileCleaner->setCurrentLocation(dir);
            fileCleaner->setFilesToRemove();
            fileCleaner->removeFiles();
            delete fileCleaner;
            fileCleaner = nullptr;
            break;
        case 5:
        {
            fileCleaner = new DateFileCleaner();
            fileCleaner->setCurrentLocation(dir);
            fileCleaner->setFilesToRemove();
            fileCleaner->removeFiles();
            delete fileCleaner;
            fileCleaner = nullptr;
            break;
        }
        case 6:
        {
            std::cin.ignore();
            std::string newLocation;
            std::cout << "Provide a new location: ";
            std::getline(std::cin, newLocation);

            if (std::filesystem::exists(newLocation) && std::filesystem::is_directory(newLocation))
            {
                dir = newLocation;
                std::cout << "Location changed to: " << dir << std::endl;
            }
            else
            {
                std::cout << "Invalid path provided. Please check the location and try again.\n";
            }
            break;
        }
        case 7:
            std::cout << "Exiting program\n";
            exitProgram = true;
            break;
        default:
            std::cout << "Invalid choice Please select a valid option (1-7)\n";
            break;
        }
    }

    logFile.close();
    return 0;
}