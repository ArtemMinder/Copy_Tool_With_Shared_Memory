#include "FileReader.h"
#include <fstream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace std;
using namespace boost::interprocess;

void FileReader::processFile(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName, ios::binary);
    char data[1024 * 1024]; // Буфер размером 1 МБ

    while (inputFile.read(data, sizeof(data))) {
        shared_memory_object shm(open_or_create, "shared_memory", read_write);
        shm.truncate(inputFile.gcount());

        mapped_region region(shm, read_write);
        char* dest = static_cast<char*>(region.get_address());
        memcpy(dest, data, inputFile.gcount());
    }

    inputFile.close();
}
