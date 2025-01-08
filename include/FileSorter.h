#pragma once

#include "./Operations.h"

class FileSorter : public Operations
{
public:
    void setCurrentLocation(const std::string &dir) override;
    std::filesystem::path getCurrentLocation() const override;
    virtual void ProcessFiles();

protected:
    virtual void processFile(const std::string &file);
    void moveFileToCategory(const std::string &file);
};
