#pragma once

class FileProcessor 
{
public:
    virtual void processFile(const char* inputFileName, const char* outputFileName, const char* sharedMemoryObjectName) = 0;
    virtual ~FileProcessor() {}
};
