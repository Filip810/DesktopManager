#pragma once

#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <windows.h>
#include <shlobj.h>
#include <stdexcept>
#include <fstream>

std::filesystem::path getDesktopPath();

class Operations
{
protected:
    std::filesystem::path currentLocation;

public:
    virtual void setCurrentLocation(const std::string &dir) = 0;
    virtual std::filesystem::path getCurrentLocation() const = 0;
    std::vector<std::string> listOfFileWithExtension(const std::string &ext);
    void createDirectories();
};