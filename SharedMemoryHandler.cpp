#include "SharedMemoryHandler.h"
#include <boost/interprocess/exceptions.hpp>

SharedMemoryHandler::SharedMemoryHandler(const std::string& name, std::size_t size) {
    try {
        boost::interprocess::shared_memory_object::remove(name.c_str());
        shm = boost::interprocess::shared_memory_object(boost::interprocess::create_only, name.c_str(), boost::interprocess::read_write);
        shm.truncate(size);
        region = boost::interprocess::mapped_region(shm, boost::interprocess::read_write);
    }
    catch (const boost::interprocess::interprocess_exception& ex) {
        throw;
    }
}

SharedMemoryHandler::~SharedMemoryHandler() {
    boost::interprocess::shared_memory_object::remove(shm.get_name());
}

void SharedMemoryHandler::writeData(const char* data, std::size_t size) {
    char* dest = static_cast<char*>(region.get_address());
    std::memcpy(dest, data, size);
}

void SharedMemoryHandler::readData(char* buffer, std::size_t size) {
    char* src = static_cast<char*>(region.get_address());
    std::memcpy(buffer, src, size);
}

std::size_t SharedMemoryHandler::getRegionSize() {
    return region.get_size();
}


