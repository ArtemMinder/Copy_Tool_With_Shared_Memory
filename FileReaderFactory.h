#pragma once

#include "FileProcessorFactory.h"

class FileReaderFactory : public FileProcessorFactory 
{
public:
    FileProcessor* createFileProcessor() override;
};

