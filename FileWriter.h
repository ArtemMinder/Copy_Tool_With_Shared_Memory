#pragma once

#include "FileProcessor.h"

class FileWriter : public FileProcessor {
public:
    void processFile(const std::string& inputFileName, const std::string& outputFileName, const std::string& sharedMemoryObjectName) override;
};

