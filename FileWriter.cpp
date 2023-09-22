#include "FileWriter.h"
#include <fstream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace std;
using namespace boost::interprocess;

void FileWriter::processFile(const string& inputFileName, const string& outputFileName) {
    shared_memory_object shm(open_only, "shared_memory", read_only);

    mapped_region region(shm, read_only);
    ofstream outputFile(outputFileName, ios::binary);
    outputFile.write(static_cast<char*>(region.get_address()), region.get_size());
    outputFile.close();
}
