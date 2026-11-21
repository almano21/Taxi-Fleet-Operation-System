#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "trip.h"
#include "driver.h"
#include "admin.h"
#include "storage.h"

int runMainMenu(struct Driver** driverArray, int* driverCount,
    int* capacity, struct Trip* trip)
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

    int fleetMenuChoice = -1;
    int adminDriverID = 0;
    int newDriverStatus = 0;

    const double maxAllowedDistance = 5.0;

    struct Driver* drivers = *driverArray;

    const long long adminID = 100200300;
    const int adminPassword = 4471;

    const double fixedDistance[LOCATION_COUNT][LOCATION_COUNT] =
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
                isUserRegistered, isCardLinked, trip->status);

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
                    drivers, *driverCount, enteredPickup, maxAllowedDistance);

                if (selectedDriverID == 0)
                {
                    printf("No eligible driver is available. Please try later.\n");
                }
                else
                {
                    int driverIndex = selectedDriverID - 1;

                    trip->previousDriverStatus = drivers[driverIndex].status;
                    trip->assignedDriverID = selectedDriverID;
                    trip->orderHour = enteredHour;
                    trip->orderMinute = enteredMinute;
                    trip->contactPhoneNumber = phoneNumber;
                    trip->pickupLocation = enteredPickup;
                    trip->destinationLocation = enteredDestination;
                    trip->tripDistance = getTripDistance(
                        fixedDistance, enteredPickup, enteredDestination);
                    trip->fare = FareDistance(trip->tripDistance);
                    trip->status = 1;
                    drivers[driverIndex].status = 3;

                    printf("%s has been assigned to your taxi.\n", drivers[driverIndex].name);
                    printf("\n--- BOOKING SUMMARY ---\n");
                    printf("Trip distance: %.1f km\n", trip->tripDistance);
                    printf("Fare: %.2f EUR\n", trip->fare);
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
                if (trip->status == 0)
                {
                    printf("No current trip. Order a taxi first.\n");
                }
                else if (currentTripMenu == 1)
                {
                    if (trip->status == 2)
                    {
                        printf("Your trip has already started and been paid for.\n");
                    }
                    else
                    {
                        printf("%.2f EUR\n", trip->fare);
                        printf("Enter 1 to simulate successful payment or 0 to simulate failure: ");

                        if (scanf_s("%d", &paymentChoice) != 1)
                        {
                            printf("Invalid input or input ended. Please restart the program.\n");
                            return 1;
                        }

                        if (paymentChoice == 1)
                        {
                            trip->status = 2;
                            printf("Payment successful. Your trip has started.\n");
                        }
                        else if (paymentChoice == 0)
                        {
                            printf("Payment failed. Your trip remains booked and unpaid.\n");
                        }
                        else
                        {
                            printf("Invalid option. Choose 1 or 0.\n");
                        }
                    }
                }
                else if (currentTripMenu == 2)
                {
                    if (trip->status == 1)
                    {
                        printf("Your trip has not started. Start the trip and pay first.\n");
                    }
                    else if (trip->status == 2)
                    {
                        int driverIndex = trip->assignedDriverID - 1;

                        drivers[driverIndex].completedTrips = drivers[driverIndex].completedTrips + 1;
                        drivers[driverIndex].revenue = drivers[driverIndex].revenue + trip->fare;

                        if (!appendTripLog(TRIP_LOG_FILE, trip, drivers[driverIndex].name))
                        {
                            printf("Warning: the trip could not be written to %s.\n", TRIP_LOG_FILE);
                        }

                        drivers[driverIndex].status = 1;
                        trip->status = 0;
                        trip->assignedDriverID = 0;
                        trip->previousDriverStatus = 0;
                        trip->orderHour = -1;
                        trip->orderMinute = -1;
                        trip->contactPhoneNumber = 0;
                        trip->pickupLocation = 0;
                        trip->destinationLocation = 0;
                        trip->tripDistance = 0.0;
                        trip->fare = 0.0;

                        printf("Trip completed. Thank you for riding with TUDENGITAKSO!\n");
                    }
                }
                else if (currentTripMenu == 3)
                {
                    if (trip->status == 2)
                    {
                        printf("Your trip has already started and been paid for. Cancellation is unavailable.\n");
                    }
                    else if (trip->status == 1)
                    {
                        int driverIndex = trip->assignedDriverID - 1;

                        drivers[driverIndex].status = trip->previousDriverStatus;

                        trip->status = 0;
                        trip->assignedDriverID = 0;
                        trip->previousDriverStatus = 0;
                        trip->orderHour = -1;
                        trip->orderMinute = -1;
                        trip->contactPhoneNumber = 0;
                        trip->pickupLocation = 0;
                        trip->destinationLocation = 0;
                        trip->tripDistance = 0.0;
                        trip->fare = 0.0;

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

                for (int i = 0; i < *driverCount; i++)
                {
                    totalTrips += drivers[i].completedTrips;
                    totalRevenue += drivers[i].revenue;
                }

                printf("\n--- DAILY FLEET REPORT ---\n");
                printf("Total trips completed: %d\n", totalTrips);
                printf("Total revenue: %.2f EUR\n", totalRevenue);
                for (int i = 0; i < *driverCount; i++)
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
                printf("3. Add a driver\n");
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
                    printf("Stored drivers: %d (allocated capacity: %d)\n",
                        *driverCount, *capacity);

                    displayDriverArray(drivers, *driverCount);
                }
                else if (fleetMenuChoice == 2)
                {
                    if (canConfigureFleet(isAdminAuthenticated, trip->status) == 0)
                    {
                        printf("Driver status cannot be changed while a trip is booked or started.\n");
                    }
                    else
                    {
                        printf("Enter driver ID (1-%d): ", *driverCount);
                        if (scanf_s("%d", &adminDriverID) != 1)
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
                        if (adminDriverID >= 1 && adminDriverID <= *driverCount &&
                            newDriverStatus >= 1 && newDriverStatus <= 3)
                        {
                            int driverIndex = adminDriverID - 1;

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
                else if (fleetMenuChoice == 3)
                {
                    if (canConfigureFleet(isAdminAuthenticated, trip->status) == 0)
                    {
                        printf("Drivers cannot be added while a trip is booked or started.\n");
                    }
                    else
                    {
                        struct Driver newDriver;
                        int distancesValid = 1;

                        printf("Enter the driver's first name (max %d letters, no spaces or commas): ",
                            DRIVER_NAME_SIZE - 1);
                        if (scanf_s("%19s", newDriver.name, (unsigned)sizeof newDriver.name) != 1)
                        {
                            printf("Invalid input or input ended. Please restart the program.\n");
                            return 1;
                        }

                        for (int i = 0; i < LOCATION_COUNT; i++)
                        {
                            printf("Distance from the driver to location %d (0-50 km): ", i + 1);
                            if (scanf_s("%lf", &newDriver.pickupDistances[i]) != 1)
                            {
                                printf("Invalid input or input ended. Please restart the program.\n");
                                return 1;
                            }
                            if (newDriver.pickupDistances[i] < 0.0 ||
                                newDriver.pickupDistances[i] > 50.0)
                            {
                                distancesValid = 0;
                            }
                        }

                        if (strchr(newDriver.name, ',') != NULL || !distancesValid)
                        {
                            printf("Invalid name or distance. No driver was added.\n");
                        }
                        else
                        {
                            newDriver.driverID = *driverCount + 1;
                            newDriver.status = 1;
                            newDriver.completedTrips = 0;
                            newDriver.revenue = 0.0;

                            if (addDriver(driverArray, driverCount, capacity, &newDriver))
                            {
                                drivers = *driverArray;

                                printf("%s added with ID %d.\n",
                                    newDriver.name, newDriver.driverID);
                                printf("Stored drivers: %d (allocated capacity: %d)\n",
                                    *driverCount, *capacity);
                                displayDriverArray(drivers, *driverCount);
                            }
                        }
                    }
                }
                else
                {
                    printf("Invalid option. Choose from 0 to 3.\n");
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


