/* ================================================================
   seat_reservations.c -- Member 5 | Data Structure: ARRAY (2nd use)
   Module: Seat Reservation Management
   ================================================================
   WHY ARRAY HERE:
     A train has a fixed number of seats that never changes.
     A Intercity train always has exactly 340 seats.
     An Express always has 460. These are physical constraints.
     Array models this fixed capacity perfectly -- direct
     access by seat number is O(1), no traversal needed.
     Bubble sort orders the seat map by seat number for
     clean display and organised management.
   ================================================================ */

#include <stdio.h>
#include <string.h>
#include "../include/seat_reservations.h"

/* ---------- Global seat map and state ---------- */
Seat seatMap[MAX_SEATS];
int  totalSeats      = 0;
int  currentTrainID  = -1;
char currentTrainName[NAME_LEN] = "";

/* ================================================================
   BASE OPERATIONS
   ================================================================ */

/* Check if a train's seat map has been loaded */
int isSeatMapEmpty() {
    return currentTrainID == -1;
}

/* Load seat map for a specific train
   In a real system this would load from database.
   Here we initialise a fresh seat map for the train. */
void loadTrainSeats() {
    int trainID, seats;
    char trainName[NAME_LEN];

    printf("\n--- Load Seat Map for a Train ---\n");
    printf("Enter Train ID          : T"); scanf("%d", &trainID);
    printf("Enter Train Name        : "); scanf(" %[^\n]", trainName);
    printf("Total seats on this train: "); scanf("%d", &seats);

    if (seats <= 0 || seats > MAX_SEATS) {
        printf("[!] Invalid seat count. Must be 1 to %d.\n", MAX_SEATS);
        return;
    }

    /* Ask for class breakdown */
    int firstClass, secondClass;
    printf("First class seats       : "); scanf("%d", &firstClass);
    printf("Second class seats      : "); scanf("%d", &secondClass);
    /* Remaining are third class */

    currentTrainID = trainID;
    strcpy(currentTrainName, trainName);
    totalSeats = seats;

    /* Initialise the seat array */
    for (int i = 0; i < totalSeats; i++) {
        seatMap[i].seatNumber = i + 1;
        strcpy(seatMap[i].status, "Available");
        strcpy(seatMap[i].passengerName, "");
        strcpy(seatMap[i].passengerNIC,  "");
        strcpy(seatMap[i].reservedAt,    "");
        strcpy(seatMap[i].journeyDate,   "");

        /* Assign class based on seat number */
        if (i + 1 <= firstClass)
            strcpy(seatMap[i].seatClass, "First");
        else if (i + 1 <= firstClass + secondClass)
            strcpy(seatMap[i].seatClass, "Second");
        else
            strcpy(seatMap[i].seatClass, "Third");
    }

    printf("[+] Seat map loaded for T%d %s | %d seats ready.\n",
           trainID, trainName, totalSeats);
}

/* Reserve a specific seat for a passenger */
void reserveSeat() {
    if (isSeatMapEmpty()) {
        printf("[!] No train loaded. Load a train seat map first.\n");
        return;
    }

    int seatNum;
    printf("\nEnter Seat Number to Reserve (1-%d): ", totalSeats);
    scanf("%d", &seatNum);

    if (seatNum < 1 || seatNum > totalSeats) {
        printf("[!] Invalid seat number.\n");
        return;
    }

    /* Array direct access by index -- O(1) */
    int idx = seatNum - 1;

    if (strcmp(seatMap[idx].status, "Reserved") == 0) {
        printf("[!] Seat %d is already reserved by %s.\n",
               seatNum, seatMap[idx].passengerName);
        return;
    }

    printf("Passenger Name : "); scanf(" %[^\n]", seatMap[idx].passengerName);
    printf("Passenger NIC  : "); scanf(" %[^\n]", seatMap[idx].passengerNIC);
    printf("Journey Date   : "); scanf(" %[^\n]", seatMap[idx].journeyDate);
    printf("Reserved At    : "); scanf(" %[^\n]", seatMap[idx].reservedAt);
    strcpy(seatMap[idx].status, "Reserved");

    printf("[+] Seat %d (%s class) reserved for %s on %s.\n",
           seatNum, seatMap[idx].seatClass,
           seatMap[idx].passengerName, seatMap[idx].journeyDate);
}

/* Release a reserved seat back to Available */
void releaseSeat() {
    if (isSeatMapEmpty()) {
        printf("[!] No train loaded.\n"); return;
    }

    int seatNum;
    printf("\nEnter Seat Number to Release (1-%d): ", totalSeats);
    scanf("%d", &seatNum);

    if (seatNum < 1 || seatNum > totalSeats) {
        printf("[!] Invalid seat number.\n"); return;
    }

    int idx = seatNum - 1;

    if (strcmp(seatMap[idx].status, "Available") == 0) {
        printf("[!] Seat %d is already available.\n", seatNum); return;
    }

    printf("[+] Seat %d released. Was reserved by: %s\n",
           seatNum, seatMap[idx].passengerName);

    /* Clear passenger data */
    strcpy(seatMap[idx].status,        "Available");
    strcpy(seatMap[idx].passengerName, "");
    strcpy(seatMap[idx].passengerNIC,  "");
    strcpy(seatMap[idx].reservedAt,    "");
    strcpy(seatMap[idx].journeyDate,   "");
}

/* Update passenger details for an existing reservation */
void updateReservation() {
    if (isSeatMapEmpty()) {
        printf("[!] No train loaded.\n"); return;
    }

    int seatNum;
    printf("\nEnter Seat Number to Update (1-%d): ", totalSeats);
    scanf("%d", &seatNum);

    if (seatNum < 1 || seatNum > totalSeats) {
        printf("[!] Invalid seat number.\n"); return;
    }

    int idx = seatNum - 1;

    if (strcmp(seatMap[idx].status, "Available") == 0) {
        printf("[!] Seat %d is not reserved. Nothing to update.\n", seatNum);
        return;
    }

    printf("Update:\n  1. Passenger Name\n  2. NIC\n  3. Journey Date\nChoice: ");
    int ch; scanf("%d", &ch);
    switch (ch) {
        case 1:
            printf("New passenger name : ");
            scanf(" %[^\n]", seatMap[idx].passengerName); break;
        case 2:
            printf("New NIC            : ");
            scanf(" %[^\n]", seatMap[idx].passengerNIC); break;
        case 3:
            printf("New journey date   : ");
            scanf(" %[^\n]", seatMap[idx].journeyDate); break;
        default:
            printf("[!] Invalid choice.\n"); return;
    }
    printf("[+] Seat %d updated.\n", seatNum);
}

/* Search seat by number or passenger name */
void searchSeat() {
    if (isSeatMapEmpty()) {
        printf("[!] No train loaded.\n"); return;
    }

    printf("\nSearch by:\n  1. Seat Number\n  2. Passenger Name\nChoice: ");
    int ch; scanf("%d", &ch);
    int found = 0;

    if (ch == 1) {
        int seatNum;
        printf("Enter Seat Number: "); scanf("%d", &seatNum);
        if (seatNum < 1 || seatNum > totalSeats) {
            printf("[!] Invalid seat number.\n"); return;
        }
        int idx = seatNum - 1;
        printf(DIVIDER);
        printf("  Seat Number  : %d\n",   seatMap[idx].seatNumber);
        printf("  Class        : %s\n",   seatMap[idx].seatClass);
        printf("  Status       : %s\n",   seatMap[idx].status);
        if (strcmp(seatMap[idx].status, "Reserved") == 0) {
            printf("  Passenger    : %s\n", seatMap[idx].passengerName);
            printf("  NIC          : %s\n", seatMap[idx].passengerNIC);
            printf("  Journey Date : %s\n", seatMap[idx].journeyDate);
            printf("  Reserved At  : %s\n", seatMap[idx].reservedAt);
        }
        printf(DIVIDER);
        found = 1;

    } else {
        char name[NAME_LEN];
        printf("Enter Passenger Name: "); scanf(" %[^\n]", name);
        for (int i = 0; i < totalSeats; i++) {
            if (strstr(seatMap[i].passengerName, name)) {
                printf("  Seat %-4d | %-8s | %-10s | %s\n",
                       seatMap[i].seatNumber, seatMap[i].seatClass,
                       seatMap[i].status,     seatMap[i].journeyDate);
                found = 1;
            }
        }
    }
    if (!found) printf("[!] No matching seat found.\n");
}

/* Display full seat map in a readable layout */
void displaySeatMap() {
    if (isSeatMapEmpty()) {
        printf("[!] No train loaded. Load a train first.\n"); return;
    }

    printf("\nSeat map for T%d %s (%d seats total)\n",
           currentTrainID, currentTrainName, totalSeats);
    printf(DIVIDER);
    printf("%-6s %-10s %-12s %-25s %-15s\n",
           "Seat", "Class", "Status", "Passenger", "Journey Date");
    printf(DIVIDER);

    for (int i = 0; i < totalSeats; i++) {
        printf("%-6d %-10s %-12s %-25s %-15s\n",
               seatMap[i].seatNumber,
               seatMap[i].seatClass,
               seatMap[i].status,
               strcmp(seatMap[i].status, "Reserved") == 0
                   ? seatMap[i].passengerName : "-",
               strcmp(seatMap[i].status, "Reserved") == 0
                   ? seatMap[i].journeyDate : "-");
    }
    printf(DIVIDER);
    printf("Total: %d seats | ", totalSeats);

    /* Quick count inline */
    int avail = 0;
    for (int i = 0; i < totalSeats; i++)
        if (strcmp(seatMap[i].status, "Available") == 0) avail++;
    printf("Available: %d | Reserved: %d\n", avail, totalSeats - avail);
}

/* ================================================================
   SORT -- BUBBLE SORT by Seat Number (ascending)
   Keeps the seat map ordered after any manual reordering.
   ================================================================ */
void bubbleSortBySeatNumber() {
    if (isSeatMapEmpty() || totalSeats < 2) {
        printf("[!] Not enough seats to sort.\n"); return;
    }

    Seat temp;
    int swapped;

    for (int i = 0; i < totalSeats - 1; i++) {
        swapped = 0;
        for (int j = 0; j < totalSeats - i - 1; j++) {
            if (seatMap[j].seatNumber > seatMap[j+1].seatNumber) {
                temp          = seatMap[j];
                seatMap[j]    = seatMap[j+1];
                seatMap[j+1]  = temp;
                swapped       = 1;
            }
        }
        if (!swapped) break;
    }
    printf("[+] Seat map sorted by seat number (1 -> %d).\n", totalSeats);
    displaySeatMap();
}

/* ================================================================
   EXTRA FUNCTION -- countAvailableSeats()
   TYPE: Conditional COUNT across array elements
   Scans every element in the seat array and counts those
   whose status field equals "Available".
   Answers: "How many seats are still open on this train?"
   ================================================================ */
void countAvailableSeats() {
    if (isSeatMapEmpty()) {
        printf("[!] No train loaded.\n"); return;
    }

    int available = 0, reserved = 0;
    int firstAvail = 0, secondAvail = 0, thirdAvail = 0;

    for (int i = 0; i < totalSeats; i++) {
        if (strcmp(seatMap[i].status, "Available") == 0) {
            available++;
            if      (strcmp(seatMap[i].seatClass, "First")  == 0) firstAvail++;
            else if (strcmp(seatMap[i].seatClass, "Second") == 0) secondAvail++;
            else                                                   thirdAvail++;
        } else {
            reserved++;
        }
    }

    printf("\n========== SEAT AVAILABILITY ==========\n");
    printf("  Train          : T%d %s\n", currentTrainID, currentTrainName);
    printf("  Total Seats    : %d\n",     totalSeats);
    printf("  Available      : %d\n",     available);
    printf("  Reserved       : %d\n",     reserved);
    printf("  Occupancy      : %.1f%%\n",
           totalSeats > 0 ? (float)reserved / totalSeats * 100 : 0);
    printf("  ---- By Class ----\n");
    printf("  First  class   : %d available\n", firstAvail);
    printf("  Second class   : %d available\n", secondAvail);
    printf("  Third  class   : %d available\n", thirdAvail);
    printf("========================================\n");
}

/* ================================================================
   FORMATTED DISPLAY
   ================================================================ */
void displaySeatTable() {
    if (isSeatMapEmpty()) {
        printf("[!] No train loaded.\n"); return;
    }

    printf("\nT%d -- %s | Seat Reservation Map\n",
           currentTrainID, currentTrainName);
    printf("+------+----------+------------+-------------------------+---------------+\n");
    printf("| Seat | Class    | Status     | Passenger               | Journey Date  |\n");
    printf("+------+----------+------------+-------------------------+---------------+\n");

    for (int i = 0; i < totalSeats; i++) {
        printf("| %-4d | %-8s | %-10s | %-23s | %-13s |\n",
               seatMap[i].seatNumber,
               seatMap[i].seatClass,
               seatMap[i].status,
               strcmp(seatMap[i].status, "Reserved") == 0
                   ? seatMap[i].passengerName : "-",
               strcmp(seatMap[i].status, "Reserved") == 0
                   ? seatMap[i].journeyDate : "-");
    }
    printf("+------+----------+------------+-------------------------+---------------+\n");

    int avail = 0;
    for (int i = 0; i < totalSeats; i++)
        if (strcmp(seatMap[i].status, "Available") == 0) avail++;
    printf("  %d / %d seats available\n", avail, totalSeats);
}

/* ================================================================
   SUB-MENU -- Member 5
   ================================================================ */
void seatReservationsMenu() {
    int choice;
    do {
        printf("\n%s", HEADER);
        printf("     SEAT RESERVATION MANAGEMENT  [ARRAY]\n");
        printf("%s", HEADER);
        if (currentTrainID != -1)
            printf("  Loaded: T%d %s (%d seats)\n",
                   currentTrainID, currentTrainName, totalSeats);
        else
            printf("  No train loaded. Select option 1 first.\n");
        printf(DIVIDER);
        printf("  1.  Load Train Seat Map\n");
        printf("  2.  Reserve a Seat\n");
        printf("  3.  Release a Seat\n");
        printf("  4.  Update Reservation\n");
        printf("  5.  Search Seat\n");
        printf("  6.  Display Seat Map\n");
        printf("  7.  Sort by Seat Number  [Bubble Sort]\n");
        printf("  8.  Count Available Seats  [EXTRA]\n");
        printf("  9.  Display Seat Table\n");
        printf("  0.  Back to Main Menu\n");
        printf("%s", HEADER);
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: loadTrainSeats();          break;
            case 2: reserveSeat();             break;
            case 3: releaseSeat();             break;
            case 4: updateReservation();       break;
            case 5: searchSeat();              break;
            case 6: displaySeatMap();          break;
            case 7: bubbleSortBySeatNumber();  break;
            case 8: countAvailableSeats();     break;
            case 9: displaySeatTable();        break;
            case 0: break;
            default: printf("[!] Invalid choice.\n");
        }
    } while (choice != 0);
}
