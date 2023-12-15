#pragma once

struct SharedData 
{
    char buffer[1048576];
    int chunkIndex = 0;
    bool dataExist = false;
};