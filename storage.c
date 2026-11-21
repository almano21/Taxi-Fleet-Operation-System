#include <stdio.h>
#include "storage.h"
#include "driver.h"

#define LINE_SIZE 256

int loadDrivers(const char* fileName, struct Driver** drivers,
    int* count, int* capacity)
{
    FILE* file;
    char line[LINE_SIZE];
    int lineNumber = 0;

    file = fopen(fileName, "r");
    if (file == NULL)
    {
        return 0;
    }

    *count = 0;

    while (fgets(line, sizeof line, file) != NULL)
    {
        struct Driver record;
        double* d = record.pickupDistances;
        int valid = 1;

        lineNumber++;

        if (lineNumber == 1 || line[0] == '\n' || line[0] == '\r')
        {
            continue;
        }

        if (sscanf(line, "%d,%19[^,],%d,%lf,%lf,%lf,%lf,%lf,%lf,%d,%lf",
                &record.driverID, record.name, &record.status,
                &d[0], &d[1], &d[2], &d[3], &d[4], &d[5],
                &record.completedTrips, &record.revenue) != 11)
        {
            valid = 0;
        }

        if (valid && (record.driverID != *count + 1 ||
            record.status < 1 || record.status > 3 ||
            record.completedTrips < 0 || record.revenue < 0.0))
        {
            valid = 0;
        }

        for (int i = 0; valid && i < LOCATION_COUNT; i++)
        {
            if (d[i] < 0.0)
            {
                valid = 0;
            }
        }

        if (!valid)
        {
            printf("%s line %d is invalid. Using the default fleet.\n",
                fileName, lineNumber);
            fclose(file);
            *count = 0;
            return -1;
        }

        if (!addDriver(drivers, count, capacity, &record))
        {
            fclose(file);
            *count = 0;
            return -1;
        }
    }

    fclose(file);
    return *count;
}

int saveDrivers(const char* fileName, const struct Driver* drivers, int count)
{
    FILE* file = fopen(fileName, "w");

    if (file == NULL)
    {
        return 0;
    }

    fprintf(file, "id,name,status,dist1,dist2,dist3,dist4,dist5,dist6,"
        "completedTrips,revenue\n");

    for (int i = 0; i < count; i++)
    {
        const struct Driver* driver = drivers + i;

        fprintf(file, "%d,%s,%d", driver->driverID, driver->name, driver->status);
        for (int j = 0; j < LOCATION_COUNT; j++)
        {
            fprintf(file, ",%.1f", driver->pickupDistances[j]);
        }
        fprintf(file, ",%d,%.2f\n", driver->completedTrips, driver->revenue);
    }

    fclose(file);
    return 1;
}

int appendTripLog(const char* fileName, const struct Trip* trip,
    const char* driverName)
{
    FILE* file;
    int isNewFile;

    file = fopen(fileName, "r");
    isNewFile = (file == NULL);
    if (file != NULL)
    {
        fclose(file);
    }

    file = fopen(fileName, "a");
    if (file == NULL)
    {
        return 0;
    }

    if (isNewFile)
    {
        fprintf(file, "orderTime,pickup,destination,distanceKm,fareEur,driver\n");
    }

    fprintf(file, "%02d:%02d,%d,%d,%.1f,%.2f,%s\n",
        trip->orderHour, trip->orderMinute,
        trip->pickupLocation, trip->destinationLocation,
        trip->tripDistance, trip->fare, driverName);

    fclose(file);
    return 1;
}



