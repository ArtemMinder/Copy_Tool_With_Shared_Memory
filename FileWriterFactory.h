#pragma once

#include "FileProcessorFactory.h"

class FileWriterFactory : public FileProcessorFactory 
{
public:
    FileProcessor* createFileProcessor() override;
};

