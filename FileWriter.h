#pragma once

#include "FileProcessor.h"

class FileWriter : public FileProcessor 
{
public:
    void processFile(const char* inputFileName, const char* outputFileName, const char* sharedMemoryObjectName) override;
};

