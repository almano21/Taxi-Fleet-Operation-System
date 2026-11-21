#include <stdio.h>
#include <stdlib.h>
#include "driver.h"

int selectDriver(const struct Driver drivers[],
    int driverCount,
    int pickupLocation,
    double maxAllowedDistance)
{
    int selectedDriverID = 0;
    double nearestDistance = 0.0;

    if (drivers == NULL || driverCount <= 0 ||
        pickupLocation < 1 || pickupLocation > LOCATION_COUNT)
    {
        return 0;
    }

    for (int i = 0; i < driverCount; i++)
    {
        if (drivers[i].status == 1)
        {
            double distance = drivers[i].pickupDistances[pickupLocation - 1];

            if (selectedDriverID == 0 || distance < nearestDistance ||
                (distance == nearestDistance &&
                    drivers[i].driverID < selectedDriverID))
            {
                selectedDriverID = drivers[i].driverID;
                nearestDistance = distance;
            }
        }
    }

    if (selectedDriverID != 0)
    {
        return selectedDriverID;
    }

    for (int i = 0; i < driverCount; i++)
    {
        double distance = drivers[i].pickupDistances[pickupLocation - 1];

        if (drivers[i].status == 2 && distance <= maxAllowedDistance)
        {
            if (selectedDriverID == 0 || distance < nearestDistance ||
                (distance == nearestDistance &&
                    drivers[i].driverID < selectedDriverID))
            {
                selectedDriverID = drivers[i].driverID;
                nearestDistance = distance;
            }
        }
    }

    return selectedDriverID;
}

struct Driver* createDriverArray(int capacity)
{
    if (capacity <= 0)
    {
        return NULL;
    }

    return calloc((size_t)capacity, sizeof(struct Driver));
}

void initDriverArray(struct Driver* drivers, int count)
{
    const struct Driver defaults[DEFAULT_DRIVER_COUNT] =
    {
        {1, "Karl", 1, {2.0, 1.0, 3.0, 7.0, 10.0, 14.0}, 0, 0.0},
        {2, "Gustavo", 1, {7.0, 8.0, 5.0, 2.0, 5.0, 9.0}, 0, 0.0}
    };

    if (drivers == NULL)
    {
        return;
    }

    for (int i = 0; i < count && i < DEFAULT_DRIVER_COUNT; i++)
    {
        drivers[i] = defaults[i];
    }
}

void displayDriverArray(const struct Driver* drivers, int count)
{
    if (drivers == NULL || count <= 0)
    {
        printf("No drivers are stored.\n");
        return;
    }

    printf("%-4s %-19s %-7s %-6s %s\n", "ID", "Name", "Status", "Trips", "Revenue");

    for (int i = 0; i < count; i++)
    {
        const struct Driver* current = drivers + i;

        printf("%-4d %-19s %-7d %-6d %.2f EUR\n",
            drivers[i].driverID,
            current->name,
            (*(drivers + i)).status,
            current->completedTrips,
            current->revenue);
    }
}

int doubleDriverArray(struct Driver** drivers, int capacity)
{
    int newCapacity;
    struct Driver* temporary;

    if (drivers == NULL || *drivers == NULL || capacity <= 0)
    {
        return -1;
    }

    newCapacity = capacity * 2;
    temporary = realloc(*drivers, (size_t)newCapacity * sizeof **drivers);

    if (temporary == NULL)
    {
        return -1;
    }

    *drivers = temporary;
    return newCapacity;
}

int addDriver(struct Driver** drivers, int* count, int* capacity,
    const struct Driver* newDriver)
{
    if (drivers == NULL || *drivers == NULL || count == NULL ||
        capacity == NULL || newDriver == NULL)
    {
        return 0;
    }

    if (*count == *capacity)
    {
        int newCapacity = doubleDriverArray(drivers, *capacity);

        if (newCapacity == -1)
        {
            printf("Not enough memory. The driver was not added.\n");
            return 0;
        }

        printf("Driver list was full: capacity grew from %d to %d.\n",
            *capacity, newCapacity);
        *capacity = newCapacity;
    }

    (*drivers)[*count] = *newDriver;
    *count = *count + 1;

    return 1;
}

void freeDriverArray(struct Driver** drivers)
{
    if (drivers != NULL)
    {
        free(*drivers);
        *drivers = NULL;
    }
}



