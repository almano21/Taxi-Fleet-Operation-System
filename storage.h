#ifndef STORAGE_H
#define STORAGE_H

#include "models.h"

int loadDrivers(const char* fileName, struct Driver** drivers,
    int* count, int* capacity);

int saveDrivers(const char* fileName, const struct Driver* drivers, int count);

int appendTripLog(const char* fileName, const struct Trip* trip,
    const char* driverName);

#endif
