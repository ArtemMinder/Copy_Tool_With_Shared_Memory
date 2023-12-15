#include "FileReader.h"
#include "SharedData.h"
#include <fstream>
#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

using namespace std;
using namespace boost::interprocess;

void FileReader::processFile(const char* inputFileName, const char* outputFileName, const char* sharedMemoryName)
{
	shared_memory_object sharedMemory(open_only, sharedMemoryName, read_write);
	mapped_region region(sharedMemory, read_write);
	SharedData* sharedData = static_cast<SharedData*>(region.get_address());
	std::ofstream outputFile(outputFileName, std::ios::binary | std::ios::app);

	size_t receivedChunks = 0;

    while (receivedChunks < sharedData->chunkIndex)
	{
		interprocess_mutex mutex(open_or_create);
        scoped_lock<interprocess_mutex> lock(mutex);
		outputFile.write(sharedData->buffer, sizeof(sharedData->buffer));
		++receivedChunks;
		sharedData->dataExist = false;
    }

	std::fill(std::begin(sharedData->buffer), std::end(sharedData->buffer), '\0');

	outputFile.close();

	std::cout << "Read process completed." << std::endl;
}
