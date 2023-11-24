#pragma once

#include <boost/interprocess/sync/interprocess_mutex.hpp>

using namespace boost::interprocess;

struct SharedData {
    char buffer[1048576];
    interprocess_mutex mutex;
    bool dataExist;
    SharedData() : dataExist(false) {}
};