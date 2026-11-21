#ifndef DRIVER_H
#define DRIVER_H

#include "models.h"

int selectDriver(const struct Driver drivers[],
    int driverCount,
    int pickupLocation,
    double maxAllowedDistance);

struct Driver* createDriverArray(int capacity);

void initDriverArray(struct Driver* drivers, int count);

void displayDriverArray(const struct Driver* drivers, int count);

int doubleDriverArray(struct Driver** drivers, int capacity);

int addDriver(struct Driver** drivers, int* count, int* capacity,
    const struct Driver* newDriver);

void freeDriverArray(struct Driver** drivers);

#endif
