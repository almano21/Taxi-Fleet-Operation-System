#include <stdio.h>
#include "models.h"
#include "driver.h"
#include "storage.h"
#include "menu.h"

int main(void)
{
    int capacity = INITIAL_DRIVER_CAPACITY;
    int driverCount = 0;
    int loadResult;
    int exitCode;

    struct Trip trip = { 0, -1, -1, 0, 0, 0, 0.0, 0.0, 0, 0 };

    struct Driver* drivers = createDriverArray(capacity);
    if (drivers == NULL)
    {
        printf("Not enough memory to start TUDENGITAKSO.\n");
        return 1;
    }

    loadResult = loadDrivers(DRIVERS_FILE, &drivers, &driverCount, &capacity);
    if (loadResult > 0)
    {
        printf("Loaded %d drivers from %s.\n", driverCount, DRIVERS_FILE);
    }
    else
    {
        driverCount = DEFAULT_DRIVER_COUNT;
        initDriverArray(drivers, driverCount);
        printf("Using the default fleet (%d drivers).\n", driverCount);
    }

    exitCode = runMainMenu(&drivers, &driverCount, &capacity, &trip);

    if (trip.status != 0 && trip.assignedDriverID >= 1 &&
        trip.assignedDriverID <= driverCount)
    {
        drivers[trip.assignedDriverID - 1].status = trip.previousDriverStatus;
        printf("The unfinished trip was not saved.\n");
    }

    if (saveDrivers(DRIVERS_FILE, drivers, driverCount))
    {
        printf("Driver data saved to %s.\n", DRIVERS_FILE);
    }
    else
    {
        printf("Warning: driver data could not be saved to %s.\n", DRIVERS_FILE);
    }

    freeDriverArray(&drivers);

    return exitCode;
}


