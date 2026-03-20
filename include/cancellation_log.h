#ifndef CANCELLATION_LOG_H
#define CANCELLATION_LOG_H

/* ================================================================
   cancellation_log.h — Member 5 | Data Structure: STACK
   Module: Ticket Cancellation Log
   ================================================================
   RESPONSIBILITY:
     Records every ticket cancellation in the system.
     The most recent cancellation is always at the top —
     pure LIFO. If a cancellation was made by mistake,
     pop it to reinstate the ticket. The stack provides
     a complete audit trail of every cancellation made.

   EXTRA FUNCTION:
     getTotalRefundAmount()
     → traverses entire stack SUMMING the ticketPrice
       field of every cancellation record
     → Answers: "What is the total value of all
       cancelled tickets pending refund?"
     → Pure numeric SUM aggregate on stacked data —
       the strongest possible Stack extra function
   ================================================================ */

#include "shared_types.h"

/* ---------- Cancellation record structure ---------- */
typedef struct {
    int   cancellationID;
    int   ticketID;
    int   passengerID;
    int   trainID;                /* links to Train Fleet            */
    char  passengerName[NAME_LEN];
    char  trainName[NAME_LEN];
    char  fromStation[NAME_LEN];
    char  toStation[NAME_LEN];
    char  journeyDate[TIME_LEN];
    float ticketPrice;            /* used in getTotalRefundAmount()  */
    char  cancelledAt[TIME_LEN];
    char  reason[DESC_LEN];
} Cancellation;

/* ---------- Stack structure (array-based) ---------- */
typedef struct {
    Cancellation records[MAX_CANCELLATIONS];
    int top;                      /* -1 when empty                   */
} CancellationStack;

/* ---------- Global stack instance ---------- */
extern CancellationStack cancelStack;

/* ---------- Base operations ---------- */
void pushCancellation();         /* push new cancellation onto stack */
void popCancellation();          /* undo/reinstate last cancellation */
void peekLastCancellation();     /* view top without removing        */
void searchCancellation();       /* scan stack for a ticketID        */
void displayCancellationLog();   /* print full stack top → bottom    */
void clearLog();                 /* wipe all cancellation records    */
int  isStackEmpty();             /* check if stack is empty          */
int  isStackFull();              /* check if stack is full           */

/* ---------- Extra function ---------- */
void getTotalRefundAmount();     /* SUM all ticketPrice in stack     */

/* ---------- Formatted display ---------- */
void displayFormattedLog();      /* formatted box table              */

/* ---------- Sub-menu ---------- */
void cancellationLogMenu();

#endif /* CANCELLATION_LOG_H */
