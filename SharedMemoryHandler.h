#pragma once

#include <string>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

class SharedMemoryHandler {
public:
    SharedMemoryHandler(const std::string& name, std::size_t size);
    ~SharedMemoryHandler();

    void writeData(const char* data, std::size_t size);
    void readData(char* buffer, std::size_t size);
    std::size_t getRegionSize();

private:
    boost::interprocess::shared_memory_object shm;
    boost::interprocess::mapped_region region;
};

