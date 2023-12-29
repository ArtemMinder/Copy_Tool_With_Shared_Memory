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

	std::vector<char> buffer(chunk_size);

	bool file_complete = false;
	while (!file_complete)
	{
		scoped_lock<interprocess_mutex> lock(sharedData->mutex);

		std::memcpy(buffer.data(), sharedData->data, sharedData->chunk_size);
		outputFile.write(buffer.data(), sharedData->chunk_size);
		sharedData->ready = false;

		if (sharedData->chunk_size == 0)
		{
			file_complete = true;
		}
		break;
	}

	std::fill(std::begin(sharedData->data), std::end(sharedData->data), '\0');

	outputFile.close();

	std::cout << "Read process completed." << std::endl;
}
