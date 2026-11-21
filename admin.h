#ifndef ADMIN_H
#define ADMIN_H

int authenticateAdministrator(long long enteredID,
    int enteredPassword, long long adminID, int adminPassword);

int canConfigureFleet(int isAdminAuthenticated, int tripStatus);

#endif
