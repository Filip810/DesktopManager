#pragma once

#include "./Operations.h"

class FileCleaner : public Operations
{
protected:
    std::vector<std::string> filesToRemove;

public:
    virtual void setFilesToRemove() = 0;
    virtual std::vector<std::string> getFilesToRemove() const = 0;
    void setCurrentLocation(const std::string &dir) override;
    std::filesystem::path getCurrentLocation() const override;
    void removeFiles();
};
