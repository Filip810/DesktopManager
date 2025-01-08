#pragma once

#include "./FileCleaner.h"

class ExtensionFileCleaner : public FileCleaner
{
public:
    void setFilesToRemove() override;
    std::vector<std::string> getFilesToRemove() const override;
};
