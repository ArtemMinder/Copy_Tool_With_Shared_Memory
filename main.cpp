#include <iostream>
#include "FileProcessor.h"
#include "FileReaderFactory.h"
#include "FileWriterFactory.h"
#include "SharedMemoryHandler.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <input_file> <output_file> <shared_memory_object_name>" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];
    std::string sharedMemoryObjectName = argv[3];

    bool isSharedMemoryEmpty;

    try {
        SharedMemoryHandler shmHandler(sharedMemoryObjectName, 1048576);
        isSharedMemoryEmpty = (shmHandler.getRegionSize() == 0);
    }
    catch (const boost::interprocess::interprocess_exception& ex) {
        isSharedMemoryEmpty = true;
    }

    FileProcessorFactory* factory;

    if (isSharedMemoryEmpty) {
        factory = new FileReaderFactory();
    }
    else {
        factory = new FileWriterFactory();
    }

    FileProcessor* processor = factory->createFileProcessor();
    processor->processFile(inputFileName, outputFileName);

    delete processor;
    delete factory;

    return 0;
}
