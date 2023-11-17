#include <iostream>
#include "FileProcessor.h"
#include "SharedData.h"
#include <fstream>
#include "FileReaderFactory.h"
#include "FileWriterFactory.h"
#include "SharedMemoryHandler.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

using namespace boost::interprocess;

int main(int argc, char* argv[]) 
{
    if (argc != 4) 
    {
        std::cout << "Usage: " << argv[0] << " <input_file> <output_file> <shared_memory_object_name>" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];
    std::string sharedMemoryObjectName = argv[3];
   
    FileProcessorFactory* factory;

    try 
    {
        shared_memory_object sharedMemory(open_only, sharedMemoryObjectName, read_write);
        mapped_region region(sharedMemory, read_only);
        SharedData* sharedData = static_cast<SharedData*>(region.get_address());

        bool dataExist = false;
        {
           scoped_lock<interprocess_mutex> lock(sharedData->mutex);
            dataExist = sharedData->dataExist;
        }

        if (dataExist) 
        {
            std::cout << "Shared memory exists with data. Starting write process.\n";
            factory = new FileWriterFactory();
        }
        else {
            std::cout << "Shared memory exists without data. Starting read process.\n";
            factory = new FileReaderFactory();
        }
    }
    catch (const interprocess_exception& ex) 
    {
        std::cout << "Shared memory does not exist. Starting write process.\n";
        factory = new FileWriterFactory();
    }

    FileProcessor* processor = factory->createFileProcessor();
    processor->processFile(inputFileName, outputFileName, sharedMemoryObjectName);

    delete processor;
    delete factory;

    return 0;
}
