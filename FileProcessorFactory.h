#pragma once

#include "FileProcessor.h"

class FileProcessorFactory {
public:
    virtual FileProcessor* createFileProcessor() = 0;
    virtual ~FileProcessorFactory() {}
};

