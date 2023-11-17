#include "FileReader.h"
#include "SharedData.h"
#include <fstream>
#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace std;
using namespace boost::interprocess;

void FileReader::processFile(const char* inputFileName, const char* outputFileName, const char* sharedMemoryName)
{
    shared_memory_object sharedMemory(open_only, sharedMemoryName, read_write);
    mapped_region region(sharedMemory, read_write);
    SharedData* sharedData = static_cast<SharedData*>(region.get_address());
    std::ofstream outputFile(outputFileName, std::ios::binary | std::ios::app);

    while (true) 
    {
        scoped_lock<interprocess_mutex> lock(sharedData->mutex);

        if (sharedData->dataExist) 
        {
            outputFile.write(sharedData->buffer, sizeof(sharedData->buffer));
            sharedData->dataExist = false;
        }
    }

    std::cout << "Read process completed." << std::endl;
}
