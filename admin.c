#include "admin.h"

int authenticateAdministrator(long long enteredID,
    int enteredPassword, long long adminID, int adminPassword)
{
    if (enteredID == adminID && enteredPassword == adminPassword)
    {
        return 1;
    }

    return 0;
}

int canConfigureFleet(int isAdminAuthenticated, int tripStatus)
{
    if (isAdminAuthenticated == 1 && tripStatus == 0)
    {
        return 1;
    }

    return 0;
}
