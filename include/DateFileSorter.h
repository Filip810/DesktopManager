#pragma once

#include "./FileSorter.h"

class DateFileSorter : public FileSorter
{
public:
    void ProcessFiles() override;

protected:
    void processFile(const std::string &file) override;
};
