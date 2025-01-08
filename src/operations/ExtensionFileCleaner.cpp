#include "../../include/ExtensionFileCleaner.h"
#include <iostream>

void ExtensionFileCleaner::setFilesToRemove()
{
    std::string ext;
    std::cout << "Enter file extension to delete (e.g., .txt): ";
    std::cin >> ext;

    try
    {
        filesToRemove = listOfFileWithExtension(ext);
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Error setting files to remove: " << e.what() << std::endl;
    }
}

std::vector<std::string> ExtensionFileCleaner::getFilesToRemove() const
{
    return filesToRemove;
}