#include <stdio.h>

int main(void)
{
    // Control the main menu and keep the program running.
        int mainMenuChoice = -1;
        int programRunning = 1;

   // Store the student's registration information during this session.
        int isUserRegistered = 0;
        long long studentID = 0;
        long long phoneNumber = 0;

   // Store the status and fictional bank card information during this session.
        int isCardLinked = 0;
        int cardLinkChoice = -1;
        long long demoCardNumber = 0;
        int expiryMonth = 0;
        int expiryYear = 0;

        // Store the current taxi order and simulated fleet status.
        int isTripActive = 0;
        int orderHour = -1;
        int orderMinute = -1;
        int pickupLocation = 0;
        int destinationLocation = 0;

        int isRushHour = 0;
        int isKarlFree = 1;
        int isGustavoFree = 1;
        int karlDistance = 0;
        int gustavoDistance = 0;
        int maxAllowedDistance = 5;
        int assignedDriver = 0;

   // Display the main menu repeatedly until the user selects Exit.
        while (programRunning == 1) {

            printf("----TUDENGITAKSO----\n");
            printf("\n1. Create an account\n2. Link a bank card\n3. Order a taxi\n4. Complete trip and pay\n5. View daily fleet report\n0. Exit\nChoose an option: ");

            scanf_s("%d", &mainMenuChoice);
            if (mainMenuChoice == 0)
            {
                printf("Program closed. Thank you for using TUDENGITAKSO!\n");
                programRunning = 0;
            }
            // Option 1: Create and validate a student account.
            else if (mainMenuChoice == 1)
            {
                if (isUserRegistered == 1)
                {
                    printf("You are already registered. Please choose another menu option.\n");
                }
                else
                {
                    printf("Enter the 12 digits between S and M in your student ID: ");
                    scanf_s("%lld", &studentID);

                    printf("Enter your phone number starting with 372 followed by 8 digits: ");
                    scanf_s("%lld", &phoneNumber);

                    // Check for a 12-digit student ID and an Estonian phone number.
                    if (studentID >= 100000000000LL && studentID <= 999999999999LL && phoneNumber / 100000000 == 372)
                    {
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
            // Option 2: Link a fictional bank card to a registered account.
            else if (mainMenuChoice == 2)
            {
                if (isUserRegistered == 0)
                {
                    printf("Bank card can't be linked. Register your account first.\n");
                }
                else
                {
                    if (isCardLinked == 1)
                    {
                        printf("Your card is already linked.\n");
                    }
                    else
                    {
                        printf("Enter 1 to link a demo bank card or 0 to cancel: ");
                        scanf_s("%d", &cardLinkChoice);
                        if (cardLinkChoice == 1)
                        {
                            printf("Enter a fictional 16-digit card number: ");
                            scanf_s("%lld", &demoCardNumber);

                            printf("Enter the expiry month (1-12): ");
                            scanf_s("%d", &expiryMonth);

                            printf("Enter the expiry year (2026-2036): ");
                            scanf_s("%d", &expiryYear);
                            // Validate the 16-digit fictional card number and expiry date.
                            if (demoCardNumber >= 1000000000000000LL &&
                                demoCardNumber <= 9999999999999999LL &&
                                expiryMonth >= 1 && expiryMonth <= 12 &&
                                expiryYear >= 2026 && expiryYear <= 2036)
                            {
                                isCardLinked = 1;
                                printf("Bank card linked successfully! Happy riding with TUDENGITAKSO!\n");
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

            }
            else if (mainMenuChoice == 3)
            {
               
                    if (isUserRegistered == 0)
                {
                    printf("Can't order a taxi. Register your account first.\n");
                }
                else if (isCardLinked == 0)
                {
                    printf("Can't order a taxi. Link a bank card first.\n");
                }
                else if (isTripActive == 1)
                {
                    printf("Can't order another taxi. Complete your current trip first.\n");
                }
                else
                    {
                        printf("Enter the order hour (0-23): ");
                        scanf_s("%d", &orderHour);

                        printf("Enter the order minute (0-59): ");
                        scanf_s("%d", &orderMinute);


                        if (orderHour >= 1 && orderHour <= 23 &&
                            orderMinute >= 1 && orderMinute <= 59)
                        {
                            printf("Order time recorded: %02d:%02d\n", orderHour, orderMinute);
                            printf("\n--- TUDENGITAKSO LOCATIONS ---\n");
                            printf("1. TalTech Main Building\n"
                                "2. Akadeemia Student Dormitory\n"
                                "3. Mustamae Keskus\n"
                                "4. Telliskivi / Balti Jaam\n"
                                "5. Tallinn Airport\n"
                                "6. IKEA Tallinn (Kurna)\n");

                            printf("Choose the pickup location: ");
                            scanf_s("%d", &pickupLocation);

                            printf("Choose the destination: ");
                            scanf_s("%d", &destinationLocation);
                            if (pickupLocation < 0 || pickupLocation > 6 ||
                                destinationLocation < 0 || destinationLocation > 6)
                            {
                                printf("Invalid location. Please choose numbers from 1 to 6.\n");
                            }
                            else if (pickupLocation == destinationLocation)
                            {
                                printf("Pickup and destination cannot be the same.\n");
                            }
                            else
                            {
                                // Set each driver's distance from the selected pickup location.
                                if (pickupLocation == 1)
                                {
                                    karlDistance = 2;
                                    gustavoDistance = 7;
                                }
                                else if (pickupLocation == 2)
                                {
                                    karlDistance = 1;
                                    gustavoDistance = 8;
                                }
                                else if (pickupLocation == 3)
                                {
                                    karlDistance = 3;
                                    gustavoDistance = 5;
                                }
                                else if (pickupLocation == 4)
                                {
                                    karlDistance = 7;
                                    gustavoDistance = 2;
                                }
                                else if (pickupLocation == 5)
                                {
                                    karlDistance = 10;
                                    gustavoDistance = 5;
                                }
                                else if (pickupLocation == 6)
                                {
                                    karlDistance = 14;
                                    gustavoDistance = 9;
                                }

                                printf("Karl is %d km from the pickup location.\n", karlDistance);
                                printf("Gustavo is %d km from the pickup location.\n", gustavoDistance);
                            }
                           
                        }
                        else
                        {
                            printf("Invalid time. Enter an hour from 0 to 23 and minutes from 0 to 59.\n");
                           
                        }

                    }
               
            }
            else if (mainMenuChoice >= 4 && mainMenuChoice <= 5)
            {
                printf("You selected option %d.\n", mainMenuChoice);
            }
            else
            {
                printf("Invalid input. Please choose an option from 0 to 5.\n");
            }

        }
        return 0;
}
