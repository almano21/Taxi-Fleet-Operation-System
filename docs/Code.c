#include <stdio.h>

struct Driver
{
    int driverID;
    char name[20];
    /* 1 = free; 2 = busy/en route; 3 = busy/unavailable, including reserved. */
    int status;
    double pickupDistances[6];
    int completedTrips;
    double revenue;
};

/* Keeps the current booking's related values together. */
struct Trip
{
    /* 0 = none; 1 = booked/unpaid; 2 = started/paid. */
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
    if (pickupLocation < 1 || pickupLocation > 6 ||
        destinationLocation < 1 || destinationLocation > 6)
    {
        return 1;
    }

    if (pickupLocation == destinationLocation)
    {
        return 2;
    }

    return 0;
}

/* Call only after location validation has succeeded. */
double getTripDistance(const double fixedDistance[6][6],
    int pickupLocation,
    int destinationLocation)
{
    return fixedDistance[pickupLocation - 1][destinationLocation - 1];
}

/* Choose a driver without changing records or creating a booking.
 * Equal distances select the lower ID (Karl), regardless of array order.
 */
int selectDriver(const struct Driver drivers[],
    int driverCount,
    int pickupLocation,
    double maxAllowedDistance)
{
    int selectedDriverID = 0;
    double nearestDistance = 0.0;

    if (driverCount <= 0 ||
        pickupLocation < 1 || pickupLocation > 6)
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

int authenticateAdministrator(long long enteredID,
    int enteredPassword, long long adminID,int adminPassword){

    if (enteredID == adminID && enteredPassword == adminPassword) {
        return 1;
    }
    else {
        return 0;
    }


}

int canConfigureFleet(int isAdminAuthenticated, int tripStatus) {
    if (isAdminAuthenticated == 1 && tripStatus == 0) {
        return 1;
    }
    else {
        return 0;
    }

}


int main(void)
{
    int mainMenuChoice = -1;
    int programRunning = 1;

    int isUserRegistered = 0;
    long long studentID = 0;
    long long phoneNumber = 0;

    int isCardLinked = 0;
    int cardLinkChoice = -1;
    long long demoCardNumber = 0;
    int expiryMonth = 0;
    int expiryYear = 0;

    int currentTripMenu = -1;
    int paymentChoice = -1;

    // Store the administrator's fleet menu choices.
    int fleetMenuChoice = -1;
    int selectedDriverID = 0;
    int newDriverStatus = 0;

    const double maxAllowedDistance = 5.0;

    struct Trip trip = { 0, -1, -1, 0, 0, 0, 0.0, 0.0, 0, 0 };

    /* This order is fixed: index 0 = ID 1; index 1 = ID 2. */
    struct Driver drivers[2] =
    {
        {1, "Karl", 1, {2.0, 1.0, 3.0, 7.0, 10.0, 14.0}, 0, 0.0},
        {2, "Gustavo", 1, {7.0, 8.0, 5.0, 2.0, 5.0, 9.0}, 0, 0.0}
    };

    const long long adminID = 100200300;
    const int adminPassword = 4471;

    /* Rows are pickup locations; columns are destinations. */
    const double fixedDistance[6][6] =
    {
        {0.0, 1.0, 2.6, 7.0, 9.2, 12.9},
        {0.8, 0.0, 2.6, 7.1, 9.3, 13.4},
        {2.4, 2.6, 0.0, 5.3, 8.0, 12.7},
        {7.2, 7.3, 5.8, 0.0, 5.7, 18.3},
        {9.2, 9.4, 7.9, 5.8, 0.0, 13.2},
        {12.1, 12.7, 12.7, 14.7, 14.2, 0.0}
    };

    while (programRunning == 1)
    {
        printf("\n---- TUDENGITAKSO ----\n");
        printf("1. Create an account\n"
            "2. Link a bank card\n"
            "3. Order a taxi\n"
            "4. Manage current trip\n"
            "5. View daily fleet report\n"
            "6. Fleet administration\n"
            "0. Exit\n");

        printf("Choose an option: ");
        if (scanf_s("%d", &mainMenuChoice) != 1)
        {
            printf("Invalid input or input ended. Please restart the program.\n");
            return 1;
        }

        if (mainMenuChoice == 0)
        {
            printf("Program closed. Thank you for using TUDENGITAKSO!\n");
            programRunning = 0;
        }
        else if (mainMenuChoice == 1)
        {
            if (isUserRegistered == 1)
            {
                printf("You are already registered. Choose another menu option.\n");
            }
            else
            {
                long long enteredStudentID;
                long long enteredPhone;

                printf("Enter the 12 digits between S and M (first digit 1-9): ");
                if (scanf_s("%lld", &enteredStudentID) != 1)
                {
                    printf("Invalid input or input ended. Please restart the program.\n");
                    return 1;
                }

                printf("Enter your phone number: 372 followed by 8 digits: ");
                if (scanf_s("%lld", &enteredPhone) != 1)
                {
                    printf("Invalid input or input ended. Please restart the program.\n");
                    return 1;
                }

                if (enteredStudentID >= 100000000000LL &&
                    enteredStudentID <= 999999999999LL &&
                    enteredPhone / 100000000LL == 372)
                {
                    studentID = enteredStudentID;
                    phoneNumber = enteredPhone;
                    isUserRegistered = 1;
                    printf("Registration successful! Choose option 2 to link your bank card.\n");
                    printf("Registered student ID: S%lldM\n", studentID);
                }
                else
                {
                    printf("Invalid student ID or phone number. Please try again.\n");
                }
            }
        }
        else if (mainMenuChoice == 2)
        {
            if (isUserRegistered == 0)
            {
                printf("Bank card can't be linked. Register your account first.\n");
            }
            else if (isCardLinked == 1)
            {
                printf("Your card is already linked.\n");
            }
            else
            {
                printf("Enter 1 to link a demo bank card or 0 to cancel: ");
                if (scanf_s("%d", &cardLinkChoice) != 1)
                {
                    printf("Invalid input or input ended. Please restart the program.\n");
                    return 1;
                }

                if (cardLinkChoice == 1)
                {
                    long long enteredCardNumber;
                    int enteredMonth;
                    int enteredYear;

                    printf("Enter a fictional 16-digit card number: ");
                    if (scanf_s("%lld", &enteredCardNumber) != 1)
                    {
                        printf("Invalid input or input ended. Please restart the program.\n");
                        return 1;
                    }
                    printf("Enter the expiry month (1-12): ");
                    if (scanf_s("%d", &enteredMonth) != 1)
                    {
                        printf("Invalid input or input ended. Please restart the program.\n");
                        return 1;
                    }
                    printf("Enter the expiry year (2026-2036): ");
                    if (scanf_s("%d", &enteredYear) != 1)
                    {
                        printf("Invalid input or input ended. Please restart the program.\n");
                        return 1;
                    }

                    if (enteredCardNumber >= 1000000000000000LL &&
                        enteredCardNumber <= 9999999999999999LL &&
                        enteredMonth >= 1 && enteredMonth <= 12 &&
                        enteredYear >= 2026 && enteredYear <= 2036)
                    {
                        demoCardNumber = enteredCardNumber;
                        expiryMonth = enteredMonth;
                        expiryYear = enteredYear;
                        isCardLinked = 1;
                        printf("Demo card ending in %04lld linked successfully!\n",
                            demoCardNumber % 10000LL);
                        printf("Demo expiry: %02d/%d\n", expiryMonth, expiryYear);
                    }
                    else
                    {
                        printf("Invalid card information. The card was not linked.\n");
                    }
                }
                else if (cardLinkChoice == 0)
                {
                    printf("Bank card linking cancelled. Returning to the main menu.\n");
                }
                else
                {
                    printf("Invalid input. Please enter 1 to link or 0 to cancel.\n");
                }
            }
        }
        else if (mainMenuChoice == 3)
        {
            int bookingResult = checkBookingRequirements(
                isUserRegistered, isCardLinked, trip.status);

            if (bookingResult == 1)
            {
                printf("Can't order a taxi. Register your account first.\n");
            }
            else if (bookingResult == 2)
            {
                printf("Can't order a taxi. Link a bank card first.\n");
            }
            else if (bookingResult == 3)
            {
                printf("Can't order another taxi. Manage your current trip first.\n");
            }
            else
            {
                /* Validate temporary inputs before changing the trip record. */
                int enteredHour;
                int enteredMinute;
                int enteredPickup;
                int enteredDestination;
                int locationResult;
                int selectedDriverID;

                printf("Enter the order hour (0-23): ");
                if (scanf_s("%d", &enteredHour) != 1)
                {
                    printf("Invalid input or input ended. Please restart the program.\n");
                    return 1;
                }
                printf("Enter the order minute (0-59): ");
                if (scanf_s("%d", &enteredMinute) != 1)
                {
                    printf("Invalid input or input ended. Please restart the program.\n");
                    return 1;
                }

                if (!isValidOrderTime(enteredHour, enteredMinute))
                {
                    printf("Invalid time. Enter an hour from 0 to 23 and minutes from 0 to 59.\n");
                    continue;
                }

                printf("Order time recorded: %02d:%02d\n", enteredHour, enteredMinute);
                printf("\n--- TUDENGITAKSO LOCATIONS ---\n"
                    "1. TalTech Main Building\n"
                    "2. Academic Hostel\n"
                    "3. Mustamae Keskus\n"
                    "4. Balti Jaam railway station\n"
                    "5. Tallinn Airport\n"
                    "6. IKEA Tallinn\n");

                printf("Choose the pickup location: ");
                if (scanf_s("%d", &enteredPickup) != 1)
                {
                    printf("Invalid input or input ended. Please restart the program.\n");
                    return 1;
                }
                printf("Choose the destination: ");
                if (scanf_s("%d", &enteredDestination) != 1)
                {
                    printf("Invalid input or input ended. Please restart the program.\n");
                    return 1;
                }

                locationResult = checkLocations(enteredPickup, enteredDestination);
                if (locationResult == 1)
                {
                    printf("Invalid location. Please choose numbers from 1 to 6.\n");
                    continue;
                }
                if (locationResult == 2)
                {
                    printf("Pickup and destination cannot be the same.\n");
                    continue;
                }

                selectedDriverID = selectDriver(
                    drivers, 2, enteredPickup, maxAllowedDistance);

                if (selectedDriverID == 0)
                {
                    printf("No eligible driver is available. Please try later.\n");
                }
                else
                {
                    int driverIndex = selectedDriverID - 1;

                    trip.previousDriverStatus = drivers[driverIndex].status;
                    trip.assignedDriverID = selectedDriverID;
                    trip.orderHour = enteredHour;
                    trip.orderMinute = enteredMinute;
                    trip.contactPhoneNumber = phoneNumber;
                    trip.pickupLocation = enteredPickup;
                    trip.destinationLocation = enteredDestination;
                    trip.tripDistance = getTripDistance(
                        fixedDistance, enteredPickup, enteredDestination);
                    trip.fare = FareDistance(trip.tripDistance);
                    trip.status = 1;
                    drivers[driverIndex].status = 3;

                    printf("%s has been assigned to your taxi.\n", drivers[driverIndex].name);
                    printf("\n--- BOOKING SUMMARY ---\n");
                    printf("Trip distance: %.1f km\n", trip.tripDistance);
                    printf("Fare: %.2f EUR\n", trip.fare);
                    printf("Booking saved. No payment has been made.\n");
                }
            }
        }
        else if (mainMenuChoice == 4)
        {
            printf("\n--- MANAGE CURRENT TRIP ---\n"
                "1. Start trip and pay\n"
                "2. Complete trip\n"
                "3. Cancel booking\n"
                "0. Return to main menu\n");

            printf("Choose an option: ");
            if (scanf_s("%d", &currentTripMenu) != 1)
            {
                printf("Invalid input or input ended. Please restart the program.\n");
                return 1;
            }

            if (currentTripMenu == 0)
            {
                printf("Returning to main menu.\n");
            }
            else if (currentTripMenu >= 1 && currentTripMenu <= 3)
            {
                if (trip.status == 0)
                {
                    printf("No current trip. Order a taxi first.\n");
                }
                else if (currentTripMenu == 1)
                {
                    if (trip.status == 2)
                    {
                        printf("Your trip has already started and been paid for.\n");
                    }
                    else
                    {
                        printf("%.2f EUR\n", trip.fare);
                        printf("Enter 1 to simulate successful payment or 0 to simulate failure: ");

                        if (scanf_s("%d", &paymentChoice) != 1) {
                            printf("Invalid input or input ended. Please restart the program.\n");
                            return 1;
                        }

                        if (paymentChoice == 1) {
                            trip.status = 2;
                            printf("Payment successful. Your trip has started.\n");
                        }
                        else if (paymentChoice == 0) {
                            printf("Payment failed. Your trip remains booked and unpaid.\n");
                        }
                        else {
                            printf("Invalid option. Choose 1 or 0.\n");
                        }
                    }
                }
                else if (currentTripMenu == 2)
                {
                    if (trip.status == 1)
                    {
                        printf("Your trip has not started. Start the trip and pay first.\n");
                    }
                    else if (trip.status == 2)
                    {
                        int driverIndex = trip.assignedDriverID - 1;

                        drivers[driverIndex].completedTrips = drivers[driverIndex].completedTrips + 1;
                        drivers[driverIndex].revenue = drivers[driverIndex].revenue + trip.fare;

                        drivers[driverIndex].status = 1;
                        trip.status = 0;
                        trip.assignedDriverID = 0;
                        trip.previousDriverStatus = 0;
                        trip.orderHour = -1;
                        trip.orderMinute = -1;
                        trip.contactPhoneNumber = 0;
                        trip.pickupLocation = 0;
                        trip.destinationLocation = 0;
                        trip.tripDistance = 0.0;
                        trip.fare = 0.0;

                        printf("Trip completed. Thank you for riding with TUDENGITAKSO!\n");
                    }
                }
                else if (currentTripMenu == 3)
                {
                    if (trip.status == 2)
                    {
                        printf("Your trip has already started and been paid for. Cancellation is unavailable.\n");
                    }
                    else if (trip.status == 1)
                    {
                        int driverIndex = trip.assignedDriverID - 1;

                        // Restore the driver's status before clearing the saved value.
                        drivers[driverIndex].status = trip.previousDriverStatus;

                        // Clear the cancelled booking.
                        trip.status = 0;
                        trip.assignedDriverID = 0;
                        trip.previousDriverStatus = 0;
                        trip.orderHour = -1;
                        trip.orderMinute = -1;
                        trip.contactPhoneNumber = 0;
                        trip.pickupLocation = 0;
                        trip.destinationLocation = 0;
                        trip.tripDistance = 0.0;
                        trip.fare = 0.0;

                        printf("Your trip has been cancelled! Come back again?\n");
                        printf("No payment was taken.\n");
                    }
                }
            }
            else
            {
                printf("Invalid option. Choose from 0 to 3.\n");
            }
        }
        else if (mainMenuChoice == 5)
        {
            long long enteredID;
            int enteredPassword;

            printf("Administrator login required.\n");
            printf("Enter admin ID: ");
            if (scanf_s("%lld", &enteredID) != 1)
            {
                printf("Invalid input or input ended. Please restart the program.\n");
                return 1;
            }
            printf("Enter admin password: ");
            if (scanf_s("%d", &enteredPassword) != 1)
            {
                printf("Invalid input or input ended. Please restart the program.\n");
                return 1;
            }

            if (authenticateAdministrator(
                enteredID, enteredPassword, adminID, adminPassword) == 1)
            {
                int totalTrips = 0;
                double totalRevenue = 0.0;

                /* Derive fleet totals from the same records as driver totals. */
                for (int i = 0; i < 2; i++)
                {
                    totalTrips += drivers[i].completedTrips;
                    totalRevenue += drivers[i].revenue;
                }

                printf("\n--- DAILY FLEET REPORT ---\n");
                printf("Total trips completed: %d\n", totalTrips);
                printf("Total revenue: %.2f EUR\n", totalRevenue);
                for (int i = 0; i < 2; i++)
                {
                    printf("%s: %d trips, %.2f EUR revenue\n",
                        drivers[i].name, drivers[i].completedTrips, drivers[i].revenue);
                }
            }
            else
            {
                printf("Invalid administrator credentials.\n");
            }
        }
        else if (mainMenuChoice == 6)
        {
            long long enteredID;
            int enteredPassword;

            printf("Administrator login required.\n");

            printf("Enter admin ID: ");
            if (scanf_s("%lld", &enteredID) != 1)
            {
                printf("Invalid input or input ended. Please restart the program.\n");
                return 1;
            }

            printf("Enter admin password: ");
            if (scanf_s("%d", &enteredPassword) != 1)
            {
                printf("Invalid input or input ended. Please restart the program.\n");
                return 1;
            }

            int isAdminAuthenticated = authenticateAdministrator(
                enteredID, enteredPassword, adminID, adminPassword);

            if (isAdminAuthenticated == 1)
            {
                printf("\n--- FLEET ADMINISTRATION ---\n");
                printf("1. View driver status\n");
                printf("2. Change driver status\n");
                printf("0. Return to main menu\n");

                printf("Choose an option: ");
                if (scanf_s("%d", &fleetMenuChoice) != 1)
                {
                    printf("Invalid input or input ended. Please restart the program.\n");
                    return 1;
                }

                if (fleetMenuChoice == 0)
                {
                    printf("Returning to main menu.\n");
                }
                else if (fleetMenuChoice == 1)
                {
                    printf("\n--- DRIVER STATUS ---\n");
                    printf("1 = Free\n");
                    printf("2 = Busy / en route\n");
                    printf("3 = Busy / unavailable, including reserved\n");

                    for (int i = 0; i < 2; i++)
                    {
                        printf("%s: status %d\n", drivers[i].name, drivers[i].status);
                    }
                }
                else if (fleetMenuChoice == 2)
                {
                    if (canConfigureFleet(isAdminAuthenticated, trip.status) == 0)
                    {
                        printf("Driver status cannot be changed while a trip is booked or started.\n");
                    }
                    else
                    {
                        printf("Enter driver ID (1 = Karl, 2 = Gustavo): ");
                        if (scanf_s("%d", &selectedDriverID) != 1)
                        {
                            printf("Invalid input or input ended. Please restart the program.\n");
                            return 1;
                        }

                        printf("Enter new status (1 = Free, 2 = Busy/en route, 3 = Unavailable): ");
                        if (scanf_s("%d", &newDriverStatus) != 1)
                        {
                            printf("Invalid input or input ended. Please restart the program.\n");
                            return 1;
                        }
                        if (selectedDriverID >= 1 && selectedDriverID <= 2 &&
                            newDriverStatus >= 1 && newDriverStatus <= 3)
                        {
                            int driverIndex = selectedDriverID - 1;

                            drivers[driverIndex].status = newDriverStatus;

                            printf("%s now has status %d.\n",
                                drivers[driverIndex].name,
                                drivers[driverIndex].status);
                        }
                        else
                        {
                            printf("Invalid driver ID or status. No changes were made.\n");
                        }
                    }
                }
                else
                {
                    printf("Invalid option. Choose from 0 to 2.\n");
                }
            }
            else
            {
                printf("Invalid administrator credentials.\n");
            }
}
        else
        {
            printf("Invalid input. Please choose an option from 0 to 6.\n");
        }
    }

    return 0;
}
