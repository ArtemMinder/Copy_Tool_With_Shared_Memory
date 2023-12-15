#include "FileWriter.h"
#include "SharedData.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

void FileWriter::processFile(const char* inputFileName, const char* outputFileName, const char* sharedMemoryName)
{
    std::ifstream inputFile(inputFileName, std::ios::binary);
    if (!inputFile.is_open()) 
    {
        std::cerr << "Error: Unable to open input file\n";
        return;
    }

    shared_memory_object sharedMemory(open_or_create, sharedMemoryName, read_write);
    sharedMemory.truncate(sizeof(SharedData));
    mapped_region region(sharedMemory, read_write);
    SharedData* sharedData = static_cast<SharedData*>(region.get_address());

    while (inputFile.read(sharedData->buffer, sizeof(SharedData)))
    {
        inputFile.read(sharedData->buffer, sizeof(sharedData->buffer));
        interprocess_mutex mutex(open_or_create);
        scoped_lock<interprocess_mutex> lock(mutex);
        sharedData += sizeof(SharedData);
        ++sharedData->chunkIndex;
        sharedData->dataExist = true;
    }

    size_t lastChunkSize = inputFile.gcount();

    if (lastChunkSize > 0) 
    {
        inputFile.read(sharedData->buffer, sizeof(sharedData->buffer));
        interprocess_mutex mutex(open_or_create);
        scoped_lock<interprocess_mutex> lock(mutex);
    }

    inputFile.close();

    std::cout << "Write process completed.\n";
}
