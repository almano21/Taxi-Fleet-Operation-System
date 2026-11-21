#ifndef MODELS_H
#define MODELS_H

#define LOCATION_COUNT 6
#define DRIVER_NAME_SIZE 20
#define INITIAL_DRIVER_CAPACITY 2
#define DEFAULT_DRIVER_COUNT 2

#define DRIVERS_FILE "drivers.csv"
#define TRIP_LOG_FILE "trip_log.csv"

#ifndef _MSC_VER
#define scanf_s scanf
#endif

struct Driver
{
    int driverID;
    char name[DRIVER_NAME_SIZE];

    int status;
    double pickupDistances[LOCATION_COUNT];
    int completedTrips;
    double revenue;
};

struct Trip
{
    int status;
    int orderHour;
    int orderMinute;
    long long contactPhoneNumber;
    int pickupLocation;
    int destinationLocation;
    double tripDistance;
    double fare;
    int assignedDriverID;
    int previousDriverStatus;
};

#endif
