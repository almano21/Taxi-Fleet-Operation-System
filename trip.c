#include "trip.h"

double FareDistance(double tripDistance)
{
    const double baseFare = 2.50;
    const double ratePerKm = 1.00;

    return baseFare + ratePerKm * tripDistance;
}

int isValidOrderTime(int orderHour, int orderMinute)
{
    if (orderHour >= 0 && orderHour <= 23 &&
        orderMinute >= 0 && orderMinute <= 59)
    {
        return 1;
    }

    return 0;
}

int checkBookingRequirements(int isUserRegistered,
    int isCardLinked,
    int tripStatus)
{
    if (isUserRegistered == 0)
    {
        return 1;
    }

    if (isCardLinked == 0)
    {
        return 2;
    }

    if (tripStatus != 0)
    {
        return 3;
    }

    return 0;
}

int checkLocations(int pickupLocation, int destinationLocation)
{
    if (pickupLocation < 1 || pickupLocation > LOCATION_COUNT ||
        destinationLocation < 1 || destinationLocation > LOCATION_COUNT)
    {
        return 1;
    }

    if (pickupLocation == destinationLocation)
    {
        return 2;
    }

    return 0;
}

double getTripDistance(const double fixedDistance[LOCATION_COUNT][LOCATION_COUNT],
    int pickupLocation,
    int destinationLocation)
{
    return fixedDistance[pickupLocation - 1][destinationLocation - 1];
}

