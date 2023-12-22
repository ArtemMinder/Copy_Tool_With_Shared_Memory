#include "FileWriter.h"
#include "SharedData.h"
#include <iostream>
#include <fstream>
#include <thread> 
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


    std::vector<char> buffer(chunk_size);

    while (true)
    {
        scoped_lock<interprocess_mutex> lock(sharedData->mutex);

        if (!sharedData->ready)
        {
            inputFile.read(buffer.data(), buffer.size());

            std::size_t bytes_read = inputFile.gcount();
            if (bytes_read == 0)
            {
                sharedData->chunk_size = 0;
                sharedData->ready = true;
                break;
            }

            std::memcpy(sharedData->data, buffer.data(), bytes_read);
            sharedData->chunk_size = bytes_read;
            sharedData->ready = true;
        }
    }

    inputFile.close();

    std::cout << "Write process completed.\n";
}
