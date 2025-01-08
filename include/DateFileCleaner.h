#pragma once

#include "FileCleaner.h"
#include <filesystem>
#include <string>

class DateFileCleaner : public FileCleaner
{
public:

    void setFilesToRemove() override;
    std::vector<std::string> getFilesToRemove() const override;
};
