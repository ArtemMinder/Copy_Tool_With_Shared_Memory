#include "FileWriter.h"
#include "SharedData.h"
#include <iostream>
#include <fstream>
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

    while (inputFile) 
    {
        inputFile.read(sharedData->buffer, sizeof(sharedData->buffer));
        scoped_lock<interprocess_mutex> lock(sharedData->mutex);
        sharedData->dataExist = true;
        std::move(sharedData->buffer, sharedData->buffer + sizeof(sharedData->buffer), sharedData->buffer);
    }

    std::cout << "Write process completed.\n";
}
