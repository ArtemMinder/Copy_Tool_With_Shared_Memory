#pragma once

#include "FileProcessor.h"

class FileReader : public FileProcessor 
{
public:
    void processFile(const std::string& inputFileName, const  std::string& outputFileName, const std::string& sharedMemoryName) override;
};
