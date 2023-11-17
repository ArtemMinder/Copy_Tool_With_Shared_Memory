#pragma once

#include <string>

class FileProcessor {
public:
    virtual void processFile(const std::string& inputFileName, const std::string& outputFileName, const std::string& sharedMemoryObjectName) = 0;
    virtual ~FileProcessor() {}
};
