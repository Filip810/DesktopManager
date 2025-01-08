#include "../../include/Operations.h"

std::filesystem::path getDesktopPath()
{
    const char *userProfile = std::getenv("USERPROFILE");

    if (userProfile != nullptr)
    {
        return std::filesystem::path(userProfile) / "Desktop";
    }
    else
    {
        PWSTR path = nullptr;
        if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Desktop, 0, nullptr, &path)))
        {
            std::filesystem::path desktopPath(path);
            CoTaskMemFree(path);
            return desktopPath;
        }
        else
        {
            throw std::runtime_error("Unable to get Desktop path.");
        }
    }
}


std::vector<std::string> Operations::listOfFileWithExtension(const std::string &ext)
{

    std::ofstream logFile("../log/log.txt", std::ios::app);
    if (!logFile)
    {
        std::cerr << "Error opening log file" << std::endl;
    }
    std::vector<std::string> files;
    for (const auto &dir_entry : std::filesystem::directory_iterator{currentLocation})
    {
        if (!dir_entry.exists())
        {
            throw std::runtime_error("No files found in the specified directory");
        }

        if (ext == "*" || (dir_entry.is_regular_file() && dir_entry.path().extension() == ext))
        {
            files.push_back(dir_entry.path().string());
            logFile << dir_entry.path() << std::endl; 
        }
    }

    if (files.empty())
    {
        throw std::runtime_error("No files with extension " + ext + " found in the specified directory");
    }
    logFile.close();
    return files;

}

void Operations::createDirectories()
{
    try
    {
        std::filesystem::create_directory(currentLocation / "Documents");
        std::filesystem::create_directory(currentLocation / "Movies");
        std::filesystem::create_directory(currentLocation / "Applications");
        std::filesystem::create_directory(currentLocation / "Images");
        std::filesystem::create_directory(currentLocation / "Music");
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Error creating directory: " << e.what() << std::endl;
    }
}