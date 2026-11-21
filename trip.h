#ifndef TRIP_H
#define TRIP_H

#include "models.h"

double FareDistance(double tripDistance);

int isValidOrderTime(int orderHour, int orderMinute);

int checkBookingRequirements(int isUserRegistered,
    int isCardLinked,
    int tripStatus);

int checkLocations(int pickupLocation, int destinationLocation);

double getTripDistance(const double fixedDistance[LOCATION_COUNT][LOCATION_COUNT],
    int pickupLocation,
    int destinationLocation);

#endif
