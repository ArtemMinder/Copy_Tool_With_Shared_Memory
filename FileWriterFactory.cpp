#include "FileWriterFactory.h"
#include "FileWriter.h"

FileProcessor* FileWriterFactory::createFileProcessor() 
{
    return new FileWriter();
}
