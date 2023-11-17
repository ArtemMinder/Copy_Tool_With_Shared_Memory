#include "FileReaderFactory.h"
#include "FileReader.h"

FileProcessor* FileReaderFactory::createFileProcessor() 
{
    return new FileReader();
}
