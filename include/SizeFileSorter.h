#pragma once

#include "./FileSorter.h"

class SizeFileSorter : public FileSorter
{
public:
    void ProcessFiles() override;

protected:
    void processFile(const std::string &file) override;
};
