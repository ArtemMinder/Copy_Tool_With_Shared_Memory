#pragma once

#include "FileProcessor.h"

class FileReader : public FileProcessor 
{
public:
    void processFile(const char* inputFileName, const  char* outputFileName, const char* sharedMemoryName) override;
};
