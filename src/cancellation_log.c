/* ================================================================
   cancellation_log.c — Member 5 | Data Structure: STACK
   Module: Ticket Cancellation Log
   ================================================================ */

#include <stdio.h>
#include <string.h>
#include "../include/cancellation_log.h"

/* ---------- Global stack instance ---------- */
CancellationStack cancelStack;

/* ---------- ID generator ---------- */
static int cancelIDCounter = 500;

/* ================================================================
   BASE OPERATIONS
   ================================================================ */

int isStackEmpty() { return cancelStack.top == -1; }
int isStackFull()  { return cancelStack.top == MAX_CANCELLATIONS - 1; }

/* Push a new cancellation record onto the stack */
void pushCancellation() {
    if (isStackFull()) {
        printf("[!] Cancellation log is full.\n"); return;
    }
    Cancellation c;
    c.cancellationID = ++cancelIDCounter;

    printf("\n--- Record Ticket Cancellation ---\n");
    printf("Ticket ID              : "); scanf("%d", &c.ticketID);
    printf("Passenger ID           : "); scanf("%d", &c.passengerID);
    printf("Passenger Name         : "); scanf(" %[^\n]", c.passengerName);
    printf("Train ID               : T"); scanf("%d", &c.trainID);
    printf("Train Name             : "); scanf(" %[^\n]", c.trainName);
    printf("From Station           : "); scanf(" %[^\n]", c.fromStation);
    printf("To Station             : "); scanf(" %[^\n]", c.toStation);
    printf("Journey Date           : "); scanf(" %[^\n]", c.journeyDate);
    printf("Ticket Price (Rs.)     : "); scanf("%f", &c.ticketPrice);
    printf("Reason for Cancellation: "); scanf(" %[^\n]", c.reason);
    printf("Cancelled At (time)    : "); scanf(" %[^\n]", c.cancelledAt);

    cancelStack.records[++cancelStack.top] = c;
    printf("[+] Cancellation C%d pushed. Stack depth: %d\n",
           c.cancellationID, cancelStack.top + 1);
}

/* Pop last cancellation — reinstate the ticket */
void popCancellation() {
    if (isStackEmpty()) {
        printf("[!] No cancellations to undo.\n"); return;
    }
    Cancellation c = cancelStack.records[cancelStack.top--];
    printf("\n[CANCELLATION REVERSED — TICKET REINSTATED]\n");
    printf(DIVIDER);
    printf("  Cancel ID   : C%d\n",   c.cancellationID);
    printf("  Ticket ID   : %d\n",    c.ticketID);
    printf("  Passenger   : %s\n",    c.passengerName);
    printf("  Train       : T%d — %s\n", c.trainID, c.trainName);
    printf("  Route       : %s → %s\n", c.fromStation, c.toStation);
    printf("  Date        : %s\n",    c.journeyDate);
    printf("  Refund      : Rs. %.2f\n", c.ticketPrice);
    printf(DIVIDER);
    printf("[+] Ticket reinstated. Stack depth now: %d\n",
           cancelStack.top + 1);
}

/* Peek at the most recent cancellation without removing */
void peekLastCancellation() {
    if (isStackEmpty()) {
        printf("[!] Cancellation log is empty.\n"); return;
    }
    Cancellation c = cancelStack.records[cancelStack.top];
    printf("\n[LATEST CANCELLATION — TOP OF STACK]\n");
    printf(DIVIDER);
    printf("  Cancel ID   : C%d\n",   c.cancellationID);
    printf("  Ticket ID   : %d\n",    c.ticketID);
    printf("  Passenger   : %s\n",    c.passengerName);
    printf("  Train       : T%d — %s\n", c.trainID, c.trainName);
    printf("  Route       : %s → %s\n", c.fromStation, c.toStation);
    printf("  Price       : Rs. %.2f\n", c.ticketPrice);
    printf("  Reason      : %s\n",    c.reason);
    printf(DIVIDER);
}

/* Search stack for a specific ticketID */
void searchCancellation() {
    if (isStackEmpty()) {
        printf("[!] Cancellation log is empty.\n"); return;
    }
    int tid;
    printf("Enter Ticket ID to search: "); scanf("%d", &tid);
    int found = 0;
    for (int i = cancelStack.top; i >= 0; i--) {
        if (cancelStack.records[i].ticketID == tid) {
            Cancellation c = cancelStack.records[i];
            printf("  C%-4d | Ticket:%d | %-20s | T%d | %s → %s | Rs.%.2f\n",
                   c.cancellationID, c.ticketID, c.passengerName,
                   c.trainID, c.fromStation, c.toStation, c.ticketPrice);
            found = 1;
        }
    }
    if (!found) printf("[!] Ticket %d not found in cancellation log.\n", tid);
}

/* Display full stack from top to bottom */
void displayCancellationLog() {
    if (isStackEmpty()) {
        printf("[!] Cancellation log is empty.\n"); return;
    }
    printf("\n[CANCELLATION LOG — Latest → Oldest]\n");
    printf("%-5s %-8s %-20s %-6s %-15s %-15s %-10s\n",
           "No.","CancelID","Passenger","TrnID","From","To","Price");
    printf(DIVIDER);
    for (int i = cancelStack.top; i >= 0; i--) {
        Cancellation c = cancelStack.records[i];
        printf("%-5d C%-6d %-20s T%-5d %-15s %-15s Rs.%-7.2f%s\n",
               cancelStack.top - i + 1,
               c.cancellationID, c.passengerName, c.trainID,
               c.fromStation, c.toStation, c.ticketPrice,
               (i == cancelStack.top) ? " <- TOP" : "");
    }
    printf(DIVIDER);
    printf("Stack depth: %d cancellations\n", cancelStack.top + 1);
}

/* Clear all cancellations from the log */
void clearLog() {
    char confirm;
    printf("Clear all cancellation records? (y/n): ");
    scanf(" %c", &confirm);
    if (confirm == 'y' || confirm == 'Y') {
        cancelStack.top = -1;
        printf("[+] Cancellation log cleared.\n");
    } else {
        printf("[!] Clear cancelled.\n");
    }
}

/* ================================================================
   EXTRA FUNCTION — getTotalRefundAmount()
   TYPE: Aggregate SUM — traverses entire stack summing ticketPrice
   Answers: "What is the total value of pending refunds?"
   ================================================================ */
void getTotalRefundAmount() {
    if (isStackEmpty()) {
        printf("[!] No cancellations in log.\n"); return;
    }
    float total     = 0;
    int   count     = 0;
    float highest   = 0;
    float lowest    = cancelStack.records[0].ticketPrice;

    for (int i = 0; i <= cancelStack.top; i++) {
        float price = cancelStack.records[i].ticketPrice;
        total += price;
        count++;
        if (price > highest) highest = price;
        if (price < lowest)  lowest  = price;
    }
    printf("\n========== TOTAL REFUND AMOUNT ==========\n");
    printf("  Cancellations pending : %d\n",    count);
    printf("  Total refund due      : Rs. %.2f\n", total);
    printf("  Average refund        : Rs. %.2f\n", total / count);
    printf("  Highest single refund : Rs. %.2f\n", highest);
    printf("  Lowest single refund  : Rs. %.2f\n", lowest);
    printf("==========================================\n");
}

/* ================================================================
   FORMATTED DISPLAY
   ================================================================ */
void displayFormattedLog() {
    if (isStackEmpty()) {
        printf("[!] Cancellation log is empty.\n"); return;
    }
    printf("\n╔══════╦════════╦══════════════════════╦═══════╦═══════════════╦═══════════════╦══════════╗\n");
    printf("║  No. ║ CancelD║ Passenger            ║ TrnID ║ From          ║ To            ║ Price    ║\n");
    printf("╠══════╬════════╬══════════════════════╬═══════╬═══════════════╬═══════════════╬══════════╣\n");
    for (int i = cancelStack.top; i >= 0; i--) {
        Cancellation c = cancelStack.records[i];
        printf("║ %-4d ║ C%-5d ║ %-20s ║ T%-4d ║ %-13s ║ %-13s ║ Rs.%-5.2f ║%s\n",
               cancelStack.top - i + 1, c.cancellationID,
               c.passengerName, c.trainID,
               c.fromStation, c.toStation, c.ticketPrice,
               (i == cancelStack.top) ? "<-TOP" : "");
    }
    printf("╚══════╩════════╩══════════════════════╩═══════╩═══════════════╩═══════════════╩══════════╝\n");
}

/* ================================================================
   SUB-MENU — Member 5
   ================================================================ */
void cancellationLogMenu() {
    /* Initialize stack on first entry */
    static int initialized = 0;
    if (!initialized) { cancelStack.top = -1; initialized = 1; }

    int choice;
    do {
        printf("\n%s", HEADER);
        printf("       TICKET CANCELLATION LOG  [STACK]\n");
        printf("%s", HEADER);
        printf("  1.  Push Cancellation\n");
        printf("  2.  Pop / Reinstate Last Cancellation\n");
        printf("  3.  Peek Latest Cancellation\n");
        printf("  4.  Search by Ticket ID\n");
        printf("  5.  Display Cancellation Log\n");
        printf("  6.  Clear Log\n");
        printf("  7.  Get Total Refund Amount  [EXTRA]\n");
        printf("  8.  Display Formatted Log\n");
        printf("  0.  Back to Main Menu\n");
        printf("%s", HEADER);
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: pushCancellation();       break;
            case 2: popCancellation();        break;
            case 3: peekLastCancellation();   break;
            case 4: searchCancellation();     break;
            case 5: displayCancellationLog(); break;
            case 6: clearLog();               break;
            case 7: getTotalRefundAmount();   break;
            case 8: displayFormattedLog();    break;
            case 0: break;
            default: printf("[!] Invalid choice.\n");
        }
    } while (choice != 0);
}
