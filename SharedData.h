#pragma once

#include <boost/interprocess/sync/interprocess_mutex.hpp>

const std::size_t chunk_size = 1024 * 1024;

volatile struct SharedData 
{
    bool ready;
    char data[chunk_size];
    std::size_t chunk_size;
    boost::interprocess::interprocess_mutex mutex;
};